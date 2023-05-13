#pragma once
#include "game.hpp"
#include "GameObject.hpp"

class Bullets: public GameObject
{
    protected:
        int dx;
        int dy;
        char direction;
        bool reloading;
        int bulletspeed;

    public:
        Bullets(const char *texturesheet, SDL_Renderer *ren, int x, int y);
        virtual void Update() = 0;
        void Update(char){};
        virtual void Update(char, int, int) = 0;
        virtual void Render() = 0;
        virtual void Reset() = 0;
        virtual void Fire(char) = 0;
        virtual ~Bullets(){}
        virtual SDL_Rect *getMoverRect() = 0;
        virtual char getDirection() = 0;
        virtual int getBulletSpeed() = 0;
};
