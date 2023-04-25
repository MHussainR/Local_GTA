#include "game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "mapobject.hpp"
#include "CarObject.hpp"
#include "MainCharacter.hpp"
#include "NonPlayerCharacters.hpp"
#include "Physics.hpp"


// Game::Game(){}
// Game::~Game(){}
SDL_Event Game::event;

// NonPlayerCharacters *npc;
std::list<NonPlayerCharacters *> npcArray;
MainCharacter *human;
CarObject *car;
MapObject *map;
MapObject *screen;
MapObject *instruction;
MapObject *loader;


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
    car = new CarObject("assets/cars.png", renderer, 600 * 2, 400 * 2);
    map = new MapObject("assets/map6.png", renderer, 0, 0);
    screen = new MapObject("assets/title5.png", renderer, 0, 0);
    instruction = new MapObject("assets/ins2.png", renderer, 0, 0);
    loader = new MapObject("assets/loader.png", renderer, 0, 0);
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
            Game::dx = 0;
            Game::direction = 'u';
            car->Update('u', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            car->set_speed(5);
        }
        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_DOWN])
        {
            Game::dy = 5;
            Game::dx = 0;
            Game::direction = 'd';
            car->Update('d', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            car->set_speed(5);
        }
        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_RIGHT])
        {

            Game::dy = 0;
            Game::dx = 5;
            Game::direction = 'r';
            // npc->Update(5, map->getXpos(), map->getYpos());
            car->Update('r', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            car->set_speed(5);
        }
        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_LEFT])
        {
            Game::dy = 0;
            Game::dx = -5;
            Game::direction = 'l';
            car->Update('l', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            car->set_speed(5);
        }
        else if (state[SDL_SCANCODE_LEFT])
        {
            Game::dy = 0;
            Game::direction = 'l';
            car->Update('l', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            if (car->getStatus())
            {
                Game::dx = -5;
            }
            else
            {
                Game::dx = -2;
                car->set_speed(2);
            }
        }
        else if (state[SDL_SCANCODE_UP])
        {
            Game::dx = 0;
            Game::direction = 'u';
            car->Update('u', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            if (car->getStatus())
            {
                Game::dy = -5;
            }
            else
            {
                Game::dy = -2;
                car->set_speed(2);
            }
        }
        else if (state[SDL_SCANCODE_RIGHT])
        {
            Game::dy = 0;
            Game::direction = 'r';
            car->Update('r', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            if (car->getStatus())
            {
                Game::dx = 5;
            }
            else
            {
                Game::dx = 2;
                car->set_speed(2);
            }
        }
        else if (state[SDL_SCANCODE_DOWN])
        {
            Game::dx = 0;
            Game::direction = 'd';
            car->Update('d', map->getXpos(), map->getYpos(), human->inside_box_x, human->inside_box_y);
            if (car->getStatus())
            {
                Game::dy = 5;
            }
            else
            {
                Game::dy = 2;
                car->set_speed(2);
            }
            // std::cout << car->getStatus();
        }
        else if (state[SDL_SCANCODE_R])
        {
            title = true;
            map->Reset();
            car->Reset();
        }
        // else if (state[SDL_SCANCODE_F])
        // {

        // }
        else if (Game::event.type == SDL_KEYDOWN)
        {
            if (Game::event.key.keysym.sym == SDLK_f)
            {
                car->setStatus(human->getXpos(), human->getYpos());
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
        car->Update();

        // car->draw_circle(renderer, 600, 400, 100);
        car->srcRect = {616, 51, 200, 390};
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
        car->Render();
        for (NonPlayerCharacters *npc : npcArray)
        {
            npc->Render();
        }
        if (!car->getStatus())
        {
            human->Render();
        }
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
