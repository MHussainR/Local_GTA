#pragma once
#include<SDL.h>
#include<iostream>
#include<SDL_image.h>

class Game {
 
    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
        int move = 0;
    public:
        Game(){}
        ~Game (){}

        void init(const char* title, int x_pos, int y_pos, int height, int width, bool fullscreen);
        
        void handleEvents();
        void update();
        void render();
        void clean();

        bool running () {return isRunning;}

};