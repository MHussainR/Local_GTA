#pragma once
#include "game.hpp"

class GameObject{
    public:
        GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
        ~GameObject();

        virtual void Update();
        virtual void Render();
        SDL_Rect srcRect, moverRect;


    protected:
        int x_pos, y_pos;
        SDL_Texture* objTexture;
        // SDL_Rect srcRect, moverRect;
        SDL_Renderer* renderer;
};