#pragma once
#include "missions.hpp"
#include "CarObject.hpp"
#include "GameObject.hpp"
#include "FontManager.hpp"
#include "Shapes.hpp"
#include <SDL_ttf.h>
#include <string>

class TaxiMission : public Mission
{
private:
    CarObject *Taxi;
    SDL_RendererFlip flip1, flip2;
    int x_pos, y_pos;
    bool picked1, picked2;
    bool failed;
    SDL_Rect position;
    CarObject *passanger1;
    CarObject *passanger2;
    SDL_Texture *arrow;
    SDL_Point pivot;
    double arrow_angle, position_angle;
    SDL_Rect aSrcRect, aMoverRect, pSrcRect, pMoverRect;
    FontManager *font;
    FontManager *font1;
    Shapes* shape;

public:
    TaxiMission(SDL_Renderer *ren, int, int);
    ~TaxiMission();
    void Update(char direction, int x, int y, bool movex, bool movey);
    void Update(int, int);
    void Render(int x, int y, int x1, int y1);
    void check();
    void set_speed(int val);
    bool getStatus();
    void setStatus(int, int);
    void Running(int x, int y);
    void setSpeedP(int val);
    bool getState();
};