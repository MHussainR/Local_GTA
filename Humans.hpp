#pragma once
#include "GameObject.hpp"

class Humans : public GameObject
{
public:
    Humans(const char *, SDL_Renderer*, int, int);
    virtual void Update() = 0;
    virtual void Render() = 0;
};