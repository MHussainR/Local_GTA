#include "stacked_sprites.hpp"
#include "Shapes.hpp"
#include <omp.h>

#include <cmath>

Stacked_Sprites::Stacked_Sprites(const char *textursheet, SDL_Renderer *ren, int x, int y, int srcx, int srcy, int srcw, int srch, int ang, int nl, int step, int delt, int scal)
{
    texture = TextureManager::LoadTexture(textursheet, ren);
    x_pos = x;
    y_pos = y;
    game_speed = 2;
    scale = scal;
    num_layers = nl;
    this->step = step;
#pragma omp parallel for
    {
        for (int i = 0; i < num_layers; i += step)
        {
            srcRects[i] = {srcx, srcy * (num_layers - i - 1), srcw, srch};
            moverRects[i] = {x_pos, y_pos + (i * 4), srcRects[i].w * scale, srcRects[i].h * scale};
        }
    }
    renderer = ren;
    angle = ang;
    flip = SDL_FLIP_NONE;
    shape = new Shapes();
    delta = delt;
    // memo = std::map<std::pair<float, float>, std::pair<float, float>>();
}

Stacked_Sprites::~Stacked_Sprites()
{
    delete shape;
}

void Stacked_Sprites::Update(int x, int y)
{
    // Calculate the distance between the Stacked_Sprites and the target coordinates.
    float dist = shape->Distance(x_pos + moverRects[0].w / 2, y_pos + moverRects[0].h / 2, x, y);

    if (dist < 1500)
    {
        // Calculate the angle (theta) between the Stacked_Sprites and the target coordinates.
        float theta = -(std::atan2((x_pos + moverRects[0].w / 2 - x), (y_pos + moverRects[0].h / 2 - y))) + M_PI_2;

        // Calculate the sine and cosine values of the angle.
        float sin_theta = std::sin(theta);
        float cos_theta = std::cos(theta);

#pragma omp parallel for
        {
            for (int i = 0; i < num_layers; i += step)
            {
                // Update the mover rectangles based on the angle and delta values.
                moverRects[i] = {x_pos + int(i * delta * cos_theta), y_pos + int(i * delta * sin_theta), srcRects[i].w * scale, srcRects[i].h * scale};
            }
        }
    }
}

void Stacked_Sprites::Update(char direction, int x, int y, bool movex, bool movey)
{
    // Update the Stacked_Sprites' position based on the provided direction and movement flags.
    // angle += 2;
    if (movey == false)
    {
        if (direction == 'u')
        {
            if (y != 0)
                y_pos += game_speed;
        }
        else if (direction == 'd')
        {
            if (y != 3200)
                y_pos -= game_speed;
        }
    }
    if (movex == false)
    {
        if (direction == 'l')
        {
            if (x != 0)
                x_pos += game_speed;
        }
        else if (direction == 'r')
        {
            if (x != 4800)
                x_pos -= game_speed;
        }
    }
}
void Stacked_Sprites::Update(int speedx, int speedy, int hx, int hy)
{
    // Update the Stacked_Sprites' position based on the provided speed values.
    y_pos = y_pos - speedy;
    x_pos = x_pos - speedx;
    // Update(direction, x, y, movex, movey);
    Update(hx, hy);
}

void Stacked_Sprites::set_speed(int speed)
{
    // Set the game speed of the Stacked_Sprites.
    this->game_speed = speed;
}

void Stacked_Sprites::Rotate()
{
    // Rotate the Stacked_Sprites.
    angle += 2;
}

void Stacked_Sprites::Render()
{
    // Render the Stacked_Sprites.
    for (int i = 0; i < num_layers; i += step)
    {
        SDL_RenderCopyEx(renderer, texture, &srcRects[i], &moverRects[i], angle, NULL, flip);
    }
}

void Stacked_Sprites::Render(int x, int y)
{
    // Render the Stacked_Sprites only if the target coordinates are within a certain distance.
    float dist = shape->Distance(x_pos + moverRects[0].w / 2, y_pos + moverRects[0].h / 2, x, y);

    if (dist <= 1500)
    {
#pragma omp parallel for
        {
            for (int i = 0; i < num_layers; i += step)
            {
                SDL_RenderCopyEx(renderer, texture, &srcRects[i], &moverRects[i], angle, NULL, flip);
            }
        }
    }
    // shape->Draw_Line(renderer, x_pos+moverRects[0].w/2, y_pos+moverRects[0].h/2, x, y);
}
