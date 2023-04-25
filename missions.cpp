#include "missions.hpp"

Mission::Mission(SDL_Renderer* ren){
    isRunning = false;
    completed = false;
    timer = 0;
    renderer = ren;
}

void Mission::setStatus(bool val){
    isRunning = val;
}

void Mission::Update(){}

void Mission::Render(){}

void Mission::Running(){}