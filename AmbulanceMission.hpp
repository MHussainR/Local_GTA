#pragma once
#include "missions.hpp"
#include "CarObject.hpp"
#include "GameObject.hpp"
#include "FontManager.hpp"
#include <SDL_ttf.h>
#include <string>

class AmbulanceMission : public Mission{
    private:
        CarObject* Ambulance;
        SDL_RendererFlip flip;
        int x_pos, y_pos;
        bool picked;
        bool failed;
        // TTF_Font* font;
        SDL_Rect position;
        CarObject* patient;
        SDL_Texture* arrow;
        SDL_Point pivot;
        double arrow_angle;
        SDL_Rect aSrcRect, aMoverRect;
        FontManager* font;
        FontManager* font1;
        // SDL_FreeSurface(tempSurface);
    public:
        AmbulanceMission(SDL_Renderer* ren, int, int);
        ~AmbulanceMission();
        void Update();
        void Update(char direction, int x, int y, bool movex, bool movey);
        void Update(int, int);
        void Render();
        void Render(int x, int y);
        void check();
        void set_speed(int val);
        bool getStatus();
        void setStatus(int, int);
        void Running(int x, int y);
        void setSpeedP(int val);
        bool getState();
        // void drawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2);
        
};