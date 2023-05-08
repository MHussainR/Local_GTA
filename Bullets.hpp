#pragma once
#include "game.hpp"
#include "GameObject.hpp"

class Bullets: public GameObject
{
    private:

    public:
        Bullets(const char *texturesheet, SDL_Renderer *ren, int x, int y);
        Bullets(const char *texturesheet, SDL_Renderer *ren, int x, int y, std::string type);
        void Update(){};
        void Update(char){};
        void Update(char, int, int){};
        void Render(){};
        void Reset(){};
};
