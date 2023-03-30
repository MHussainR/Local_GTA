#pragma once
#include "game.hpp"

class GameObject{
    public:
        GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
        ~GameObject();

        void Update();
        void Render();
        SDL_Rect srcRect, moverRect;


    private:
        int x_pos, y_pos;
        SDL_Texture* objTexture;
        // SDL_Rect srcRect, moverRect;
        SDL_Renderer* renderer;
};