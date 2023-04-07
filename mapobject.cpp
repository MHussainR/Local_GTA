#include "mapobject.hpp"
#include "TextureManager.hpp"
#include<iostream>

MapObject::MapObject(const char *textursheet, SDL_Renderer *ren, int x, int y) : GameObject(textursheet, ren, x, y) {}
// renderer = ren;
// objTexture = TextureManager::LoadTexture(textursheet, ren);

// x_pos = x;
// y_pos = y;

void MapObject::Update(){
    srcRect = {x_pos, y_pos, 1200, 800};
}

void MapObject::Update(char direction)
{

    if (direction == 'u'){
        if (y_pos != 0)
            y_pos -= 5;
    } else if (direction == 'd'){
        if (y_pos != 3200)
            y_pos += 5;
    } else if (direction == 'l'){
        if (x_pos != 0)
            x_pos -= 5;
    } else if (direction == 'r'){
        if (x_pos != 4800)
            x_pos += 5;
    }
    // x_pos++;
    // y_pos++;

    // srcRect = {771, 48, 136, 192};
    srcRect = {x_pos, y_pos, 1200, 800};
    // moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};
}

void MapObject::Update(char direction, bool movex, bool movey){
    if (movey == false){
        if (direction == 'u'){
            if (y_pos != 0)
                y_pos -= 5;
        } else if (direction == 'd'){
            if (y_pos != 3200)
                y_pos += 5;
        }
    } 
    if (movex == false){
        if (direction == 'l'){
            if (x_pos != 0)
                x_pos -= 5;
        } else if (direction == 'r'){
            if (x_pos != 4800)
                x_pos += 5;
        }
    }
    // x_pos++;
    // y_pos++;
    // std::cout << x_pos << " " << y_pos << std::endl;

    // srcRect = {771, 48, 136, 192};
    srcRect = {x_pos, y_pos, 1200, 800};
    // moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};
}

void MapObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, NULL);
}

void MapObject::load(){
    if (frame <= 60){
        srcRect = {0, 0, 1200, 800};
        frame ++;
    } else if (frame <= 120){
        srcRect = {1200, 0, 1200, 800};
        frame ++;
    } else if (frame <= 180){
        srcRect = {0, 800, 1200, 800};
        frame ++;
    } else if (frame <= 240){
        srcRect = {1200, 800, 1200, 800};
        frame ++;
    } else if (frame <= 300){
        srcRect = {0, 1600, 1200, 800};
        frame ++;
    } else if  (frame <= 360){
        srcRect = {1200, 1600, 1200, 800};
        frame ++;
    } else {
        frame = 0;
    }

}