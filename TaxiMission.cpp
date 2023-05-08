#include "TaxiMission.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include <string.h>
#include <cstring>

TaxiMission::TaxiMission(SDL_Renderer *ren, int mapx, int mapy) : Mission(ren)
{

    Taxi = new CarObject("assets/cars.png", ren, 1300 - mapx, 3000 - mapy, "Taxi");
    picked1 = false;
    picked2 = false;
    failed = false;
    passanger1 = new CarObject("assets/npcs.png", ren, 4400 - mapx, 1300 - mapy);
    passanger2 = new CarObject("assets/npcs.png", ren, 1500 - mapx, 3700 - mapy);
    passanger1->srcRect = {50, 64, 49, 28};
    passanger2->srcRect = {50, 64, 49, 28};
    flip1 = SDL_FLIP_NONE;
    flip1 = SDL_FLIP_VERTICAL;
    pivot = {Taxi->moverRect.h / 2, 49 / 2};
    aSrcRect = {315, 323, 53, 49};
    pSrcRect = {225, 223, 89, 62};
    arrow = TextureManager::LoadTexture("assets/arrows.png", ren);
    arrow_angle = 0;
    font = new FontManager();
    font->setFont("fonts/StampedPersonalUseRegular-ywJm3.ttf");
    font1 = new FontManager();
    font1->setFont("fonts/Orbitron-VariableFont_wght.ttf");
    timer = 3600;
    shape = new Shapes();
}

void TaxiMission::Update(char direction, int x, int y, bool movex, bool movey)
{
    // Ambulance->Update(direction, x, y, movex, movey);
    // patient->Update(direction, x, y, movex, movey);
    passanger1->moverRect.w = 49;
    passanger1->moverRect.h = 28;
    passanger2->moverRect.w = 49;
    passanger2->moverRect.h = 28;
    // aMoverRect = {600 - 53 / 2, 400 - 49 / 2, 53, 49};
    // pMoverRect = {x-900, y-2700, pSrcRect.w, pSrcRect.h};
    // std::cout << aMoverRect.x << "  " << aMoverRect.y << std::endl;
}

void TaxiMission::Update(int x, int y)
{
    Taxi->Update(x, y);
    passanger1->Update(x, y);
    passanger2->Update(x, y);

    passanger1->moverRect.w = 49;
    passanger1->moverRect.h = 28;
    passanger1->moverRect.w = 49;
    passanger1->moverRect.h = 28;
    // aMoverRect = {600 - 53 / 2, 400 - 49 / 2, 53, 49};
    // patient->moverRect.w = 49;
    // patient->moverRect.h = 28;
    aMoverRect = {Taxi->getXpos(), Taxi->getYpos() + Taxi->moverRect.h / 2, aSrcRect.w, aSrcRect.h};
    pMoverRect = {x-900, y-2700, pSrcRect.w, pSrcRect.h};
    
}

void TaxiMission::Render(int x, int y, int x1, int y1)
{

    char buffer[10];
    sprintf(buffer, "%d", timer / 60);
    Taxi->Render();
    // if (!picked && isRunning)
    //     patient->Render();
    if (isRunning)
    {
        // SDL_RenderCopyEx(renderer, arrow, &aSrcRect, &aMoverRect, arrow_angle, &pivot, flip1);
        if (timer >= 3480)
            font->renderText(renderer, "Mission Started", 400, 100, 36, {0, 0, 0, 255});
        // if (timer%60 == 0)
        if (timer >= 600)
            font1->renderText(renderer, buffer, 600, 50, 50, {0, 0, 0, 255});
        else
            font1->renderText(renderer, buffer, 600, 50, 50, {255, 0, 0, 255});

        if (picked1 | picked2)
        {
            font1->renderText(renderer, "Take the passender to their dropoff back to the hospital", 300, 700, 25, {0, 0, 0, 255});
            font1->renderText(renderer, "(Follow the arrow)", 500, 750, 25, {0, 0, 0, 255});
            SDL_RenderCopyEx(renderer, arrow, &pSrcRect, &pMoverRect, position_angle, NULL, flip2);
        }
        else
        {
            font1->renderText(renderer, "Follow the arrow, go to the patient, press \"g\" to pick them...", 250, 750, 25, {0, 0, 0, 255});
            passanger1->Render();
            passanger2->Render();
            // SDL_RenderCopyEx(renderer, arrow, &aSrcRect, &aMoverRect, arrow_angle, &pivot, flip);
        }
        SDL_RenderCopyEx(renderer, arrow, &aSrcRect, &aMoverRect, arrow_angle, &pivot, flip1);
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
    shape->Draw_circle(renderer, 1000-x, 1000-y, 250);

    // AmbulanceMission::drawLine(renderer, patient->getXpos(), patient->getYpos(), Ambulance->getXpos(), Ambulance->getYpos());
}

void TaxiMission::set_speed(int val)
{
    Taxi->set_speed(val);
}

bool TaxiMission::getStatus()
{
    return Taxi->getStatus();
}

void TaxiMission::setStatus(int x, int y)
{
    Taxi->setStatus(x, y);
}

void TaxiMission::check()
{
    if (failed == false)
    {
        if (Taxi->getStatus())
        {
            isRunning = true;
        }
    }
}

void TaxiMission::setSpeedP(int val)
{
    passanger1->set_speed(val);
    passanger2->set_speed(val);
}

bool TaxiMission::getState()
{
    return isRunning;
}

void TaxiMission::Running(int x, int y)
{
    if (timer == 0)
    {
        isRunning = false;
        picked1 = false;
        picked2 = false;
        // std::cout << "Mission Failed" << '\n';
        failed = true;
    }
    else
    {
        timer--;
    }
    if (timer % 60 == 0)
    {
        // std::cout << timer/60 << '\n';
        if (picked1)
            arrow_angle = -(std::atan2((pMoverRect.x - Taxi->getXpos()), (pMoverRect.y - Taxi->getYpos()))) * (180 / M_PI) + 90;
        else
            arrow_angle = -(std::atan2((passanger1->getXpos() - Taxi->getXpos()), (passanger1->getYpos() - Taxi->getYpos()))) * (180 / M_PI) + 90;
    }

    if (abs((passanger1->getXpos() - Taxi->getXpos()) * (passanger1->getXpos() - Taxi->getXpos()) + abs((passanger1->getYpos() - Taxi->getYpos()) * (passanger1->getYpos() - Taxi->getYpos())) <= 100 * 100))
    {

        if (Game::event.type == SDL_KEYDOWN)
        {
            if (Game::event.key.keysym.sym == SDLK_g)
            {
                picked1 = true;
            }
        }
    }
    if (picked1)
    {
        if (abs((x - 900 - 100 - Taxi->moverRect.w / 4) * (x - 900 - 100 - Taxi->moverRect.w / 4)) + abs((y - 2700 + 100 - Taxi->moverRect.h / 4) * (y - 2700 + 100 - Taxi->moverRect.h / 4)) <= 150 * 150)
        {
            completed = true;
            isRunning = false;
            // Ambulance->setStatus(false);
            // std::cout << "Mission completed" << '\n';
            // Ambulance->moverRect.x = 600 * 8 + 50;
            // Ambulance->moverRect.y = 400 * 2;
            // Ambulance->set_speed('n');
            
        }
        // shape->Draw_circle(renderer, x - 900 - 100 - Taxi->moverRect.w / 4, y - 2700 + 100 - Taxi->moverRect.h / 4, 250);
        // std::cout << abs((x-600*7 - 100 - Ambulance->moverRect.w/4)*(x-600*7 - 100- Ambulance->moverRect.w/4)) + abs((y-400 + 100 - Ambulance->moverRect.h/4)*(y-400 + 100- Ambulance->moverRect.h/4)) << '\n';
        // std::cout << x << "   " << y << '\n';
    }
    

    //     // std::cout << arrow_angle << '\n';
}
