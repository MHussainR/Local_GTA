#pragma once

#include "TextureManager.hpp"
#include "game.hpp"
#include "Shapes.hpp"
#include <map>
#include <vector>

class Stacked_Sprites
{
    private:
        SDL_Texture *texture;
        SDL_Renderer *renderer;
        SDL_Rect srcRects[20], moverRects[20];
        int angle;
        SDL_RendererFlip flip;
        int x_pos, y_pos, game_speed;
        Shapes *shape;
        int delta;
        int scale;
        int num_layers;
        int step;
        int game_speed_x, game_speed_y;
        std::map<float, float> sin_map;
        std::map<float, float> cos_map;
        // std::map<std::pair<float, float>, std::pair<float, float>> memo;

    public:
        Stacked_Sprites(const char *textursheet, SDL_Renderer *ren, int x, int y, int srcx, int srcy, int srcw, int srch, int ang, int nl, int step, int delt, int scale);
        ~Stacked_Sprites();
        void Update(char direction, int x, int y, bool movex, bool movey);
        void Update(int x, int y);
        void Update(int, int, int, int);
        void Rotate();
        void Render();
        void Render(int, int);
        void set_speed(int speed);
};