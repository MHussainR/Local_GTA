#pragma once
#include "game.hpp"
#include "GameObject.hpp"

class MapObject : public GameObject
{

public:
    MapObject(const char *texturesheet, SDL_Renderer *ren, int x, int y);
    void Update();
    void Render();
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