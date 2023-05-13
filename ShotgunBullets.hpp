#pragma once
#include "Bullets.hpp"

class ShotgunBullets : public Bullets
{
    private:
    public:
        ShotgunBullets(const char *, SDL_Renderer *, int, int, char);
        ~ShotgunBullets() {}
        void Update();
        void Update(char, int, int);
        void Render();
        void Fire(char);
        void Reset() {}
        SDL_Rect *getMoverRect();
        int getBulletSpeed();
        char getDirection();
        int time;
};