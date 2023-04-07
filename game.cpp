#include "game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "mapobject.hpp"

// Game::Game(){}

// Game::~Game(){}
SDL_Event Game::event;

GameObject* tree1;
GameObject* tree2;
MapObject* map;
MapObject* screen;
MapObject* instruction;
MapObject* loader;

void Game::init(const char* title, int x_pos, int y_pos, int height, int width, bool fullscreen)
{
    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
            std::cout << "Subsystems initialized" << std::endl;
            window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        if (window){
            std::cout << "Window Created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1 , 0);
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer Created" << std::endl;
        }
        isRunning = true;
    } else {
        isRunning = false;
    }

    // SDL_Surface* tmpSurface = IMG_Load("Trees.png");
    // block = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    // SDL_FreeSurface(tmpSurface);
    tree1 = new GameObject("assets/Trees.png", renderer, 600, 400);
    tree2 = new GameObject("assets/Trees.png", renderer, 100, 0);
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

    SDL_PollEvent (&event);
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
    if (loading){
        if (Game::event.type == SDL_QUIT){
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
        if (loader->frame == 360){
            loading = false;
            title = true;
        }
        loader->load();
    } else if (title){
        if (Game::event.type == SDL_QUIT){
            isRunning = false;
        }
        if(Game::event.type == SDL_MOUSEBUTTONDOWN){
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse,&yMouse);
            if (xMouse >= 49 && xMouse <= 194 && yMouse >= 337 && yMouse <= 378)
                title = false;
            if (xMouse >= 50 && xMouse <= 495 && yMouse >= 508 && yMouse <= 548){
                title = false;
                instructions = true;
            }
        }
        screen->Update();

    } else if (instructions){
        if (Game::event.type == SDL_QUIT){
            isRunning = false;
        }
        if(Game::event.type == SDL_KEYDOWN){
            if (Game::event.key.keysym.sym == SDLK_r){
                instructions = false;
                title = true;
            }
        }
        instruction->Update();
    } else {
        if (Game::event.type == SDL_QUIT){
            isRunning = false;
        }
        if (Game::event.type == SDL_KEYDOWN){
            if (Game::event.key.keysym.sym == SDLK_UP){
                map->Update('u', tree1->inside_box_x, tree1->inside_box_y);
                tree1->Update('u', map->getXpos(), map->getYpos());
            }
            if (Game::event.key.keysym.sym == SDLK_DOWN){
                map->Update('d', tree1->inside_box_x, tree1->inside_box_y);
                tree1->Update('d', map->getXpos(), map->getYpos());
            }
            if (Game::event.key.keysym.sym == SDLK_LEFT){
                map->Update('l', tree1->inside_box_x, tree1->inside_box_y);
                tree1->Update('l', map->getXpos(), map->getYpos());
            }
            if (Game::event.key.keysym.sym == SDLK_RIGHT){
                map->Update('r', tree1->inside_box_x, tree1->inside_box_y);
                tree1->Update('r', map->getXpos(), map->getYpos());
            }
            if (Game::event.key.keysym.sym == SDLK_r){
                title = true;
            }
        }
        map->Update();
        tree1->Update();
        tree1->srcRect = {771, 48, 136, 192};
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
    if (loading){
        loader->Render();
    } else if (title){
        screen->Render();
    }
    else if (instructions) {
        instruction->Render();
    } else {
    map->Render();
    tree1->Render();
    tree2->Render();
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
