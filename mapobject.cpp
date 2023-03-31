#include "mapobject.hpp"
#include "TextureManager.hpp"

MapObject::MapObject(const char* textursheet, SDL_Renderer* ren, int x, int y):GameObject(textursheet, ren, x, y){}
    // renderer = ren;
    // objTexture = TextureManager::LoadTexture(textursheet, ren);
    
    // x_pos = x;
    // y_pos = y;


void MapObject::Update()
{
    x_pos++;
    y_pos++;

    // srcRect = {771, 48, 136, 192};
    srcRect = {x_pos, y_pos, 1200, 800};
    // moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};

}

void MapObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, NULL);
}