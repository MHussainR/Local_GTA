#pragma once
#include "SDL.h"
#include "Reaction.hpp"
#include <string>
#include <list>
// #include "mapobject.hpp"
// #include "NonPlayerCharacters.hpp"
// #include "MainCharacter.hpp"
// #include
class NonPlayerCharacters;
class MainCharacter;
class MapObject;
class Physics
{
private:
    // Reaction reaction;
    
public:
    void collisionHandler(std::list<NonPlayerCharacters*>, MapObject *);
    void collisionHandler(NonPlayerCharacters *, MapObject *);
    bool collisionHandler(MainCharacter *, MapObject *, int, int);
    bool collisionHandler(MainCharacter *, NonPlayerCharacters *, int, int);
    bool collisionDetector(SDL_Rect *, NonPlayerCharacters **){};
    void collisionHandler(std::list<NonPlayerCharacters *>, int, int);
    void takeAction(std::string){};
};
