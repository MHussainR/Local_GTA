#pragma once
#include "game.hpp"
#include "GameObject.hpp"
#include<string.h>

class CarObject : public GameObject
{
    private:
        double angle;
        bool stolen;

    public:
        CarObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
        void Update();
        // void Update(char direction);
        void Update(char direction, int x, int y);
        void Render();
        // void load();
        // int frame = 0;
        
};