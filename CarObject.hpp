#pragma once
#include "game.hpp"
#include "GameObject.hpp"
#include<string.h>

class CarObject : public GameObject
{
    private:
        double angle;
        bool stolen;
        SDL_RendererFlip flip;
        int car_speed;

    public:
        CarObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
        void Update();
        // void Update(char direction, int x, int y, int map_pos_x, int map_pos_y);
        void Update(char direction, int x, int y, bool movex, bool movey);
        void Render();
        void Reset();
        void draw_circle(SDL_Renderer*, int, int , int);
        // void load();
        // int frame = 0;
        bool getStatus();
        void setStatus(int x, int y);
        void set_speed(int);
        
};