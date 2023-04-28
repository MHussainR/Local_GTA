#include "stacked_sprites.hpp"
#include "Shapes.hpp"
#include <cmath>

Stacked_Sprites::Stacked_Sprites(const char *textursheet, SDL_Renderer *ren, int x, int y, int srcx, int srcy, int srcw, int srch, int nl, int step, int delt, int scal)
{
    texture = TextureManager::LoadTexture(textursheet, ren);
    x_pos = x;
    y_pos = y;
    game_speed = 2;
    scale = scal;
    num_layers = nl;
    this->step = step;
    for (int i = 0; i < num_layers; i += step)
    {
        srcRects[i] = {srcx, srcy * (num_layers - i - 1), srcw, srch};
        moverRects[i] = {x_pos, y_pos + (i * 4), srcRects[i].w * scale, srcRects[i].h * scale};
    }
    renderer = ren;
    angle = 0;
    flip = SDL_FLIP_NONE;
    shape = new Shapes();
    delta = delt;
}

void Stacked_Sprites::Update(int x, int y)
{
    float theta = -(std::atan2((x_pos + moverRects[0].w / 2 - x), (y_pos + moverRects[0].h / 2 - y))) + M_PI_2;

    float sin_theta = std::sin(theta);
    float cos_theta = std::cos(theta);

    for (int i = 0; i < num_layers; i += step)
    {
        moverRects[i] = {x_pos + int(i * delta * cos_theta), y_pos + int(i * delta * sin_theta), srcRects[i].w * scale, srcRects[i].h * scale};
    }
}

void Stacked_Sprites::Update(char direction, int x, int y, bool movex, bool movey)
{
    // angle += 2;
    if (movey == false)
    {
        if (direction == 'u')
        {
            if (y != 0)
                y_pos += game_speed_y;
        }
        else if (direction == 'd')
        {
            if (y != 3200)
                y_pos += game_speed_y;
        }
    }
    if (movex == false)
    {
        if (direction == 'l')
        {
            if (x != 0)
                x_pos += game_speed_x;
        }
        else if (direction == 'r')
        {
            if (x != 4800)
                x_pos += game_speed_x;
        }
    }
}

void Stacked_Sprites::Update(int speedx, int speedy, int hx, int hy)
{
    y_pos = y_pos - speedy;
    x_pos = x_pos - speedx;
    // Update(direction, x, y, movex, movey);
    Update(hx,hy);
}

void Stacked_Sprites::set_speed(int speed)
{
    this->game_speed = speed;
}

void Stacked_Sprites::Rotate()
{
    angle += 2;
}

void Stacked_Sprites::Render()
{
    for (int i = 0; i < num_layers; i += step)
    {
        SDL_RenderCopyEx(renderer, texture, &srcRects[i], &moverRects[i], angle, NULL, flip);
    }
}

void Stacked_Sprites::Render(int x, int y)
{
    float dist = shape->Distance(x_pos, y_pos, x, y);

    if (dist <= 2000)
    {
        for (int i = 0; i < num_layers; i += step)
        {
            SDL_RenderCopyEx(renderer, texture, &srcRects[i], &moverRects[i], angle, NULL, flip);
        }
    }
    // shape->Draw_Line(renderer, x_pos+moverRects[0].w/2, y_pos+moverRects[0].h/2, x, y);
}