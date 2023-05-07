#pragma once
// #include "game.hpp"
#include "FontManager.hpp"
#include <SDL_ttf.h>

class Health
{
    private:
        FontManager *font;
        int health;
        SDL_Texture *healthim1; //*healthim2, *healthim3, *healthim4, *healthim5, *healthim6, *healthim7, *healthim8, *healthim9, *healthim10, *healthim11;
        SDL_Texture *healthim2;
        SDL_Renderer *renderer;
        SDL_Rect srcRect1[8]; // srcRect2, srcRect3, srcRect4, srcRect5, srcRect6, srcRect7, srcRect8, srcRect9, srcRect10, srcRect11;
        SDL_Rect mvrRect[15];
        SDL_Rect bar[37];

    public:
        Health(SDL_Renderer *);
        void Render();
        void setHealth(int);
        int getHealth();
        void Reset(){};
        ~Health();
};