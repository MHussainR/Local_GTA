#include "Characters.hpp"

class MainCharacter : public Characters
{
    public:
        MainCharacter(const char *, SDL_Renderer *, int, int);
        void Update() override;
        // void Update(char);
        void Update(char, int, int) override;
        void Render() override;
        void Animator(char) ;
        void Run(bool) override;

    private:
        int lFrame, rFrame, uFrame, dFrame;
        bool transition_from_up_movement, transition_from_right_movement, transition_from_left_movement, transition_from_down_movement;
        char previous_direction;
        int reference;
};