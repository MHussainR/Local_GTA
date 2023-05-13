#include "TextureManager.hpp"
#include "Money.hpp"

Money::Money(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    font = new FontManager();
    money = 100;
    font->setFont("fonts/cuppajoe.regular.ttf");
    healthim1 = TextureManager::LoadTexture("assets/icons8-dollars-64.png", renderer);
    srcRect = {3, 2, 58, 60};
    mvrRect = {932, 50, 45, 45};
}

void Money::Render()
{

    SDL_RenderCopy(renderer, healthim1, &srcRect, &mvrRect);

    std::stringstream ss;
    ss << std::setw(8) << std::setfill('0') << money;
    std::string numberString = ss.str();
    font->renderText(renderer, ('$' + numberString).c_str(), 990, 55, 30, {108, 204, 156, 255});
}

void Money::setMoney(int money)
{
    if (money < 0)
    {
        this->money = 0;
    }
    else if (money > 99999999)
    {
        this->money = 99999999;
    }
    else
    {
        this->money = money;
    }
}

int Money::getMoney()
{
    return this->money;
}

Money::~Money()
{
    delete this->font;
    font = nullptr;
}

void Money::addMoney(int val)
{
    this->money += val;
}