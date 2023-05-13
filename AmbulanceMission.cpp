#include "AmbulanceMission.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include <string.h>
#include <cstring>
#include "Money.hpp"
// #include "font.hpp"
#include <cmath>
// #include <SDL2/SDL.h>

#include <iostream>

AmbulanceMission::AmbulanceMission(SDL_Renderer *ren, int mapx, int mapy) : Mission(ren)
{
    // Create an instance of the Ambulance object
    Ambulance = new CarObject("assets/cars.png", renderer, 4850 - mapx, 800 - mapy, "Ambulance");
    picked = false;
    failed = false;

    // Create an instance of the patient object
    patient = new CarObject("assets/npcs.png", renderer, 1200 - mapx, 3300 - mapy);
    patient->srcRect = {50, 64, 49, 28};

    flip = SDL_FLIP_NONE;
    pivot = {Ambulance->moverRect.h / 2, 49 / 2};
    aSrcRect = {315, 323, 53, 49};

    // Load the arrow texture
    arrow = TextureManager::LoadTexture("assets/arrows.png", ren);
    arrow_angle = 0;

    // Create instances of FontManager for rendering text
    font = new FontManager();
    font->setFont("fonts/StampedPersonalUseRegular-ywJm3.ttf");
    font1 = new FontManager();
    font1->setFont("fonts/Orbitron-VariableFont_wght.ttf");

    timer = 3600;
}

AmbulanceMission::~AmbulanceMission()
{
    // Deallocate memory for objects
    delete Ambulance;
    delete patient;
    delete font;
    delete font1;
}

void AmbulanceMission::Update()
{
    // Update the position of the ambulance and patient objects
    Ambulance->Update();
    patient->Update();

    // Set dimensions for the patient object
    patient->moverRect.w = 49;
    patient->moverRect.h = 28;

    // Set the position and dimensions for the arrow
    aMoverRect = {Ambulance->getXpos(), Ambulance->getYpos() + Ambulance->moverRect.h / 2, 53, 49};
}

void AmbulanceMission::Update(char direction, int x, int y, bool movex, bool movey)
{
    // Update the position and movement of objects based on player input
    patient->moverRect.w = 49;
    patient->moverRect.h = 28;
    aMoverRect = {600 - 53 / 2, 400 - 49 / 2, 53, 49};
}

void AmbulanceMission::Update(int x, int y)
{
    // Update the position of the ambulance and patient objects based on given coordinates
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
    // Render the ambulance object
    Ambulance->Render();
    // Render the patient object if it has not been picked up
    if (!picked && isRunning)
        patient->Render();

    // Render the arrow indicating the direction
    if (isRunning)
        SDL_RenderCopyEx(renderer, arrow, &aSrcRect, &aMoverRect, arrow_angle, &pivot, flip);

    // AmbulanceMission::drawLine(renderer, 600*2 + 300, 400*9+100, )
}
void AmbulanceMission::Render(int x, int y)
{
    // Convert the timer value to a string
    char buffer[10];
    sprintf(buffer, "%d", timer / 60);
    // Render the ambulance object
    Ambulance->Render();

    if (isRunning)
    {
        if (timer >= 3480)
            font->renderText(renderer, "Mission Started", 400, 100, 36, {0, 0, 0, 255});

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
}

void AmbulanceMission::set_speed(int val)
{
    // Set the speed of the ambulance object
    Ambulance->set_speed(val);
}

bool AmbulanceMission::getStatus()
{
    // Get the status of the ambulance object
    return Ambulance->getStatus();
}

void AmbulanceMission::setStatus(int x, int y)
{
    // Set the status of the ambulance object
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
    // Set the speed of the patient object
    patient->set_speed(val);
}

void AmbulanceMission::Running(int x, int y, Money *money)
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
            money->addMoney(10000);
            Ambulance->moverRect.x = 600 * 8 + 50;
            Ambulance->moverRect.y = 400 * 2;
            Ambulance->set_speed('n');
        }
    }

    // std::cout << arrow_angle << '\n';
}
bool AmbulanceMission::getState()
{
    // Get the current state of the mission
    return isRunning;
}