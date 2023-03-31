#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textursheet, SDL_Renderer* ren, int x, int y){
    renderer = ren;
    objTexture = TextureManager::LoadTexture(textursheet, ren);
    
    x_pos = x;
    y_pos = y;
}

void GameObject::Update()
{
    // x_pos++;
    // y_pos++;

    // srcRect = {771, 48, 136, 192};
    moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};

}

void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &moverRect);
}