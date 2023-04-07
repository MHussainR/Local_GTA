#pragma once
#include "game.hpp"
#include "GameObject.hpp"
#include<string.h>

class MapObject : public GameObject
{

    public:
        MapObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
        void Update();
        void Update(char direction);
        void Update(char direction, bool movex, bool movey);
        void Render();
        void load();
        int frame = 0;
};

// class MapObject{
//     public:
//         MapObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
//         ~MapObject();

//         void Update();
//         void Render();
//         SDL_Rect srcRect, moverRect;

//     private:
//         int x_pos, y_pos;
//         SDL_Texture* objTexture;
//         // SDL_Rect srcRect, moverRect;
//         SDL_Renderer* renderer;
// };