#pragma once
#include "TextureManager.hpp"

class CircularMenu
{
    private:
        int number_of_guns;
        int radius;
        bool is_open;
        int centerY, centerX, NUM_GUNS;
        SDL_Renderer *renderer;
        SDL_Texture *menu_texture;
        SDL_Rect srcRect = {301,24,1033,1033}, moverRect = {0,0,550,550};
        double sectors;

    public:
        CircularMenu(SDL_Renderer *, int, int);
        void Render(double angle, int radius);
        void increaseGuns(){};
        int getNumberOfGuns(){};
        void setState(bool);
        bool getState();
};