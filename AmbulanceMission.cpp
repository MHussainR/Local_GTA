#include "AmbulanceMission.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include <string.h>
#include <cstring>
// #include "font.hpp"
#include <cmath>
// #include <SDL2/SDL.h>

#include <iostream>

AmbulanceMission::AmbulanceMission(SDL_Renderer *ren, int mapx, int mapy) : Mission(ren)
{
    Ambulance = new CarObject("assets/cars.png", renderer, 4850-mapx, 800 - mapy, "Ambulance");
    picked = false;
    failed = false;
    patient = new CarObject("assets/npcs.png", renderer, 1500-mapx, 3700-mapy);
    patient->srcRect = {50, 64, 49, 28};
    flip = SDL_FLIP_NONE;
    pivot = {Ambulance->moverRect.h / 2, 49 / 2};
    aSrcRect = {315, 323, 53, 49};
    arrow = TextureManager::LoadTexture("assets/arrows.png", ren);
    arrow_angle = 0;
    font = new FontManager();
    font->setFont("fonts/StampedPersonalUseRegular-ywJm3.ttf");
    font1 = new FontManager();
    font1->setFont("fonts/Orbitron-VariableFont_wght.ttf");
    timer = 3600;
    // font = TTF_OpenFont("font.ttf", 28);
    // FontManager::instance().loadFont("fonts/Orbitron-VariableFont_wght.ttf", 32, "Orbitron");
    // font = TTF_OpenFont("arial.ttf", 24);
}

AmbulanceMission::~AmbulanceMission(){
    delete Ambulance;
    delete patient;
    delete font;
    delete font1;
}

void AmbulanceMission::Update()
{
    Ambulance->Update();
    patient->Update();
    patient->moverRect.w = 49;
    patient->moverRect.h = 28;
    aMoverRect = {Ambulance->getXpos(), Ambulance->getYpos() + Ambulance->moverRect.h / 2, 53, 49};
    // std::cout << Ambulance->getXpos() << " " << Ambulance->getYpos() << std::endl;
}

void AmbulanceMission::Update(char direction, int x, int y, bool movex, bool movey)
{
    // Ambulance->Update(direction, x, y, movex, movey);
    // patient->Update(direction, x, y, movex, movey);
    patient->moverRect.w = 49;
    patient->moverRect.h = 28;
    aMoverRect = {600 - 53 / 2, 400 - 49 / 2, 53, 49};
    // std::cout << aMoverRect.x << "  " << aMoverRect.y << std::endl;
}

void AmbulanceMission::Update(int x, int y)
{
    Ambulance->Update(x, y);
    patient->Update(x, y);
    patient->moverRect.w = 49;
    patient->moverRect.h = 28;
    aMoverRect = {600 - 53 / 2, 400 - 49 / 2, 53, 49};
    patient->moverRect.w = 49;
    patient->moverRect.h = 28;
    aMoverRect = {Ambulance->getXpos(), Ambulance->getYpos() + Ambulance->moverRect.h / 2, 53, 49};
}

void AmbulanceMission::Render()
{

    Ambulance->Render();
    if (!picked && isRunning)
        patient->Render();
    if (isRunning)
        SDL_RenderCopyEx(renderer, arrow, &aSrcRect, &aMoverRect, arrow_angle, &pivot, flip);

    // AmbulanceMission::drawLine(renderer, 600*2 + 300, 400*9+100, )
}

void AmbulanceMission::Render(int x, int y)
{

    char buffer[10];
    sprintf(buffer, "%d", timer / 60);
    Ambulance->Render();
    // if (!picked && isRunning)
    //     patient->Render();
    if (isRunning)
    {

        if (timer >= 3480)
            font->renderText(renderer, "Mission Started", 400, 100, 36, {0, 0, 0, 255});
        // if (timer%60 == 0)
        if (timer >= 600)
            font1->renderText(renderer, buffer, 1100, 50, 50, {0, 0, 0, 255});
        else
            font1->renderText(renderer, buffer, 1100, 50, 50, {255, 0, 0, 255});

        if (picked)
        {
            font1->renderText(renderer, "Take the patient back to the hospital", 300, 750, 25, {0, 0, 0, 255});
        }
        else
        {
            font1->renderText(renderer, "Follow the arrow, go to the patient, press \"g\" to pick them...", 250, 750, 25, {0, 0, 0, 255});
            patient->Render();
            SDL_RenderCopyEx(renderer, arrow, &aSrcRect, &aMoverRect, arrow_angle, &pivot, flip);
        }
    }
    if (completed == true)
    {
        static int frame = 0;
        if (frame <= 120)
        {
            font->renderText(renderer, "Mission Completed", 400, 100, 36, {0, 255, 0, 255});
            frame++;
        }
    }

    if (timer == 0)
    {
        static int frame = 0;
        if (frame <= 120)
        {
            font->renderText(renderer, "Mission Failed", 400, 100, 36, {255, 0, 0, 255});
            frame++;
        }
    }

    // AmbulanceMission::drawLine(renderer, patient->getXpos(), patient->getYpos(), Ambulance->getXpos(), Ambulance->getYpos());
}

void AmbulanceMission::set_speed(int val)
{
    Ambulance->set_speed(val);
}

bool AmbulanceMission::getStatus()
{
    return Ambulance->getStatus();
}

void AmbulanceMission::setStatus(int x, int y)
{
    Ambulance->setStatus(x, y);
}

void AmbulanceMission::check()
{
    if (failed == false)
    {
        if (Ambulance->getStatus())
        {
            isRunning = true;
            // std::cout << "Mission Started"<<'\n';
        }
    }
}

void AmbulanceMission::setSpeedP(int val)
{
    patient->set_speed(val);
}

void AmbulanceMission::Running(int x, int y)
{
    if (timer == 0)
    {
        isRunning = false;
        picked = false;
        std::cout << "Mission Failed" << '\n';
        failed = true;
    }
    else
    {
        timer--;
    }
    if (timer % 60 == 0)
    {
        // std::cout << timer/60 << '\n';
        arrow_angle = -(std::atan2((patient->getXpos() - Ambulance->getXpos()), (patient->getYpos() - Ambulance->getYpos()))) * (180 / M_PI) + 90;
    }
    // if (Ambulance->getXpos())
    if (abs((patient->getXpos() - Ambulance->getXpos()) * (patient->getXpos() - Ambulance->getXpos()) + abs((patient->getYpos() - Ambulance->getYpos()) * (patient->getYpos() - Ambulance->getYpos())) <= 100 * 100))
    {

        if (Game::event.type == SDL_KEYDOWN)
        {
            if (Game::event.key.keysym.sym == SDLK_g)
            {
                picked = true;
                // std::cout << "person Picked" << '\n';
            }
        }
    }
    if (picked)
    {
        if (abs((x - 600 * 7 - 100 - Ambulance->moverRect.w / 4) * (x - 600 * 7 - 100 - Ambulance->moverRect.w / 4)) + abs((y - 400 + 100 - Ambulance->moverRect.h / 4) * (y - 400 + 100 - Ambulance->moverRect.h / 4)) <= 150 * 150)
        {
            completed = true;
            isRunning = false;
            Ambulance->setStatus(false);
            // std::cout << "Mission completed" << '\n';
            Ambulance->moverRect.x = 600 * 8 + 50;
            Ambulance->moverRect.y = 400 * 2;
            Ambulance->set_speed('n');
        }
        // std::cout << abs((x-600*7 - 100 - Ambulance->moverRect.w/4)*(x-600*7 - 100- Ambulance->moverRect.w/4)) + abs((y-400 + 100 - Ambulance->moverRect.h/4)*(y-400 + 100- Ambulance->moverRect.h/4)) << '\n';
        // std::cout << x << "   " << y << '\n';
    }

    // std::cout << arrow_angle << '\n';
}

bool AmbulanceMission::getState()
{
    return isRunning;
}
