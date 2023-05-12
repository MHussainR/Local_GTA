#include "mapobject.hpp"
#include "TextureManager.hpp"
// #include <iostream>

MapObject::MapObject(const char *textursheet, SDL_Renderer *ren, int x, int y) : GameObject(textursheet, ren, x, y) {}
// renderer = ren;
// objTexture = TextureManager::LoadTexture(textursheet, ren);

// x_pos = x;
// y_pos = y;

void MapObject::Update()
{
    srcRect = {x_pos, y_pos, 1200, 800};
}

void MapObject::Update(char direction)
{

    if (direction == 'u')
    {
        if (y_pos != 0)
            y_pos += game_speed_y;
    }
    else if (direction == 'd')
    {
        if (y_pos != 3200)
            y_pos += game_speed_y;
    }
    else if (direction == 'l')
    {
        if (x_pos != 0)
            x_pos += game_speed_x;
    }
    else if (direction == 'r')
    {
        if (x_pos != 4800)
            x_pos += game_speed_x;
    }
    // x_pos++;
    // y_pos++;

    // srcRect = {771, 48, 136, 192};
    srcRect = {x_pos, y_pos, 1200, 800};
    // moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};
}

void MapObject::Update(char direction, bool movex, bool movey)
{
    // if (movey == false){
    //     if (direction == 'u'){
    //         if (y_pos != 0)
    //             y_pos -= game_speed_y;
    //     } else if (direction == 'd'){
    //         if (y_pos != 3200)
    //             y_pos += game_speed_y;
    //     }
    // }
    // if (movex == false){
    //     if (direction == 'l'){
    //         if (x_pos != 0)
    //             x_pos -= game_speed_x;
    //     } else if (direction == 'r'){
    //         if (x_pos != 4800)
    //             x_pos += game_speed_x;
    //     }
    // }
    // if (movey == false)
    // {
    if (direction == 'u')
    {
        if (y_pos + game_speed_y >= 0)
            y_pos += game_speed_y;
    }
    else if (direction == 'd')
    {
        if (y_pos + game_speed_y <= 3200)
            y_pos += game_speed_y;
    }
    // }
    // if (movex == false)
    // {
    if (direction == 'l')
    {
        if (x_pos + game_speed_x >= 0)
            x_pos += game_speed_x;
    }
    else if (direction == 'r')
    {
        if (x_pos + game_speed_x <= 4800)
            x_pos += game_speed_x;
    }
    // // }
    // x_pos++;
    // y_pos++;
    // std::cout << x_pos << " " << y_pos << std::endl;

    // srcRect = {771, 48, 136, 192};
    srcRect = {x_pos, y_pos, 1200, 800};
    // moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};
    // std::cout << x_pos << " " << y_pos << std::endl;
}

void MapObject::Update(char direction, bool movex, bool movey, int speedx, int speedy)
{
    this->game_speed_x = speedx;
    this->game_speed_y = speedy;
    if (direction != 'n')
    {
        Update(direction, movex, movey);
    }
    Update();
}

void MapObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, NULL);
}

void MapObject::load()
{
    if (frame <= 120)
    {
        srcRect = {0, 0, 1200, 800};
        frame++;
    }
    else if (frame <= 240)
    {
        srcRect = {1200, 0, 1200, 800};
        frame++;
    }
    else if (frame <= 360)
    {
        srcRect = {0, 800, 1200, 800};
        frame++;
    }
    else if (frame <= 480)
    {
        srcRect = {1200, 800, 1200, 800};
        frame++;
    }
    else if (frame <= 600)
    {
        srcRect = {0, 1600, 1200, 800};
        frame++;
    }
    else if (frame <= 720)
    {
        srcRect = {1200, 1600, 1200, 800};
        frame++;
    }
    else
    {
        frame = 0;
    }

    // if ((frame >= 50 && frame <= 60)| (frame >= 110 && frame <= 120) | (frame >= 170 && frame <= 180) | (frame >= 230 && frame <= 240) | (frame >= 290 && frame <= 300) | (frame >= 350 && frame <= 360)){
    //     SDL_SetTextureAlphaMod(objTexture, 128);
    // }
    // if ((frame >= 50 && frame <= 360) && (frame % 60 >= 0 && frame % 60 <= 10)) {
    //     SDL_SetTextureAlphaMod(objTexture, 128);
    // }
    if (frame >= 100 && frame <= 120)
    {
        SDL_SetTextureAlphaMod(objTexture, ((-12.75 * frame) + 1530));
    }

    if (frame >= 220 && frame <= 240)
    {
        SDL_SetTextureAlphaMod(objTexture, ((-12.75 * frame) + (1530 * 2)));
    }

    if (frame >= 340 && frame <= 360)
    {
        SDL_SetTextureAlphaMod(objTexture, ((-12.75 * frame) + (1530 * 3)));
    }

    if (frame >= 460 && frame <= 480)
    {
        SDL_SetTextureAlphaMod(objTexture, ((-12.75 * frame) + (1530 * 4)));
    }

    if (frame >= 580 && frame <= 600)
    {
        SDL_SetTextureAlphaMod(objTexture, ((-12.75 * frame) + (1530 * 5)));
    }

    if (frame >= 700 && frame <= 720)
    {
        SDL_SetTextureAlphaMod(objTexture, ((-12.75 * frame) + (1530 * 6)));
    }
    //////////////////////////
    if (frame >= 120 && frame <= 140)
    {
        SDL_SetTextureAlphaMod(objTexture, ((12.75 * frame) - 1530));
    }

    if (frame >= 240 && frame <= 260)
    {
        SDL_SetTextureAlphaMod(objTexture, ((12.75 * frame) - (1530 * 2)));
    }

    if (frame >= 360 && frame <= 380)
    {
        SDL_SetTextureAlphaMod(objTexture, ((12.75 * frame) - (1530 * 3)));
    }

    if (frame >= 480 && frame <= 500)
    {
        SDL_SetTextureAlphaMod(objTexture, ((12.75 * frame) - (1530 * 4)));
    }

    if (frame >= 600 && frame <= 620)
    {
        SDL_SetTextureAlphaMod(objTexture, ((12.75 * frame) - (1530 * 5)));
    }

    if (frame >= 720)
    {
        SDL_SetTextureAlphaMod(objTexture, ((12.75 * frame) - (1530 * 6)));
    }
    // if ((frame >= 40 && frame <= 60) ||
    //     (frame >= 100 && frame <= 120) ||
    //     (frame >= 160 && frame <= 180) ||
    //     (frame >= 220 && frame <= 240) ||
    //     (frame >= 280 && frame <= 300) ||
    //     (frame >= 340 && frame <= 360))  {

    //     int alpha_mod = ((-12.75 * frame) + (1530 * ((frame - 40) / 60)));
    //     SDL_SetTextureAlphaMod(objTexture, alpha_mod);
    //     std::cout << alpha_mod << std::endl;
    // }

    // if ((frame >= 60 && frame <= 80) ||
    //     (frame >= 120 && frame <= 140) ||
    //     (frame >= 180 && frame <= 200) ||
    //     (frame >= 240 && frame <= 260) ||
    //     (frame >= 300 && frame <= 320) ||
    //     (frame >= 360)) {

    //     int alpha_mod = ((12.75 * frame) - (1530 * ((frame - 50) / 60)));
    //     SDL_SetTextureAlphaMod(objTexture, alpha_mod);
    // }

    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void MapObject::Reset()
{
    x_pos = 0;
    y_pos = 0;
}

int *MapObject::getMapCoordinates()
{
    int co_ordinates[2];
    co_ordinates[0] = x_pos % 100;
    co_ordinates[1] = y_pos % 100;
    return co_ordinates;
}
int MapObject::getMapAllowance(int i, int j)
{
    return gameMap[j][i];
}

// int MapObject::get_gameSpeedx()
// {
//     return game_speed_x;
// }

// int MapObject::get_gameSpeedy()
// {
//     return game_speed_y;
// }

int MapObject::getSpeed()
{
    return game_speed;
}

void MapObject::set_speed(int val)
{

    game_speed = val;
}

void MapObject::death()
{
    static int frame = 0;
    if (frame >= 140)
        srcRect = {0, 0, 1200, 800};
    else
        srcRect = {0, 800, 1200, 800};
        frame++;
    if (frame==260)
    {
        death_state = true;
    }
}

bool MapObject::get_death_state()
{
    return death_state;
}