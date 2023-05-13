#include "Guns.hpp"

Guns::Guns(const char *texturesheet, SDL_Renderer *renderer, int x, int y, char characterDirection) : GameObject(texturesheet, renderer, x, y), frame(0), ammo(1000),
                                                                                                      direction(characterDirection)
{
    srcRect = {1256, 130, 83, 28};
    moverRect = {x,y,40,40};
}

void Guns::Animator()
{
   
}

void Guns::Reloader()
{

}

void Guns::Update()
{
    moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};
}

void Guns::Update(char direction, int speedx, int speedy)
{
    // x_pos = x_pos - speedx;
    // y_pos = y_pos - speedy;
    Update();
}

void Guns::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &moverRect);
}