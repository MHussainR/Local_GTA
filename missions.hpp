#pragma once

#include "game.hpp"

class Mission{
    protected:
        bool isRunning;
        bool completed;
        int timer;
        SDL_Renderer* renderer;
    public:
        Mission(SDL_Renderer* ren);
        virtual void check() = 0;
        virtual void Running();
        void setStatus(bool);
        virtual void Update();
        virtual void Render();

};