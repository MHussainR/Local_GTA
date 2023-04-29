#pragma once
#include "game.hpp"
#include "GameObject.hpp"
// #include "Shapes.hpp"
#include<string>

class Physics;

class CarObject : public GameObject
{
    private:
        double angle;
        bool stolen;
        SDL_RendererFlip flip;
        int car_speed;
        SDL_Point pivot;
        int initial_dx = 0;
        int initial_dy = 0;
        char initial_direction = 'n';
        int dx = 0;
        int dy = 0;
        char direction = 'n';

        // Shapes* shape;

    public:
        CarObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, std::string type);
        CarObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
        void Update();
        // void Update(char direction, int x, int y, int map_pos_x, int map_pos_y);
        void Update(char direction, int x, int y, bool movex, bool movey);
        void Update(int, int);
        void Render(int x, int y);
        void Render();
        void Reset();
        // void draw_circle(SDL_Renderer*, int, int , int);
        // void load();
        // int frame = 0;
        bool getStatus();
        void setStatus(int x, int y);
        void setStatus(bool val);
        void set_speed(char);
        friend class Physics;
};