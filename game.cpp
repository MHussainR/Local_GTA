#include "game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "mapobject.hpp"
#include "CarObject.hpp"
#include "MainCharacter.hpp"
#include "AmbulanceMission.hpp"
#include "TaxiMission.hpp"
#include "SmallMapObject.hpp"
#include "stacked_sprites.hpp"
#include "cheat_codes.hpp"
#include <list>
// using std::list;
#include "NonPlayerCharacters.hpp"
#include "Health.hpp"
#include "Money.hpp"
#include "CircularMenu.hpp"
#include "Physics.hpp"
#include "Police.hpp"
#include "RayCaster.hpp"

// Game::Game(){}
// Game::~Game(){}
SDL_Event Game::event;

// NonPlayerCharacters *npc;
std::list<NonPlayerCharacters *> npcArray;
MainCharacter *human;
AmbulanceMission *aMission;
TaxiMission *tMission;
// CarObject *aMission;
// CarObject *car1;
MapObject *map;
SmallMapObject *smallMap;
MapObject *screen;
MapObject *instruction;
MapObject *loader;
Stacked_Sprites *box;
Stacked_Sprites *flats;
Stacked_Sprites *box_3d2;
Stacked_Sprites *police_st;
Stacked_Sprites *farm;
Stacked_Sprites *hospital;
Stacked_Sprites *park;
Stacked_Sprites *house1;
Stacked_Sprites *house2;
Stacked_Sprites *parking;
RayCaster *RayCast;
Health *health;
Money *money;
CircularMenu *menu;
Police *police;
Cheat_codes *c_codes;
std::list<CarObject *> cars;

void Game::init(const char *title, int x_pos, int y_pos, int height, int width, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        // std::cout << "Subsystems initialized" << std::endl;
        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        if (window)
        {
            // std::cout << "Window Created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            // std::cout << "Renderer Created" << std::endl;
        }
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    // SDL_Surface* tmpSurface = IMG_Load("Trees.png");
    // block = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    // SDL_FreeSurface(tmpSurface);
    // for (int i = 0; i < 2;i++)
    // {
    // NonPlayerCharacters *NPC = new NonPlayerCharacters("assets/npcs.png", renderer, 900, 700);
    map = new MapObject("assets/map6.png", renderer, 200, 800);
    Co_Ordinate_System = CoOrdinateSystem::getInstance(map->getXpos(), map->getYpos());

    npcArray.push_back(new NonPlayerCharacters("assets/npcs.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1120), Co_Ordinate_System->setGlobalCoOrdinatey(400), 'r'));
    npcArray.push_back(new NonPlayerCharacters("assets/npcs.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1120), Co_Ordinate_System->setGlobalCoOrdinatey(1000), 'u'));
    npcArray.push_back(new NonPlayerCharacters("assets/npcs.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1120), Co_Ordinate_System->setGlobalCoOrdinatey(500), 'd'));

    police = new Police(Co_Ordinate_System, renderer);

    human = new MainCharacter("assets/players.png", renderer, 600, 400);
    cars.push_back(new CarObject("assets/cars.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1200), Co_Ordinate_System->setGlobalCoOrdinatey(800), "Normal"));
    cars.push_back(new CarObject("assets/cars.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(2850), Co_Ordinate_System->setGlobalCoOrdinatey(2050), "Taxi"));

    smallMap = new SmallMapObject("assets/map6.png", renderer, 0, 0);
    screen = new MapObject("assets/title5.png", renderer, 0, 0);
    instruction = new MapObject("assets/ins2.png", renderer, 0, 0);
    loader = new MapObject("assets/loader.png", renderer, 0, 0);
    aMission = new AmbulanceMission(renderer, map->getXpos(), map->getYpos());
    tMission = new TaxiMission(renderer, map->getXpos(), map->getYpos());
    // box = new Stacked_Sprites("assets/block_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1000), Co_Ordinate_System->setGlobalCoOrdinatey(1100), 0, 100, 100, 100, 0, 25, 1, 1, 1);
    flats = new Stacked_Sprites("assets/flats_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1400), Co_Ordinate_System->setGlobalCoOrdinatey(300), 0, 100, 200, 100, 180, 20, 1, 5, 7);
    box_3d2 = new Stacked_Sprites("assets/building_4_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(4800), Co_Ordinate_System->setGlobalCoOrdinatey(1300), 0, 200, 240, 200, 180, 20, 1, 5, 3);
    police_st = new Stacked_Sprites("assets/police_station_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1400), Co_Ordinate_System->setGlobalCoOrdinatey(2900), 0, 100, 175, 100, 180, 20, 1, 7, 8);
    farm = new Stacked_Sprites("assets/farm_type_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(3100), Co_Ordinate_System->setGlobalCoOrdinatey(2900), 0, 100, 175, 100, 180, 20, 1, 5, 8);
    hospital = new Stacked_Sprites("assets/hospital_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(4800), Co_Ordinate_System->setGlobalCoOrdinatey(200), 0, 160, 180, 160, 0, 20, 1, 5, 5);
    park = new Stacked_Sprites("assets/park_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(3100), Co_Ordinate_System->setGlobalCoOrdinatey(300), 0, 100, 200, 100, 180, 20, 1, 5, 7);
    health = new Health(renderer);
    money = new Money(renderer);
    menu = new CircularMenu(renderer, (width / 2) + (human->getMoverRect()->w / 2), (height / 2) + (human->getMoverRect()->h / 2));
    house1 = new Stacked_Sprites("assets/building_5_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(2200), Co_Ordinate_System->setGlobalCoOrdinatey(1300), 0, 200, 200, 200, 270, 20, 1, 3, 3);
    house2 = new Stacked_Sprites("assets/house_2_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(3900), Co_Ordinate_System->setGlobalCoOrdinatey(1300), 0, 200, 200, 200, 270, 20, 1, 3, 3);
    parking = new Stacked_Sprites("assets/parking_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(300), Co_Ordinate_System->setGlobalCoOrdinatey(200), 0, 200, 200, 200, 0, 20, 1, 3, 4);
    RayCast = new RayCaster(renderer);
    c_codes = new Cheat_codes();
}

void Game::handleEvents()
{
    // SDL_PollEvent (&event);
    // switch (event.type){
    //     case SDL_QUIT:
    //         isRunning = false;
    //         break;
    //     // case SDLK_u:
    //     //     move+=100;
    //     //     break;
    //     default:
    //         break;
    // }
}

void Game::update()
{

    SDL_PollEvent(&event);
    // switch (event.type){
    //     case SDL_QUIT:
    //         isRunning = false;
    //         break;
    //     // case SDLK_u:
    //     //     move+=100;
    //     //     break;
    //     default:
    //         break;
    // }
    if (loading)
    {
        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        // if(Game::event.type == SDL_MOUSEBUTTONDOWN){
        //     int xMouse, yMouse;
        //     SDL_GetMouseState(&xMouse,&yMouse);
        //     if (xMouse >= 49 && xMouse <= 194 && yMouse >= 337 && yMouse <= 378)
        //         title = false;
        //     if (xMouse >= 50 && xMouse <= 495 && yMouse >= 508 && yMouse <= 548){
        //         title = false;
        //         instructions = true;
        //     }
        // }
        if (loader->frame == 360)
        {
            loading = false;
            title = true;
        }
        loader->load();
    }

    else if (title)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        if (Game::event.type == SDL_MOUSEBUTTONDOWN)
        {
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);
            std::cout << xMouse << " " << yMouse << std::endl;
            if (xMouse >= 49 && xMouse <= 194 && yMouse >= 337 && yMouse <= 378)
                title = false;
            if (xMouse >= 50 && xMouse <= 495 && yMouse >= 508 && yMouse <= 548)
            {
                title = false;
                instructions = true;
            }
        }

        screen->Update();
    }

    else if (instructions)
    {
        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (Game::event.type == SDL_KEYDOWN)
        {
            if (Game::event.key.keysym.sym == SDLK_r)
            {
                instructions = false;
                title = true;
            }
        }
        instruction->Update();
    }

    else if (RayCast->getState())
    {
        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        RayCast->Update2(map->getMapAllowance(((human->getXpos() + map->getXpos()) / 100), (human->getYpos() + map->getYpos()) / 100));
    }
    else
    {

        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_UP])
        {
            Game::dy = -5;
            Game::dx = 0;
            Game::direction = 'u';
        }

        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_DOWN])
        {
            Game::dy = 5;
            Game::dx = 0;
            Game::direction = 'd';
        }

        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_RIGHT])
        {
            Game::dy = 0;
            Game::dx = 5;
            Game::direction = 'r';
        }

        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_LEFT])
        {
            Game::dy = 0;
            Game::dx = -5;
            Game::direction = 'l';
        }

        else if (state[SDL_SCANCODE_LEFT])
        {
            Game::dy = 0;
            Game::dx = -2;
            Game::direction = 'l';
            health->setHealth(health->getHealth() + 1);
            money->setMoney(money->getMoney() + 10000000);
        }

        else if (state[SDL_SCANCODE_UP])
        {
            Game::dx = 0;
            Game::dy = -2;
            Game::direction = 'u';
        }

        else if (state[SDL_SCANCODE_RIGHT])
        {
            Game::dx = 2;
            Game::dy = 0;
            Game::direction = 'r';
            health->setHealth(health->getHealth() - 1);
            money->setMoney(money->getMoney() - 10000);
        }

        else if (state[SDL_SCANCODE_DOWN])
        {
            Game::dx = 0;
            Game::dy = 2;
            Game::direction = 'd';
        }

        else if (state[SDL_SCANCODE_R])
        {
            title = true;
            map->Reset();
            smallMap->Reset();
            // aMission->Reset();
            // car1->Reset();
            for (CarObject *c : cars)
            {
                c->Reset();
            }
        }

        else if (Game::event.type == SDL_KEYDOWN)
        {
            if (Game::event.key.keysym.sym == SDLK_f)
            {
                bool flag = false;
                for (CarObject *c : cars)
                {
                    c->setStatus(human->getXpos(), human->getYpos());
                    if (c->getStatus())
                    {
                        if (flag == false)
                        {
                            flag = true;
                        }
                    }
                }
                if (flag)
                {
                    human->in_car = true;
                }
                else
                {
                    human->in_car = false;
                }
                aMission->setStatus(human->getXpos(), human->getYpos());
                tMission->setStatus(human->getXpos(), human->getYpos());

                // aMission->setStatus(human->getXpos(), human->getYpos());
                // car1->setStatus(human->getXpos(), human->getYpos());
            }
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_a:
                c_codes->check('a');
                break;
            case SDLK_b:
                c_codes->check('b');
                break;
            case SDLK_c:
                c_codes->check('c');
                break;
            case SDLK_d:
                c_codes->check('d');
                break;
            case SDLK_e:
                c_codes->check('e');
                break;
            case SDLK_f:
                c_codes->check('f');
                break;
            case SDLK_g:
                c_codes->check('g');
                break;
            case SDLK_h:
                c_codes->check('h');
                break;
            case SDLK_i:
                c_codes->check('i');
                break;
            case SDLK_j:
                c_codes->check('j');
                break;
            case SDLK_k:
                c_codes->check('k');
                break;
            case SDLK_l:
                c_codes->check('l');
                break;
            case SDLK_m:
                c_codes->check('m');
                break;
            case SDLK_n:
                c_codes->check('n');
                break;
            case SDLK_o:
                c_codes->check('o');
                break;
            case SDLK_p:
                c_codes->check('p');
                break;
            case SDLK_q:
                c_codes->check('q');
                break;
            case SDLK_r:
                c_codes->check('r');
                break;
            case SDLK_s:
                c_codes->check('s');
                break;
            case SDLK_t:
                c_codes->check('t');
                break;
            case SDLK_u:
                c_codes->check('u');
                break;
            case SDLK_v:
                c_codes->check('v');
                break;
            case SDLK_w:
                c_codes->check('w');
                break;
            case SDLK_x:
                c_codes->check('x');
                break;
            case SDLK_y:
                c_codes->check('y');
                break;
            case SDLK_z:
                c_codes->check('z');
                break;
            default:
                break;
            }

            if (Game::event.key.keysym.sym == SDLK_s)
            {
                // box_3d->Rotate();
            }

            if (Game::event.key.keysym.sym == SDLK_m)
            {
                if (menu->getState())
                {
                    menu->setState(false);
                }
                else
                {
                    menu->setState(true);
                }
            }
        }

        else if (Game::event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (menu->getState())
            {
                menu->setState(false);
            }

            if (Game::event.key.keysym.sym == SDLK_m)
            {
                if (menu->getState())
                {
                    menu->setState(false);
                }
                else
                {
                    menu->setState(true);
                }
            }
        }

        else if (Game::event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (menu->getState())
            {
                menu->setState(false);
            }
        }

        else
        {
            Game::dx = 0;
            Game::dy = 0;
            Game::direction = 'n';
        }

        if (human->inside_box_x)
        {
            Game::dx = 0;
        }

        if (human->inside_box_y)
        {
            Game::dy = 0;
        }

        if (aMission->getStatus() && aMission->getState())
        {
            human->in_car = true;
        }

        if (tMission->getStatus() && tMission->getState())
        {
            human->in_car = true;
        }

        if (human->in_car)
        {
            if (Game::dx > 0)
            {
                Game::dx = 7;
                Game::dy = 0;
            }
            else if (Game::dx < 0)
            {
                Game::dx = -7;
                Game::dy = 0;
            }
            else if (Game::dy > 0)
            {
                Game::dy = 7;
                Game::dx = 0;
            }
            else if (Game::dy < 0)
            {
                Game::dy = -7;
                Game::dx = 0;
            }
            else
            {
                Game::dy = 0;
                Game::dx = 0;
            }
        }

        if (Implement.collisionHandler(human, npcArray, Game::dx, Game::dy))
        {
            Game::direction = 'n';
            Game::dx = 0;
            Game::dy = 0;
        }

        // if (Implement.collisionHandler(human, cars, map, Game::dx, Game::dy))
        // {
        //     Game::direction = 'n';
        //     Game::dx = 0;
        //     Game::dy = 0;
        // }

        Implement.collisionHandler(npcArray, Game::dx, Game::dy);

        (Implement.collisionHandler(npcArray, map));

        if (Implement.collisionHandler(human, map, Game::dx, Game::dy))
        {
            Game::direction = 'n';
            Game::dx = 0;
            Game::dy = 0;
        }

        map->Update(Game::direction, human->inside_box_x, human->inside_box_y, Game::dx, Game::dy);
        smallMap->Update(Game::direction, human->inside_box_x, human->inside_box_y, Game::dx, Game::dy);
        human->Update(Game::direction, map->getXpos(), map->getYpos());
        for (NonPlayerCharacters *npc : npcArray)
        {
            npc->Update(Game::dx, Game::dy);
        }

        police->followPath(map);
        police->Update(Game::dx, Game::dy);

        for (CarObject *c : cars)
        {
            c->Update(Game::dx, Game::dy);
        }
        aMission->Update(Game::dx, Game::dy);
        tMission->Update(map->getXpos(), map->getYpos());

        if (aMission->getState())
            aMission->Running(map->getXpos(), map->getYpos());
        else
            aMission->check();

        if (tMission->getState())
            tMission->Running(map->getXpos(), map->getYpos());
        else
            tMission->check();

        // box->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        flats->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        box_3d2->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        RayCast->Update(map->getMapAllowance(((human->getXpos() + map->getXpos()) / 100), (human->getYpos() + map->getYpos()) / 100));
        police_st->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        farm->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        hospital->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        park->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        house1->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        house2->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        parking->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    if (loading)
    {
        loader->Render();
    }
    else if (title)
    {
        screen->Render();
    }
    else if (instructions)
    {
        instruction->Render();
    }
    else if (RayCast->getState())
    {
        RayCast->Render();
    }
    else
    {
        map->Render();
        // aMission->Render(map->getXpos(), map->getYpos());

        flats->Render(human->getXpos(), human->getYpos());
        box_3d2->Render(human->getXpos(), human->getYpos());
        police_st->Render(human->getXpos(), human->getYpos());
        farm->Render(human->getXpos(), human->getYpos());
        hospital->Render(human->getXpos(), human->getYpos());
        park->Render(human->getXpos(), human->getYpos());
        house1->Render(human->getXpos(), human->getYpos());
        house2->Render(human->getXpos(), human->getYpos());
        parking->Render(human->getXpos(), human->getYpos());
        // box->Render(human->getXpos(), human->getYpos());
        aMission->Render(map->getXpos(), map->getYpos());
        tMission->Render(map->getXpos(), map->getYpos(), Game::dx, Game::dy);

        // aMission->Render();
        // car1->Render();
        for (NonPlayerCharacters *npc : npcArray)
        {
            npc->Render();
        }
        // if (!aMission->getStatus() && !car1->getStatus())

        //     human->Render();
        // }

        // if (!car1->getStatus()){
        //     human->Render();
        // }
        int i = 0;
        for (CarObject *c : cars)
        {
            c->Render();
            if (c->getStatus())
            {
                i = 1;
            }
        }
        if (aMission->getStatus())
            i = 1;
        else if (tMission->getStatus())
            i = 1;

        if (i == 0)
        {
            human->Render();
        }
        smallMap->Render();
        health->Render();
        money->Render();
        menu->Render(atan2(mouseY - (800 / 2), mouseX - (1200 / 2)) * 180 / M_PI, sqrt(pow((mouseX - (1200 / 2)), 2) + pow(mouseY - (800 / 2), 2)));
        police->Render();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean()
{

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

Game::~Game()
{
    delete human;
    human = nullptr;
    delete aMission;
    aMission = nullptr;
    delete map;
    map = nullptr;
    delete smallMap;
    smallMap = nullptr;
    delete screen;
    screen = nullptr;
    delete instruction;
    instruction = nullptr;
    delete loader;
    loader = nullptr;
    delete box;
    box = nullptr;
    delete flats;
    flats = nullptr;
    delete box_3d2;
    box_3d2 = nullptr;
    delete police_st;
    police_st = nullptr;
    delete farm;
    farm = nullptr;
    delete hospital;
    hospital = nullptr;
    delete park;
    park = nullptr;
    delete house1;
    house1 = nullptr;
    delete house2;
    house2 = nullptr;
    delete parking;
    parking = nullptr;
    delete RayCast;
    RayCast = nullptr;
    delete health;
    health = nullptr;
    delete money;
    money = nullptr;
    delete menu;
    menu = nullptr;
    delete police;
    police = nullptr;
    delete Co_Ordinate_System;
    // Co_Ordinate_System = nullptr;
    for (CarObject *t : cars)
    {
        delete t;
        t = nullptr;
    }
    for (NonPlayerCharacters *n : npcArray)
    {
        delete n;
        n = nullptr;
    }
    cars.clear();
    npcArray.clear();
}
