#pragma once

#include "mapobject.hpp"

class SmallMapObject : public MapObject{

    private:
        SDL_Rect moverRect;
    public:
        SmallMapObject(const char *textursheet, SDL_Renderer *ren, int x, int y);
        void Render();
        void Update();
        void Update(char direction, bool movex, bool movey);
        void Update(char, bool, bool, int, int);
        void draw_black_rect(SDL_Renderer* renderer, int x, int y, int w, int h);
};