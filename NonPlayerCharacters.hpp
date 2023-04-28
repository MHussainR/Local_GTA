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
    int dx ;
    int dy ;
    char direction = 'd';
    void updateSpeed();

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
    SDL_Rect *getMoverRect();
    friend class Physics;
};