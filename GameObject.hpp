#pragma once
#include "game.hpp"

class GameObject
{
public:
    GameObject(const char *texturesheet, SDL_Renderer *ren, int x, int y);
    ~GameObject();

    virtual void Update();
    virtual void Update(char);
    virtual void Update(char, int, int);
    virtual void Render();
    int getXpos();
    int getYpos();
    SDL_Rect srcRect, moverRect;
    bool inside_box_x, inside_box_y;

protected:
    int x_pos, y_pos;
    
    SDL_Texture *objTexture;
    // SDL_Rect srcRect, moverRect;
    SDL_Renderer *renderer;
};