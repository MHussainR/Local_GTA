#include "TextureManager.hpp"
#include "Health.hpp"

Health::Health(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    font = new FontManager();
    health = 100;
    font->setFont("fonts/Orbitron-VariableFont_wght.ttf");
    healthim1 = TextureManager::LoadTexture("assets/spritesheet.png", renderer);
    healthim2 = TextureManager::LoadTexture("assets/health.png", renderer);
    srcRect1[0] = {267, 11, 206, 337};
    srcRect1[1] = {37, 11, 220, 337};
    srcRect1[2] = {483, 11, 206, 337};
    srcRect1[3] = {5, 364, 577, 581};
    srcRect1[4] = {1131, 5, 1180, 337};
    srcRect1[5] = {794, 105, 111, 149};
    srcRect1[6] = {915, 105, 98, 149};
    srcRect1[7] = {5, 105, 22, 149};
    mvrRect[0] = {940, 100, 20, 30};
    for (int i = 1; i < 11; i++)
    {
        mvrRect[i] = {(i * 20) + 940, 100, 20, 30};
    }
    mvrRect[11] = {(11 * 20) + 940, 100, 20, 30};
    mvrRect[12] = {940 - 10, 100, 50, 50};
    mvrRect[13] = {1020, 130, 150, 30};
    mvrRect[14] = {945, 115, 20, 20};

    bar[0] = {948, 108, 6, 14};
    for (int i = 1; i < 36; i++)
    {
        bar[i] = {(i * 6) + 948, 108, 6, 14};
    }
    bar[36] = {(36 * 6) + 948, 108, 6, 14};
}

void Health::Render()
{
    for (int i = 0; i < 12; i++)
    {
        if (i == 0)
            SDL_RenderCopy(renderer, healthim1, &(srcRect1[0]), &(mvrRect[0]));
        else if (i == 11)
            SDL_RenderCopy(renderer, healthim1, &(srcRect1[2]), &(mvrRect[11]));
        else
            SDL_RenderCopy(renderer, healthim1, &(srcRect1[1]), &(mvrRect[i]));
    }

    for (int i = 0; i < (health / 2.7027027027027); i++)
    {
        if (i == 0)
            SDL_RenderCopy(renderer, healthim1, &(srcRect1[5]), &(bar[0]));
        else if (i == 36)
            SDL_RenderCopy(renderer, healthim1, &(srcRect1[6]), &(bar[36]));
        else
            SDL_RenderCopy(renderer, healthim1, &(srcRect1[7]), &(bar[i]));
    }

    SDL_RenderCopy(renderer, healthim1, &(srcRect1[3]), &(mvrRect[12]));
    SDL_RenderCopy(renderer, healthim1, &(srcRect1[4]), &(mvrRect[13]));
    SDL_RenderCopy(renderer, healthim2, NULL, &(mvrRect[14]));

    font->renderText(renderer, ("health: " + std::to_string(health) + "/100").c_str(), 1052, 130, 13, {255, 255, 255, 255});
}

void Health::setHealth(int health)
{
    if (health < 0)
    {
        this->health = 0;
    }
    else if (health > 100)
    {
        this->health = 100;
    }
    else
    {
        this->health = health;
    }
}

int Health::getHealth()
{
    return this->health;
}

Health::~Health()
{
    delete this->font;
    this->font = nullptr;
}