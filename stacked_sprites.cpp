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

Stacked_Sprites::~Stacked_Sprites(){
    delete shape;
}

void Stacked_Sprites::Update(int x, int y)
{

    float dist = shape->Distance(x_pos + moverRects[0].w / 2, y_pos + moverRects[0].h / 2, x, y);

    if (dist < 1500)
    {

        float theta = -(std::atan2((x_pos + moverRects[0].w / 2 - x), (y_pos + moverRects[0].h / 2 - y))) + M_PI_2;

        // float sin_theta = sin_map[theta];
        // float cos_theta = cos_map[theta];

        // if (sin_map[theta] == 0.0){
        //     sin_map.insert(std::pair<float, float>(theta, std::sin(theta)));
        //     // std::cout << std::sin(theta) << " " << sin_map[theta] <<'\n';
        //     // sin_theta = std::sin(theta);
        // }

        // if (cos_map[theta] == 0.0){
        //     cos_map.insert(std::pair<float, float>(theta, std::cos(theta)));
        //     cos_theta = std::cos(theta);
        // }

        // float sin_theta = sin_map[theta];
        // float cos_theta = cos_map[theta];

        float sin_theta = std::sin(theta);
        float cos_theta = std::cos(theta);

// std::cout << theta << " " << sin_theta << " " << sin_map[theta] << '\n';
        #pragma omp parallel for
        {
            for (int i = 0; i < num_layers; i += step)
            {
                moverRects[i] = {x_pos + int(i * delta * cos_theta), y_pos + int(i * delta * sin_theta), srcRects[i].w * scale, srcRects[i].h * scale};
            }
        }
    }
}

// void Stacked_Sprites::Update(int x, int y){
//     float theta  = -(std::atan2((x_pos + moverRects[0].w/2 - x),(y_pos + moverRects[0].h/2 - y))) + M_PI_2;

//     std::pair<float, float> key = std::make_pair(theta, delta);
//     if (memo.find(key) != memo.end()) {
//         for (int i = 0; i < num_layers; i+=step){
//             moverRects[i] = {x_pos+int(i*memo[key].first), y_pos+int(i*memo[key].second), srcRects[i].w*scale, srcRects[i].h*scale};
//         }
//     } else {
//         float sin_theta = std::sin(theta);
//         float cos_theta = std::cos(theta);

//         for (int i = 0; i < num_layers; i+=step){
//             moverRects[i] = {x_pos+int(i*delta*cos_theta), y_pos+int(i*delta*sin_theta), srcRects[i].w*scale, srcRects[i].h*scale};
//         }
//         memo[key] = std::make_pair(cos_theta, sin_theta);
//     }
// }

void Stacked_Sprites::Update(char direction, int x, int y, bool movex, bool movey)
{
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
    y_pos = y_pos - speedy;
    x_pos = x_pos - speedx;
    // Update(direction, x, y, movex, movey);
    Update(hx, hy);
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