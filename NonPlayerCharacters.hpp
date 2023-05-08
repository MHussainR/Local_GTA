#include "Characters.hpp"
#pragma once

class Physics;

class NonPlayerCharacters : public Characters
{
private:
    int frame;
    bool transition_from_up_movement, transition_from_right_movement, transition_from_left_movement, transition_from_down_movement;
    char previous_direction;
    int reference;
    int initial_dx, initial_dy;
    char initial_direction;
    int dx ;
    int dy ;
    char direction = 'd';
    

public:
    NonPlayerCharacters(const char *, SDL_Renderer *, int, int, char);
    void Update() override;
    void Update(char, int, int, bool, bool){};
    // void Update(int, int, int) override;
    void Update(char, int, int){};
    void Update(int, int);
    void Render() override;
    void Animator();
    void Run(bool) override;
    char getDirection();
    void setDirection(char);
    // void setSpeed(char);
    void updateSpeed(int);
    int getDX();
    int getDY();

    SDL_Rect *getMoverRect();
    friend class Physics;
};