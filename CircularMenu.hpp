#pragma once
#include "TextureManager.hpp"
#include <vector>

class CircularMenu
{
    private:
        int number_of_guns;
        int radius;
        bool is_open;
        int centerY, centerX, NUM_GUNS;
        SDL_Renderer *renderer;
        SDL_Texture *menu_texture;
        SDL_Texture *glow;
        SDL_Rect srcRect = {301,24,1033,1033}, moverRect = {0,0,550,550};
        SDL_Rect srcRect2 = {301, 24, 1033, 1033}, moverRect2 = {0, 0, 1200, 1200};
        double sectors;
        SDL_Texture* ar;
        SDL_Rect moverAR = {};
        SDL_Rect moverHG = {};
        SDL_Rect moverSG = {};
        SDL_Rect moverMid = {};
        SDL_Texture *hg;
        SDL_Texture *sg;
        SDL_Texture *mid;
        SDL_Rect srcRect3 = {};
        

    public:
        CircularMenu(SDL_Renderer *, int, int);
        void Render(double angle, int radius);
        void increaseGuns(){};
        int getNumberOfGuns(){};
        void setState(bool);
        bool getState();
        std::string getGun(double, int);
        
};