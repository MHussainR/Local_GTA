#include "game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "mapobject.hpp"
#include "CarObject.hpp"
#include "MainCharacter.hpp"
#include "AmbulanceMission.hpp"
#include "SmallMapObject.hpp"
#include "stacked_sprites.hpp"
#include<list>
using std::list;
#include "NonPlayerCharacters.hpp"
#include "Physics.hpp"


// Game::Game(){}
// Game::~Game(){}
SDL_Event Game::event;

// NonPlayerCharacters *npc;
std::list<NonPlayerCharacters *> npcArray;
MainCharacter *human;
AmbulanceMission* aMission;
// CarObject *aMission;
// CarObject *car1;
MapObject *map;
SmallMapObject *smallMap;
MapObject *screen;
MapObject *instruction;
MapObject *loader;
Stacked_Sprites* box_3d;
list<CarObject*> cars;


void Game::init(const char *title, int x_pos, int y_pos, int height, int width, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialized" << std::endl;
        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        if (window)
        {
            std::cout << "Window Created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer Created" << std::endl;
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
    npcArray.push_back(new NonPlayerCharacters("assets/npcs.png", renderer, 900, 400, 'd'));
    npcArray.push_back(new NonPlayerCharacters("assets/npcs.png", renderer, 900, 1000, 'u'));
    // }
        // npc = new NonPlayerCharacters("assets/npcs.png", renderer, 900, 700);
    human = new MainCharacter("assets/players.png", renderer, 600, 400);
    cars.push_back(new CarObject("assets/cars.png", renderer, 600*2 - 200, 400*2, "Normal"));
    cars.push_back(new CarObject("assets/cars.png", renderer, 600*4+450, 400*5+50, "Taxi"));
    // aMission = new CarObject("assets/cars.png", renderer, 600 * 2, 400 * 2, "Normal");
    // car1 = new CarObject("assets/cars.png", renderer, 600*4, 400*4, "Ambulance");
    map = new MapObject("assets/map6.png", renderer, 0, 0);
    smallMap = new SmallMapObject("assets/map6.png", renderer, 0, 0);
    screen = new MapObject("assets/title5.png", renderer, 0, 0);
    instruction = new MapObject("assets/ins2.png", renderer, 0, 0);
    loader = new MapObject("assets/loader.png", renderer, 0, 0);
    aMission = new AmbulanceMission(renderer);
    box_3d = new Stacked_Sprites("assets/building_2_stack.png", renderer, 1405, 305, 0, 100, 200, 100, 20, 1, 5, 7);
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
            smallMap->Update('u', human->inside_box_x, human->inside_box_y);
            smallMap->set_speed(5);
            Game::dx = 0;
            Game::direction = 'u';
            for (CarObject *c : cars){
                c->Update('u', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
                c->set_speed(5);
            }
            aMission->Update('u', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            aMission->set_speed(5);
            aMission->setSpeedP(map->getSpeed());
            box_3d->Update('u', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            box_3d->set_speed(map->getSpeed());
            // car1->Update('u', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            // car1->set_speed(5);
        }
        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_DOWN])
        {
            Game::dy = 5;
            Game::dx = 0;
            smallMap->Update('d', human->inside_box_x, human->inside_box_y);
            smallMap->set_speed(5);
            Game::direction = 'd';
            for (CarObject *c : cars){
                c->Update('d', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
                c->set_speed(5);
            }
            aMission->Update('d', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            aMission->set_speed(5);
            aMission->setSpeedP(map->getSpeed());
            box_3d->Update('d', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            box_3d->set_speed(map->getSpeed());
            // car1->Update('d', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            // car1->set_speed(5);
        }
        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_RIGHT])
        {

            Game::dy = 0;
            Game::dx = 5;
            smallMap->Update('r', human->inside_box_x, human->inside_box_y);
            smallMap->set_speed(5);
            Game::direction = 'r';
            // npc->Update(5, map->getXpos(), map->getYpos());
            for (CarObject *c : cars){
                c->Update('r', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
                c->set_speed(5);
            }
            aMission->Update('r', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            aMission->set_speed(5);
            aMission->setSpeedP(map->getSpeed());
            box_3d->Update('r', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            box_3d->set_speed(map->getSpeed());
            // car1->Update('r', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            // car1->set_speed(5);
        }
        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_LEFT])
        {
            Game::dy = 0;
            Game::dx = -5;
            smallMap->Update('l', human->inside_box_x, human->inside_box_y);
            smallMap->set_speed(5);
            Game::direction = 'l';
            for (CarObject *c : cars){
                c->Update('l', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
                c->set_speed(5);
            }
            aMission->Update('l', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            aMission->set_speed(5);
            aMission->setSpeedP(map->getSpeed());
            box_3d->Update('l', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            box_3d->set_speed(map->getSpeed());
            // car1->Update('l', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            // car1->set_speed(5);
        }
        else if (state[SDL_SCANCODE_LEFT])
        {
            map->Update('l', human->inside_box_x, human->inside_box_y);
            smallMap->Update('l', human->inside_box_x, human->inside_box_y);
            // map->set_speed(2);
            human->Run(false);
            human->Update('l', map->getXpos(), map->getYpos());
            int i = 0;
            for (CarObject *c : cars){
                c->Update('l', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
                if (c->getStatus()){
                    i = 1;
                    for (CarObject *c1 : cars){
                        if (c != c1){
                            c1->set_speed(5);
                        }
                    }
                } else {
                    map->set_speed(2);
                    smallMap->set_speed(2);
                    c->set_speed(2);   
                }
            }
            
            aMission->Update('l', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            if (aMission->getStatus()){
                i = 1;
                for (CarObject *c1 : cars){
                    c1->set_speed(5);
                }
            } else {
                map->set_speed(2);
                smallMap->set_speed(2);
                aMission->set_speed(2);
            }
            if (i == 1){
                map->set_speed(5);
                smallMap->set_speed(5);
                aMission->set_speed(5);
            }
            aMission->setSpeedP(map->getSpeed());
            box_3d->Update('l', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            box_3d->set_speed(map->getSpeed());
            // car1->Update('l', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            // if (car1->getStatus()){
            //     map->set_speed(5);
            // } else {
            //     map->set_speed(2);
            //     car1->set_speed(2);
            // }
        }
        else if (state[SDL_SCANCODE_UP])
        {
            map->Update('u', human->inside_box_x, human->inside_box_y);
            smallMap->Update('u', human->inside_box_x, human->inside_box_y);
            // map->set_speed(2);
            human->Run(false);
            human->Update('u', map->getXpos(), map->getYpos());
            int i = 0;
            for (CarObject *c : cars){
                c->Update('u', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
                if (c->getStatus()){
                    i = 1;
                    for (CarObject *c1 : cars){
                        if (c != c1){
                            c1->set_speed(5);
                        }
                    }
                } else {
                    map->set_speed(2);
                    smallMap->set_speed(2);
                    c->set_speed(2);   
                }
            }
            
            aMission->Update('u', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            if (aMission->getStatus()){
                i = 1;
                for (CarObject *c1 : cars){
                    c1->set_speed(5);
                }
            } else {
                map->set_speed(2);
                smallMap->set_speed(2);
                aMission->set_speed(2);
            }
            if (i == 1){
                map->set_speed(5);
                smallMap->set_speed(5);
                aMission->set_speed(5);
            }
            aMission->setSpeedP(map->getSpeed());
            box_3d->Update('u', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            box_3d->set_speed(map->getSpeed());
            // car1->Update('u', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            // if (car1->getStatus()){
            //     map->set_speed(5);
            // } else {
            //     map->set_speed(2);
            //     car1->set_speed(2);
            // }
        }
        else if (state[SDL_SCANCODE_RIGHT])
        {
            map->Update('r', human->inside_box_x, human->inside_box_y);
            smallMap->Update('r', human->inside_box_x, human->inside_box_y);
            // map->set_speed(2);
            human->Run(false);
            human->Update('r', map->getXpos(), map->getYpos());
            int i = 0;
            for (CarObject *c : cars){
                c->Update('r', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
                if (c->getStatus()){
                    i = 1;
                    for (CarObject *c1 : cars){
                        if (c != c1){
                            c1->set_speed(5);
                        }
                    }
                } else {
                    map->set_speed(2);
                    smallMap->set_speed(2);
                    c->set_speed(2);   
                }
            }
            
            aMission->Update('r', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            if (aMission->getStatus()){
                i = 1;
                for (CarObject *c1 : cars){
                    c1->set_speed(5);
                }
            } else {
                map->set_speed(2);
                smallMap->set_speed(2);
                aMission->set_speed(2);
            }
            if (i == 1){
                map->set_speed(5);
                smallMap->set_speed(5);
                aMission->set_speed(5);
            }
            aMission->setSpeedP(map->getSpeed());
            box_3d->Update('r', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            box_3d->set_speed(map->getSpeed());
            // car1->Update('r', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            // if (car1->getStatus()){
            //     map->set_speed(5);
            // } else {
            //     map->set_speed(2);
            //     car1->set_speed(2);
            // }
        }
        else if (state[SDL_SCANCODE_DOWN])
        {
            map->Update('d', human->inside_box_x, human->inside_box_y);
            smallMap->Update('d', human->inside_box_x, human->inside_box_y);
            // map->set_speed(2);
            human->Run(false);
            human->Update('d', map->getXpos(), map->getYpos());
            int i = 0;
            for (CarObject *c : cars){
                c->Update('d', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
                if (c->getStatus()){
                    i = 1;
                    for (CarObject *c1 : cars){
                        if (c != c1){
                            c1->set_speed(5);
                        }
                    }
                } else {
                    map->set_speed(2);
                    smallMap->set_speed(2);
                    c->set_speed(2);   
                }
            }
            
            aMission->Update('d', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            if (aMission->getStatus()){
                i = 1;
                for (CarObject *c1 : cars){
                    c1->set_speed(5);
                }
            } else {
                map->set_speed(2);
                smallMap->set_speed(2);
                aMission->set_speed(2);
            }
            if (i == 1){
                map->set_speed(5);
                smallMap->set_speed(5);
                aMission->set_speed(5);
            }
            aMission->setSpeedP(map->getSpeed());
            box_3d->Update('d', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            box_3d->set_speed(map->getSpeed());
            // car1->Update('d', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            // if (car1->getStatus()){
            //     map->set_speed(5);
            // } else {
            //     map->set_speed(2);
            //     car1->set_speed(2);
            // }
            // std::cout << aMission->getStatus();
        }
        else if (state[SDL_SCANCODE_R])
        {
            title = true;
            map->Reset();
            smallMap->Reset();
            // aMission->Reset();
            // car1->Reset();
            for (CarObject *c : cars){
                c->Reset();
            }
        }
        // else if (state[SDL_SCANCODE_F])
        // {

        // }
        else if (Game::event.type == SDL_KEYDOWN)
        {
            if (Game::event.key.keysym.sym == SDLK_f)
            {
                for (CarObject *c : cars){
                    c->setStatus(human->getXpos(), human->getYpos());
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
        // if (Game::event.type == SDL_KEYDOWN)
        // {
        //     if (Game::event.key.keysym.sym == SDLK_LSHIFT)
        //     {
        //        9 std::cout << "run";
        //     }
        //     if (Game::event.key.keysym.sym == SDLK_UP)
        //     {
        //         map->Update('u', human->inside_box_x, human->inside_box_y);
        //         human->Update('u', map->getXpos(), map->getYpos());
        //     }
        //     if (Game::event.key.keysym.sym == SDLK_DOWN)
        //     {
        //         map->Update('d', human->inside_box_x, human->inside_box_y);
        //         human->Update('d', map->getXpos(), map->getYpos());
        //     }
        //     if (Game::event.key.keysym.sym == SDLK_LEFT)
        //     {
        //         map->Update('l', human->inside_box_x, human->inside_box_y);
        //         human->Update('l', map->getXpos(), map->getYpos());
        //     }
        //     if (Game::event.key.keysym.sym == SDLK_RIGHT)
        //     {
        //         map->Update('r', human->inside_box_x, human->inside_box_y);
        //         human->Update('r', map->getXpos(), map->getYpos());
        //     }
        //     if (Game::event.key.keysym.sym == SDLK_r)
        //     {
        //         title = true;
        //     }
        // }
        // map->Update();
        // human->Update();
        if (human->inside_box_x)
        {
            Game::dx = 0;
        }
        if (human->inside_box_y)
        {
            Game::dy = 0;
        }

        // if (Implement.collisionHandler(human, npc, Game::dx, Game::dy))
        // {
        //     // std::cout << Game::direction << " " << Game::dx << " " << Game::dy << std::endl;
        //     // collision = true;
        //     Game::direction = 'n';
        //     Game::dx = 0;
        //     Game::dy = 0;
        // }
        // (Implement.collisionHandler(npcArray, map));
        // {
        //     Game::direction = 'n';
        //     Game::dx = 0;
        //     Game::dy = 0;
        // }
        // {
            // std::cout << Game::direction << " " << Game::dx << " " << Game::dy << std::endl;
            // collision = true;
            // Game::direction = 'n';
            // Game::dx = 0;
            // Game::dy = 0;
        // }
            // if (collision)
            // {
            //     Game::direction = 'n';
            //     Game::dx = 0;
            //     Game::dy = 0;
            // }
            // if (not collision)
            // {
        map->Update(Game::direction, human->inside_box_x, human->inside_box_y, Game::dx, Game::dy);
        human->Update(Game::direction, map->getXpos(), map->getYpos());
        for (NonPlayerCharacters* npc: npcArray)
        {
            npc->Update(Game::dx, Game::dy);
        }
        
        // }

        // npc->Update(map->get_gameSpeed(), map->getXpos(), map->getYpos());
        // aMission->Update();

        // car1->Update();
        for (CarObject *c : cars){
            c->Update();
        }
        aMission->Update();
        
        if (aMission->getState())
            aMission->Running(map->getXpos(), map->getYpos());
        else 
            aMission->check();

        smallMap->Update();
        box_3d->Update(human->getXpos(), human->getYpos());
        // aMission->Update();
        // aMission->draw_circle(renderer, 600, 400, 100);
        // aMission->srcRect = {616, 51, 200, 390};
        // tree1->moverRect = {600, 400, 136, 192};
        // tree2->Update();
        // tree2->srcRect = {544, 3, 204, 237};
        // title_screen->Update();

        // map->moverRect = {0, 0, }
        // tree->moverRect.x = move;
        // move ++;
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
        {
        //     human->Render();
        // }
        
        // if (!car1->getStatus()){
        //     human->Render();
        // }
        int i = 0;
        for (CarObject *c : cars){
            c->Render();
            if (c->getStatus()){
                i = 1;
            }   
        }
        if (aMission->getStatus())
            i = 1;
        if (i == 0){
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
