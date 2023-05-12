#pragma once
// #include "game.hpp"
#include "FontManager.hpp"
#include "cheat_codes.hpp"
#include "CarObject.hpp"
#include <SDL_ttf.h>
#include <iomanip>

class Cheat_codes;
class Money
{
private:
    FontManager *font;
    int money;
    SDL_Texture *healthim1; //*healthim2, *healthim3, *healthim4, *healthim5, *healthim6, *healthim7, *healthim8, *healthim9, *healthim10, *healthim11;
    SDL_Renderer *renderer;
    SDL_Rect srcRect; // srcRect2, srcRect3, srcRect4, srcRect5, srcRect6, srcRect7, srcRect8, srcRect9, srcRect10, srcRect11;
    SDL_Rect mvrRect;

public:
    Money(SDL_Renderer *);
    void Render();
    void setMoney(int);
    int getMoney();
    void addMoney(int);
    void Reset(){};
    ~Money();
    friend class Cheat_codes;
    friend class CarObject;
};