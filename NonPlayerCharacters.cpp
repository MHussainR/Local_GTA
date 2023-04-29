#include "NonPlayerCharacters.hpp"

void NonPlayerCharacters::updateSpeed()
{
    switch (this->direction)
    {
    case 'l':
        this->dx = -1;
        this->dy = 0;
        break;
    case 'r':
        this->dx = 1;
        this->dy = 0;
        break;
    case 'u':
        this->dx = 0;
        this->dy = -1;
        break;
    case 'd':
        this->dx = 0;
        this->dy = 1;
        break;
    case 'n':
        this->dx = 0;
        this->dy = 0;
        break;
    }
    this->initial_dx = dx;
    this->initial_dy = dy;
}


NonPlayerCharacters::NonPlayerCharacters(const char *textursheet, SDL_Renderer *ren, int x, int y, char d) : Characters(textursheet, ren, x, y), frame(0), reference(25)
{
    // char randomSelect[6] = "lrudn";
    // this->direction = randomSelect[rand() % 5];
    this->initial_direction = d;
    this->previous_direction = d;
    this->direction = d;
    updateSpeed();
    srcRect = {111, 52, 29, 49};
    moverRect = {x, y, 30, 50};
}



void NonPlayerCharacters::Update()
{
    moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};
}

void NonPlayerCharacters::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &moverRect);
}

void NonPlayerCharacters::Animator()
{

    if (this->direction == 'n')
    {
        if (this->previous_direction == 'r')
        {
            srcRect = {111, 52, 29, 49};
        }
        else if (this->previous_direction == 'l')
        {
            srcRect = {12, 51, 29, 49};
        }
        else if (this->previous_direction == 'u')
        {
            srcRect = {51, 13, 49, 29};
        }
        else if (this->previous_direction == 'd')
        {
            srcRect = {51, 113, 49, 29};
        }
        frame = 0;
    }
    else if (this->direction == 'r')
    {
        if (frame == 0)
        {
            srcRect = {111, 52, 29, 49};
            frame++;
        }
        else if (frame == reference)
        {
            srcRect = {252, 51, 48, 50};
            frame++;
        }
        else if (frame == reference * 2)
        {
            GameObject::srcRect = {404, 52, 50, 50};
            frame = 1;
        }
        else
        {
            frame++;
        }
    }

    else if (this->direction == 'l')
    {
        if (frame == 0)
        {
            GameObject::srcRect = {12, 51, 29, 49};
            frame++;
        }
        else if (frame == reference)
        {
            srcRect = {155, 52, 38, 48};
            frame++;
        }
        else if (frame == reference * 2)
        {
            GameObject::srcRect = {303, 51, 45, 49};
            frame = 1;
        }
        else
        {
            frame++;
        }
    }

    else if (this->direction == 'u')
    {
        if (frame == 0)
        {
            GameObject::srcRect = {51, 13, 49, 29};
            frame++;
        }
        else if (frame == reference)
        {
            srcRect = {201, 4, 49, 38};
            frame++;
        }
        else if (frame == reference * 2)
        {
            GameObject::srcRect = {351, 3, 49, 37};
            frame = 1;
        }
        else
        {
            frame++;
        }
    }

    else if (this->direction == 'd')
    {
        if (frame == 0)
        {
            GameObject::srcRect = {51, 113, 49, 29};
            frame++;
        }
        else if (frame == reference)
        {
            srcRect = {201, 110, 49, 38};
            frame++;
        }
        else if (frame == reference * 2)
        {
            GameObject::srcRect = {351, 112, 49, 37};
            frame = 1;
        }
        else
        {
            frame++;
        }
    }

    // if (direction == 'r')
    // {
    //     if (transition_from_up_movement)
    //     {
    //         transition_from_down_movement = false;
    //         if (rFrame == 0)
    //         {
    //             srcRect = {251, 0, 48, 50};
    //             rFrame++;
    //         }
    //         else if (rFrame == (reference))
    //         {
    //             srcRect = {404, 0, 46, 50};
    //             rFrame = 1;
    //             transition_from_up_movement = false;
    //         }
    //         else if (rFrame > (reference))
    //         {
    //             rFrame = 0;
    //         }
    //         else
    //         {
    //             rFrame++;
    //         }
    //     }

    //     else if (transition_from_down_movement)
    //     {
    //         transition_from_up_movement = false;
    //         if (rFrame == 0)
    //         {
    //             srcRect = {252, 100, 48, 48};
    //             rFrame++;
    //         }
    //         else if (rFrame == (reference))
    //         {
    //             srcRect = {401, 104, 49, 46};
    //             rFrame = 1;
    //             transition_from_down_movement = false;
    //         }
    //         else if (rFrame > (reference))
    //         {
    //             rFrame = 0;
    //         }
    //         else
    //         {
    //             rFrame++;
    //         }
    //     }

    //     else
    //     {
    //         if (rFrame == 0)
    //         {
    //             srcRect = {111, 52, 29, 49};
    //             rFrame++;
    //         }
    //         else if (rFrame == reference)
    //         {
    //             srcRect = {252, 51, 48, 50};
    //             rFrame++;
    //         }
    //         else if (rFrame == reference * 2)
    //         {
    //             GameObject::srcRect = {404, 52, 50, 50};
    //             rFrame = 1;
    //         }
    //         else if (rFrame > reference * 2)
    //         {
    //             rFrame = 1;
    //         }
    //         else
    //         {
    //             rFrame++;
    //         }
    //     }
    // }

    // else if (direction == 'l')
    // {
    //     std::cout << lFrame << std::endl;
    //     if (transition_from_up_movement)
    //     {
    //         transition_from_down_movement = false;
    //         if (lFrame == 0)
    //         {
    //             srcRect = {151, 0, 48, 50};
    //             lFrame++;
    //         }
    //         else if (lFrame == (reference))
    //         {
    //             srcRect = {300, 0, 49, 50};
    //             lFrame = 1;
    //             transition_from_up_movement = false;
    //         }
    //         else if (lFrame > (reference))
    //         {
    //             lFrame = 0;
    //         }
    //         else
    //         {
    //             lFrame++;
    //         }
    //     }

    //     else if (transition_from_down_movement)
    //     {
    //         transition_from_up_movement = false;
    //         if (lFrame == 0)
    //         {
    //             srcRect = {151, 103, 49, 47};
    //             lFrame++;
    //         }
    //         else if (lFrame == (reference))
    //         {
    //             srcRect = {303, 103, 45, 49};
    //             lFrame = 1;
    //             transition_from_down_movement = false;
    //         }
    //         else if (lFrame > (reference))
    //         {
    //             lFrame = 0;
    //         }
    //         else
    //         {
    //             lFrame++;
    //         }
    //     }

    //     else
    //     {
    //         if (lFrame == 0)
    //         {
    //             GameObject::srcRect = {12, 51, 29, 49};
    //             lFrame++;
    //         }
    //         else if (lFrame == reference)
    //         {
    //             srcRect = {155, 52, 38, 48};
    //             lFrame++;
    //         }
    //         else if (lFrame == reference * 2)
    //         {
    //             GameObject::srcRect = {303, 51, 45, 49};
    //             lFrame = 1;
    //         }
    //         else if (lFrame > reference * 2)
    //         {
    //             lFrame = 1;
    //         }
    //         else
    //         {
    //             lFrame++;
    //         }
    //     }
    // }

    // else if (direction == 'u')
    // {
    //     if (transition_from_right_movement)
    //     {
    //         transition_from_left_movement = false;
    //         if (uFrame == 0)
    //         {
    //             srcRect = {251, 0, 48, 50};
    //             uFrame++;
    //         }
    //         else if (uFrame == (reference))
    //         {
    //             srcRect = {404, 0, 46, 50};
    //             uFrame = 1;
    //             transition_from_right_movement = false;
    //         }
    //         else if (uFrame > (reference))
    //         {
    //             uFrame = 0;
    //         }
    //         else
    //         {
    //             uFrame++;
    //         }
    //     }

    //     else if (transition_from_left_movement)
    //     {
    //         transition_from_right_movement = false;
    //         if (uFrame == 0)
    //         {
    //             srcRect = {151, 0, 48, 50};
    //             uFrame++;
    //         }
    //         else if (uFrame == (reference))
    //         {
    //             srcRect = {300, 0, 49, 50};
    //             uFrame = 1;
    //             transition_from_left_movement = false;
    //         }
    //         else if (uFrame > (reference))
    //         {
    //             uFrame = 0;
    //         }
    //         else
    //         {
    //             uFrame++;
    //         }
    //     }

    //     else
    //     {
    // if (uFrame == 0)
    // {
    //     GameObject::srcRect = {51, 13, 49, 29};
    //     uFrame++;
    // }
    // else if (uFrame == reference)
    // {
    //     srcRect = {201, 4, 49, 38};
    //     uFrame++;
    // }
    // else if (uFrame == reference * 2)
    // {
    //     GameObject::srcRect = {351, 3, 49, 37};
    //     uFrame = 1;
    // }
    // else if (uFrame > reference * 2)
    // {
    //     uFrame = 1;
    // }
    // else
    // {
    //     uFrame++;
    // }
    //     }
    // }

    // else if (direction == 'd')
    // {
    //     if (transition_from_right_movement)
    //     {
    //         transition_from_left_movement = false;
    //         if (dFrame == 0)
    //         {
    //             srcRect = {252, 100, 48, 48};
    //             dFrame++;
    //         }
    //         else if (dFrame == (reference))
    //         {
    //             srcRect = {401, 104, 49, 46};
    //             dFrame = 1;
    //             transition_from_right_movement = false;
    //         }
    //         else if (dFrame > (reference))
    //         {
    //             dFrame = 0;
    //         }
    //         else
    //         {
    //             dFrame++;
    //         }
    //     }

    //     else if (transition_from_left_movement)
    //     {
    //         transition_from_right_movement = false;
    //         if (dFrame == 0)
    //         {
    //             srcRect = {151, 103, 49, 47};
    //             dFrame++;
    //         }
    //         else if (dFrame == (reference))
    //         {
    //             srcRect = {303, 103, 45, 49};
    //             dFrame = 1;
    //             transition_from_left_movement = false;
    //         }
    //         else if (dFrame > (reference))
    //         {
    //             dFrame = 0;
    //         }
    //         else
    //         {
    //             dFrame++;
    //         }
    //     }

    //     else
    //     {
    // if (dFrame == 0)
    // {
    //     GameObject::srcRect = {51, 113, 49, 29};
    //     dFrame++;
    // }
    // else if (dFrame == reference)
    // {
    //     srcRect = {201, 110, 49, 38};
    //     dFrame++;
    // }
    // else if (dFrame == reference * 2)
    // {
    //     GameObject::srcRect = {351, 112, 49, 37};
    //     dFrame = 1;
    // }
    // else if (dFrame > reference * 2)
    // {
    //     dFrame = 1;
    // }
    // else
    // {
    //     dFrame++;
    // }
    //     }
    // }
}

void NonPlayerCharacters::Update(int speed_x, int speed_y)
{
    // updateSpeed();

    if (this->direction == 'n')
    {
        y_pos = y_pos - speed_y;
        x_pos = x_pos - speed_x;
    }
    else if (this->direction == 'l' || this->direction == 'r')
    {
        y_pos = y_pos - speed_y;
        x_pos = x_pos - speed_x + this->dx;
    }
    else if (this->direction == 'u' || this->direction == 'd')
    {
        y_pos = y_pos - speed_y + this->dy;
        x_pos = x_pos - speed_x;
    }
    Animator();
    Update();
}

void NonPlayerCharacters::Run(bool runs)
{
    if (runs)
    {
        reference = 4;
    }
    else
    {
        reference = 7;
    }
}

SDL_Rect *NonPlayerCharacters::getMoverRect()
{
    return &moverRect;
}