#include "MainCharacter.hpp"
#include <iostream>

MainCharacter::MainCharacter(const char *textursheet, SDL_Renderer *ren, int x, int y) : Characters(textursheet, ren, x, y),
                                                                                         lFrame(0), rFrame(0), uFrame(0), dFrame(0),
                                                                                         transition_from_up_movement(false),
                                                                                         transition_from_right_movement(false),
                                                                                         transition_from_left_movement(false),
                                                                                         transition_from_down_movement(false),
                                                                                         previous_direction('i'),
                                                                                         reference(7)
{
    srcRect = {111, 52, 29, 49};
    moverRect = {600, 400, 30, 50};
}

void MainCharacter::Animator(char direction)
{
    if (direction == 'n')
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
        lFrame = 0;
        rFrame = 0;
        uFrame = 0;
        dFrame = 0;
    }

    else if (direction == 'r')
    {
        if (transition_from_up_movement)
        {
            transition_from_down_movement = false;
            if (rFrame == 0)
            {
                srcRect = {251, 0, 48, 50};
                rFrame++;
            }
            else if (rFrame == (reference))
            {
                srcRect = {404, 0, 46, 50};
                rFrame = 1;
                transition_from_up_movement = false;
            }
            else if (rFrame > (reference))
            {
                rFrame = 0;
            }
            else
            {
                rFrame++;
            }
        }

        else if (transition_from_down_movement)
        {
            transition_from_up_movement = false;
            if (rFrame == 0)
            {
                srcRect = {252, 100, 48, 48};
                rFrame++;
            }
            else if (rFrame == (reference))
            {
                srcRect = {401, 104, 49, 46};
                rFrame = 1;
                transition_from_down_movement = false;
            }
            else if (rFrame > (reference))
            {
                rFrame = 0;
            }
            else
            {
                rFrame++;
            }
        }

        else
        {
            if (rFrame == 0)
            {
                srcRect = {111, 52, 29, 49};
                rFrame++;
            }
            else if (rFrame == reference)
            {
                srcRect = {252, 51, 48, 50};
                rFrame++;
            }
            else if (rFrame == reference * 2)
            {
                GameObject::srcRect = {404, 52, 50, 50};
                rFrame = 1;
            }
            else if (rFrame > reference * 2)
            {
                rFrame = 1;
            }
            else
            {
                rFrame++;
            }
        }
    }

    else if (direction == 'l')
    {
        // std::cout << lFrame << std::endl;
        if (transition_from_up_movement)
        {
            transition_from_down_movement = false;
            if (lFrame == 0)
            {
                srcRect = {151, 0, 48, 50};
                lFrame++;
            }
            else if (lFrame == (reference))
            {
                srcRect = {300, 0, 49, 50};
                lFrame = 1;
                transition_from_up_movement = false;
            }
            else if (lFrame > (reference))
            {
                lFrame = 0;
            }
            else
            {
                lFrame++;
            }
        }

        else if (transition_from_down_movement)
        {
            transition_from_up_movement = false;
            if (lFrame == 0)
            {
                srcRect = {151, 103, 49, 47};
                lFrame++;
            }
            else if (lFrame == (reference))
            {
                srcRect = {303, 103, 45, 49};
                lFrame = 1;
                transition_from_down_movement = false;
            }
            else if (lFrame > (reference))
            {
                lFrame = 0;
            }
            else
            {
                lFrame++;
            }
        }

        else
        {
            if (lFrame == 0)
            {
                GameObject::srcRect = {12, 51, 29, 49};
                lFrame++;
            }
            else if (lFrame == reference)
            {
                srcRect = {155, 52, 38, 48};
                lFrame++;
            }
            else if (lFrame == reference * 2)
            {
                GameObject::srcRect = {303, 51, 45, 49};
                lFrame = 1;
            }
            else if (lFrame > reference * 2)
            {
                lFrame = 1;
            }
            else
            {
                lFrame++;
            }
        }
    }

    else if (direction == 'u')
    {
        if (transition_from_right_movement)
        {
            transition_from_left_movement = false;
            if (uFrame == 0)
            {
                srcRect = {251, 0, 48, 50};
                uFrame++;
            }
            else if (uFrame == (reference))
            {
                srcRect = {404, 0, 46, 50};
                uFrame = 1;
                transition_from_right_movement = false;
            }
            else if (uFrame > (reference))
            {
                uFrame = 0;
            }
            else
            {
                uFrame++;
            }
        }

        else if (transition_from_left_movement)
        {
            transition_from_right_movement = false;
            if (uFrame == 0)
            {
                srcRect = {151, 0, 48, 50};
                uFrame++;
            }
            else if (uFrame == (reference))
            {
                srcRect = {300, 0, 49, 50};
                uFrame = 1;
                transition_from_left_movement = false;
            }
            else if (uFrame > (reference))
            {
                uFrame = 0;
            }
            else
            {
                uFrame++;
            }
        }

        else
        {
            if (uFrame == 0)
            {
                GameObject::srcRect = {51, 13, 49, 29};
                uFrame++;
            }
            else if (uFrame == reference)
            {
                srcRect = {201, 4, 49, 38};
                uFrame++;
            }
            else if (uFrame == reference * 2)
            {
                GameObject::srcRect = {351, 3, 49, 37};
                uFrame = 1;
            }
            else if (uFrame > reference * 2)
            {
                uFrame = 1;
            }
            else
            {
                uFrame++;
            }
        }
    }

    else if (direction == 'd')
    {
        if (transition_from_right_movement)
        {
            transition_from_left_movement = false;
            if (dFrame == 0)
            {
                srcRect = {252, 100, 48, 48};
                dFrame++;
            }
            else if (dFrame == (reference))
            {
                srcRect = {401, 104, 49, 46};
                dFrame = 1;
                transition_from_right_movement = false;
            }
            else if (dFrame > (reference))
            {
                dFrame = 0;
            }
            else
            {
                dFrame++;
            }
        }

        else if (transition_from_left_movement)
        {
            transition_from_right_movement = false;
            if (dFrame == 0)
            {
                srcRect = {151, 103, 49, 47};
                dFrame++;
            }
            else if (dFrame == (reference))
            {
                srcRect = {303, 103, 45, 49};
                dFrame = 1;
                transition_from_left_movement = false;
            }
            else if (dFrame > (reference))
            {
                dFrame = 0;
            }
            else
            {
                dFrame++;
            }
        }

        else
        {
            if (dFrame == 0)
            {
                GameObject::srcRect = {51, 113, 49, 29};
                dFrame++;
            }
            else if (dFrame == reference)
            {
                srcRect = {201, 110, 49, 38};
                dFrame++;
            }
            else if (dFrame == reference * 2)
            {
                GameObject::srcRect = {351, 112, 49, 37};
                dFrame = 1;
            }
            else if (dFrame > reference * 2)
            {
                dFrame = 1;
            }
            else
            {
                dFrame++;
            }
        }
    }

}

void MainCharacter::Update()
{
    moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};
}

void MainCharacter::Update(char direction, int x, int y)
{
    if (this->previous_direction == 'i')
    {
        this->previous_direction = direction;
    }
    else
    {

        if (previous_direction == 'u')
        {
            transition_from_up_movement = true;
            switch (direction)
            {
            case 'l':
                lFrame = 0;
                break;
            case 'r':
                rFrame = 0;
                break;
            }
        }
        else if (previous_direction == 'r')
        {
            transition_from_right_movement = true;
            switch (direction)
            {
            case 'u':
                uFrame = 0;
                break;
            case 'd':
                dFrame = 0;
                break;
            }
        }
        else if (previous_direction == 'l')
        {
            transition_from_left_movement = true;
            transition_from_right_movement = false;
            switch (direction)
            {
            case 'u':
                uFrame = 0;
                break;
            case 'd':
                dFrame = 0;
                break;
            }
        }
        else if (previous_direction == 'd')
        {
            transition_from_up_movement = false;
            transition_from_down_movement = true;
            switch (direction)
            {
            case 'l':
                uFrame = 0;
                break;
            case 'r':
                dFrame = 0;
                break;
            }
        }
        if (direction!= 'n')
        {
            previous_direction = direction;
        }
    }

    Animator(direction);

    if (x <= 0)
    {
        if (x_pos <= 600)
        {
            inside_box_x = true;
        }
        else
        {
            if (direction == 'l')
            {
                x_pos -= 5;
                inside_box_x = true;
            }
            inside_box_x = false;
        }
    }

    if (x >= 4800)
    {
        if (x_pos >= 600)
        {
            inside_box_x = true;
        }
        else
        {
            if (direction == 'r')
            {
                x_pos += 5;
                inside_box_x = true;
            }
            inside_box_x = false;
        }
    }

    if (y <= 0)
    {
        if (y_pos <= 400)
        {
            inside_box_y = true;
        }
        else
        {
            if (direction == 'u')
            {
                y_pos -= 5;
                inside_box_y = true;
            }
            inside_box_y = false;
        }
    }

    if (y >= 3200)
    {
        if (y_pos >= 400)
        {
            inside_box_y = true;
        }
        else
        {
            if (direction == 'd')
            {
                y_pos += 5;
                inside_box_y = true;
            }
            inside_box_y = false;
        }
    }

    if (inside_box_y)
    {
        if (direction == 'u')
        {
            // if (y_pos != 400)
            y_pos -= 5;
            // std::cout << moverRect.y << std::endl;
        }
        else if (direction == 'd')
        {
            // if (y_pos != 3600)
            y_pos += 5;
        }
    }

    if (inside_box_x)
    {
        if (direction == 'l')
        {
            // if (x_pos != 600)
            x_pos -= 5;
        }
        else if (direction == 'r')
        {
            // if (x_pos <= 600)
            x_pos += 5;
        }
    }

    Update();
}

void MainCharacter::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &moverRect);
}

void MainCharacter::Run(bool runs)
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

SDL_Rect *MainCharacter::getMoverRect()
{
    return &moverRect;
}