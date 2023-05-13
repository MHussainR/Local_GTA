#pragma once
#include "Bullets.hpp"

class ARBullets : public Bullets
{
    private:

    public:
        ARBullets(const char *, SDL_Renderer *, int, int, char);
        ~ARBullets(){}
        void Update();
        void Update(char, int, int);
        void Render();
        void Fire(char);
        void Reset(){}
        SDL_Rect *getMoverRect();
        int getBulletSpeed();
        char getDirection();
        int time;
};