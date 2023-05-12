#pragma once
#include "Bullets.hpp"

class HandGunBullets : public Bullets
{
    private:
    public:
        HandGunBullets(const char *, SDL_Renderer *, int, int, char);
        ~HandGunBullets() {}
        void Update();
        void Update(char, int, int);
        void Render();
        void Fire(char);
        void Reset() {}
        SDL_Rect *getMoverRect();
        int getBulletSpeed();
        char getDirection();
};