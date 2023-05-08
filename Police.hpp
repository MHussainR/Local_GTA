#pragma once
#include <map>
#include <vector>
#include <utility>
// #include "GameObject.hpp"
#include "NonPlayerCharacters.hpp"
#include "CoOrdinateSystem.hpp"
#include "mapobject.hpp"
// #include <vector>

class Police
{
    private: 
        NonPlayerCharacters *npc_police;
        int path[15][2] = {{2, 11}, {2, 12}, {2, 13}, {2, 14}, {2, 15}, {2, 16}, {2, 17}, {2, 18}, {2, 19}, {2, 20}, {2, 21}, {2, 22}, {2, 23}, {2, 24}, {2, 25}};
        int lengthpath = 15;
        int taken;
        bool follow = true;
        std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> data_of_neighbours;


    public:
        Police(CoOrdinateSystem *, SDL_Renderer *);
        // void Update(){};
        // void Update(char){};
        // void Update(char, int, int){};
        void Update(int, int);
        void Render();
        void followPath(MapObject *);
        // void Reset(){};
        // void Animator(){};
    // SDL_Rect *getMoverRect();
};