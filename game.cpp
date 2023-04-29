#include "game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "mapobject.hpp"
#include "CarObject.hpp"
#include "MainCharacter.hpp"
#include "AmbulanceMission.hpp"
#include "SmallMapObject.hpp"
#include "stacked_sprites.hpp"
#include <list>
// using std::list;
#include "NonPlayerCharacters.hpp"
#include "Physics.hpp"

// Game::Game(){}
// Game::~Game(){}
SDL_Event Game::event;

// NonPlayerCharacters *npc;
std::list<NonPlayerCharacters *> npcArray;
MainCharacter *human;
AmbulanceMission *aMission;
// CarObject *aMission;
// CarObject *car1;
MapObject *map;
SmallMapObject *smallMap;
MapObject *screen;
MapObject *instruction;
MapObject *loader;
Stacked_Sprites *box_3d;
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

    human = new MainCharacter("assets/players.png", renderer, 600, 400);
    cars.push_back(new CarObject("assets/cars.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1200), Co_Ordinate_System->setGlobalCoOrdinatey(800), "Normal"));
    cars.push_back(new CarObject("assets/cars.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(2850), Co_Ordinate_System->setGlobalCoOrdinatey(2050), "Taxi"));

    smallMap = new SmallMapObject("assets/map6.png", renderer, 0, 0);
    screen = new MapObject("assets/title5.png", renderer, 0, 0);
    instruction = new MapObject("assets/ins2.png", renderer, 0, 0);
    loader = new MapObject("assets/loader.png", renderer, 0, 0);
    aMission = new AmbulanceMission(renderer);
    box_3d = new Stacked_Sprites("assets/building_2_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1405), Co_Ordinate_System->setGlobalCoOrdinatey(305), 0, 100, 200, 100, 20, 1, 5, 7);
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

    else
    {

        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);

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

                // aMission->setStatus(human->getXpos(), human->getYpos());
                // car1->setStatus(human->getXpos(), human->getYpos());
            }

            if (Game::event.key.keysym.sym == SDLK_s)
            {
                box_3d->Rotate();
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

        if (human->in_car)
        {
            if (Game::dx > 0)
            {
                Game::dx = 5;
                Game::dy = 0;
            }
            else if (Game::dx < 0)
            {
                Game::dx = -5;
                Game::dy = 0;
            }
            else if (Game::dy > 0)
            {
                Game::dy = 5;
                Game::dx = 0;
            }
            else if (Game::dy < 0)
            {
                Game::dy = -5;
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

        for (CarObject *c : cars)
        {
            c->Update(Game::dx, Game::dy);
        }
        aMission->Update(Game::dx, Game::dy);

        if (aMission->getState())
            aMission->Running(map->getXpos(), map->getYpos());
        else
            aMission->check();

        box_3d->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());

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
    else
    {
        map->Render();
        aMission->Render(map->getXpos(), map->getYpos());
        box_3d->Render(human->getXpos(), human->getYpos());
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
        if (i == 0)
        {
            human->Render();
        }
        smallMap->Render();
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
