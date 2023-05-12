#include "HandGunBullets.hpp"

HandGunBullets::HandGunBullets(const char *texturesheet, SDL_Renderer *ren, int x, int y, char direction) : Bullets(texturesheet, ren, x, y)
{
    dx = 0;
    dy = 0;
    bulletspeed = 8;

    if (direction == 'r' || direction == 'n' || direction == 'i')
        srcRect = {41, 11, 10, 5};
    else if (direction == 'l')
        srcRect = {25, 19, 11, 5};
    else if (direction == 'u')
        srcRect = {59, 43, 6, 10};
    else if (direction == 'd')
        srcRect = {10, 60, 6, 10};

    moverRect = {x, y, 20, 20};
    Fire(direction);
}

void HandGunBullets::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &moverRect);
}

void HandGunBullets::Update()
{
    moverRect = {x_pos, y_pos, 15, 15};
}

void HandGunBullets::Update(char direction, int speedx, int speedy)
{
    x_pos = x_pos - speedx + dx;
    y_pos = y_pos - speedy + dy;
    Update();
}

void HandGunBullets::Fire(char direction)
{
    if (direction == 'r' || direction == 'n')
    {
        this->dx = bulletspeed;
        this->dy = 0;
    }
    else if (direction == 'l')
    {
        this->dx = -bulletspeed;
        this->dy = 0;
    }
    else if (direction == 'u')
    {
        this->dy = -bulletspeed;
        this->dx = 0;
    }
    else if (direction == 'd')
    {
        this->dy = bulletspeed;
        this->dx = 0;
    }
}

SDL_Rect* HandGunBullets::getMoverRect()
{
    return &moverRect;
}

int HandGunBullets::getBulletSpeed()
{
    return this->bulletspeed;
}

char HandGunBullets::getDirection()
{
    return this->direction;
}