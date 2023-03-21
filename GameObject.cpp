#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textursheet, SDL_Renderer* ren){
    renderer = ren;
    objTexture = TextureManager::LoadTexture(textursheet, ren);

}

void GameObject::Update()
{
    x_pos = 0;
    y_pos = 0;

    srcRect = {771, 48, 136, 192};
    moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};

}

void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &moverRect);
}