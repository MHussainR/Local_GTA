#include "NonPlayerCharacters.hpp"

void NonPlayerCharacters::updateSpeed(int speed)
{
    switch (this->direction)
    {
    case 'l':
        this->dx = -speed;
        this->dy = 0;
        break;
    case 'r':
        this->dx = speed;
        this->dy = 0;
        break;
    case 'u':
        this->dx = 0;
        this->dy = -speed;
        break;
    case 'd':
        this->dx = 0;
        this->dy = speed;
        break;
    case 'n':
        this->dx = 0;
        this->dy = 0;
        break;
    }
    this->initial_dx = dx;
    this->initial_dy = dy;
}


NonPlayerCharacters::NonPlayerCharacters(const char *textursheet, SDL_Renderer *ren, int x, int y, char d) : Characters(textursheet, ren, x, y), frame(0), reference(20),death(false)
{
    // char randomSelect[6] = "lrudn";
    // this->direction = randomSelect[rand() % 5];
    this->initial_direction = d;
    this->previous_direction = d;
    this->direction = d;
    updateSpeed(1);
    srcRect = {111, 52, 29, 49};
    moverRect = {x, y, 30, 50};
}



void NonPlayerCharacters::Update()
{
    moverRect = {x_pos, y_pos, srcRect.w/2, srcRect.h/2};
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
            srcRect = {1217, 655, 69, 101};
        }
        else if (this->previous_direction == 'l')
        {
            srcRect = {847, 300, 69, 101};
        }
        else if (this->previous_direction == 'u')
        {
            srcRect = {73, 264, 101, 70};
        }
        else if (this->previous_direction == 'd')
        {
            srcRect = {499, 814, 101, 70};
        }
        frame = 0;
    }
    else if (this->direction == 'r')
    {
        if (frame == 0)
        {
            srcRect = {1217, 655, 69, 101};
            // srcRect = {1007, 645, 135, 95};
            frame++;
        }
        else if (frame == reference)
        {
            srcRect = {1165, 788, 121, 104};
            // srcRect = {1007, 645, 135, 95};
            frame++;
        }
        else if (frame == reference*2)
        {
            srcRect = {1007, 645, 135, 95};
            // srcRect = {831, 645, 120, 104};
            frame++;
        }
        else if (frame == reference * 3)
        {
            srcRect = {1217, 655, 69, 101};
            frame++;
        }
        else if (frame == reference *4)
        {
            srcRect = {831, 645, 120, 104};
            frame++;
        }
        else if (frame == reference *5)
        {
            srcRect = {844, 797, 136, 95};
            frame++;
        }
        else if (frame == reference *6)
        {
            frame = 0;
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
            GameObject::srcRect = {816, 442, 136, 95};
            frame++;
        }
        else if (frame == reference)
        {
            srcRect = {847, 300, 69, 101};
            frame++;
        }
        else if (frame == reference * 2)
        {
            GameObject::srcRect = {979, 290, 135, 95};
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
            GameObject::srcRect = {63, 408, 95, 136};
            frame++;
        }
        else if (frame == reference)
        {
            srcRect = {73, 264, 101, 70};
            frame++;
        }
        else if (frame == reference * 2)
        {
            GameObject::srcRect = {215, 571, 95, 136};
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
            GameObject::srcRect = {515, 604, 95, 136};
            frame++;
        }
        else if (frame == reference)
        {
            srcRect = {499, 814, 101, 70};
            frame++;
        }
        else if (frame == reference * 2)
        {
            GameObject::srcRect = {363, 441, 95, 136};
            frame = 1;
        }
        else
        {
            frame++;
        }
    }

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

char NonPlayerCharacters::getDirection(){
    return this->direction;
}

void NonPlayerCharacters::setDirection(char direction)
{
    this->direction = direction;
    updateSpeed(5);
}

int NonPlayerCharacters::getDX()
{
    return this->dx;
}

int NonPlayerCharacters::getDY()
{
    return this->dy;
}

void NonPlayerCharacters::reduceHealth(int min)
{
    if (health - min >=0)
    {
        health -= min;
    }
    else 
    {
        health = 0;
    }
}