#pragma once
#include "game.hpp"
// #include "GameObject.hpp"

class Shapes
{
private:
public:
    Shapes();
    void Draw_circle(SDL_Renderer *, int, int, int);
    void Draw_Line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
    float Distance(float x1, float y1, float x2, float y2);
    void draw_rect(SDL_Renderer *renderer, int x, int y, int w, int h);
};