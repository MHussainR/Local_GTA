#include "Characters.hpp"

class MainCharacter : public Characters
{
    public:
        MainCharacter(const char *, SDL_Renderer *, int, int);
        void Update();
        // void Update(char);
        void Update(char, int, int);
        void Render();
        void Animator(char);

    private:
        int lFrame, rFrame, uFrame, dFrame;
        bool transition_from_up_movement, transition_from_right_movement, transition_from_left_movement, transition_from_down_movement;
};