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
class CarObject;

class Physics
{
private:
    // Reaction reaction;

public:
    bool collisionHandler(MainCharacter *, MapObject *, int, int);
    bool collisionHandler(MainCharacter *, NonPlayerCharacters *, int, int);
    bool collisionHandler(MainCharacter *, std::list<NonPlayerCharacters *>, int, int);
    bool collisionHandler(MainCharacter *, CarObject *, MapObject *, int, int);
    bool collisionHandler(MainCharacter *, std::list<CarObject *>, MapObject*, int, int);

    void collisionHandler(std::list<NonPlayerCharacters *>, MapObject *);
    void collisionHandler(std::list<NonPlayerCharacters *>, int, int);
    void collisionHandler(NonPlayerCharacters *, MapObject *);

    void takeAction(std::string){};
};
