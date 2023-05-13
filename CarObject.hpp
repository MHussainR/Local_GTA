#pragma once
#include "game.hpp"
#include "GameObject.hpp"
#include "Shapes.hpp"
#include "FontManager.hpp"
#include<string>

class Physics;
class Money;
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
        Shapes* shape;
        bool intersects;
        bool modification_state;
        std::string type;
        SDL_Texture* mod_bg;
        SDL_Rect mod_car_src, mod_car_move;
        FontManager* font;
        int mod_price;

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
        void Render(SDL_Rect rect);
        void Reset();
        void Rotation(int x, int y);
        void modification(Money * m);
        bool get_modification_state();
        void set_modification_state(bool);
        void modification_render();
        // void RotatePoint(SDL_Point& point, double rad);
        // void draw_circle(SDL_Renderer*, int, int , int);
        // void load();
        // int frame = 0;
        bool getStatus();
        void setStatus(int x, int y);
        void setStatus(bool val);
        void set_speed(char);
        friend class Physics;
};