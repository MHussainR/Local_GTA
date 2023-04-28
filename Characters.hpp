#pragma once
#include "GameObject.hpp"

class Characters : public GameObject
{
public:
    Characters(const char *, SDL_Renderer*, int, int);
    virtual void Update() = 0;
    // virtual void Update(char) = 0;
    virtual void Update(char, int, int) = 0;
    // virtual void Update(int, int, int) {};
    virtual void Render() = 0;
    virtual void Run(bool) = 0;
    virtual SDL_Rect *getMoverRect(){};
};