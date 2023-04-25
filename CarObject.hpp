#pragma once
#include "game.hpp"
#include "GameObject.hpp"
// #include "Shapes.hpp"
#include<string>

class CarObject : public GameObject
{
    private:
        double angle;
        bool stolen;
        SDL_RendererFlip flip;
        int car_speed;
        SDL_Point pivot;
        // Shapes* shape;

    public:
        CarObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, std::string type);
        CarObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
        void Update();
        // void Update(char direction, int x, int y, int map_pos_x, int map_pos_y);
        void Update(char direction, int x, int y, bool movex, bool movey);
        void Render(int x, int y);
        void Render();
        void Reset();
        // void draw_circle(SDL_Renderer*, int, int , int);
        // void load();
        // int frame = 0;
        bool getStatus();
        void setStatus(int x, int y);
        void setStatus(bool val);
        void set_speed(int);
        
};