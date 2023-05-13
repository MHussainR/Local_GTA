#pragma once
#include "GameObject.hpp"

class Guns: public GameObject
{
    private:
        int ammo;
        bool reload;
        bool fire;
        int frame;
        char direction;
        void Animator();
        void Reloader();

    public:
        Guns(const char *, SDL_Renderer *, int, int,char);
        void Update();
        void Update(char){};
        void Update(char, int, int);
        void Render();
        void Reset(){};
};