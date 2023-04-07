#include "game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "mapobject.hpp"

// Game::Game(){}

// Game::~Game(){}

GameObject* tree1;
GameObject* tree2;
MapObject* map;

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
    tree1 = new GameObject("assets/Trees.png", renderer, 0, 0);
    tree2 = new GameObject("assets/Trees.png", renderer, 100, 0);
    map = new MapObject("assets/map3.png", renderer, 100, 100);
    
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent (&event);
    switch (event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KeyboardEvent.
        // case SDLK_u:
        //     move+=100;
        //     break;
        default:
            break;
    }
}
void Game::update()
{
    tree1->Update();
    tree1->srcRect = {771, 48, 136, 192};
    tree2->Update();
    tree2->srcRect = {544, 3, 204, 237};
    map->Update();
    // map->moverRect = {0, 0, }
    // tree->moverRect.x = move;
    // move ++;

}
void Game::render()
{
    SDL_RenderClear(renderer);
    map->Render();
    tree1->Render();
    tree2->Render();
    SDL_RenderPresent(renderer);
}
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
