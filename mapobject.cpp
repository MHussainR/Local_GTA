#include "mapobject.hpp"
#include "TextureManager.hpp"
#include<iostream>

MapObject::MapObject(const char *textursheet, SDL_Renderer *ren, int x, int y) : GameObject(textursheet, ren, x, y) {}
// renderer = ren;
// objTexture = TextureManager::LoadTexture(textursheet, ren);

// x_pos = x;
// y_pos = y;

void MapObject::Update(){
    srcRect = {x_pos, y_pos, 1200, 800};
}

void MapObject::Update(char direction)
{

    if (direction == 'u'){
        if (y_pos != 0)
            y_pos -= 5;
    } else if (direction == 'd'){
        if (y_pos != 3200)
            y_pos += 5;
    } else if (direction == 'l'){
        if (x_pos != 0)
            x_pos -= 5;
    } else if (direction == 'r'){
        if (x_pos != 4800)
            x_pos += 5;
    }
    // x_pos++;
    // y_pos++;

    // srcRect = {771, 48, 136, 192};
    srcRect = {x_pos, y_pos, 1200, 800};
    // moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};
}

void MapObject::Update(char direction, bool movex, bool movey){
    if (movey == false){
        if (direction == 'u'){
            if (y_pos != 0)
                y_pos -= 5;
        } else if (direction == 'd'){
            if (y_pos != 3200)
                y_pos += 5;
        }
    } 
    if (movex == false){
        if (direction == 'l'){
            if (x_pos != 0)
                x_pos -= 5;
        } else if (direction == 'r'){
            if (x_pos != 4800)
                x_pos += 5;
        }
    }
    // x_pos++;
    // y_pos++;
    // std::cout << x_pos << " " << y_pos << std::endl;

    // srcRect = {771, 48, 136, 192};
    srcRect = {x_pos, y_pos, 1200, 800};
    // moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};
}

void MapObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, NULL);
}

void MapObject::load(){
    if (frame <= 60){
        srcRect = {0, 0, 1200, 800};
        frame ++;
    } else if (frame <= 120){
        srcRect = {1200, 0, 1200, 800};
        frame ++;
    } else if (frame <= 180){
        srcRect = {0, 800, 1200, 800};
        frame ++;
    } else if (frame <= 240){
        srcRect = {1200, 800, 1200, 800};
        frame ++;
    } else if (frame <= 300){
        srcRect = {0, 1600, 1200, 800};
        frame ++;
    } else if  (frame <= 360){
        srcRect = {1200, 1600, 1200, 800};
        frame ++;
    } else {
        frame = 0;
    }

    // if ((frame >= 50 && frame <= 60)| (frame >= 110 && frame <= 120) | (frame >= 170 && frame <= 180) | (frame >= 230 && frame <= 240) | (frame >= 290 && frame <= 300) | (frame >= 350 && frame <= 360)){
    //     SDL_SetTextureAlphaMod(objTexture, 128);
    // }
    // if ((frame >= 50 && frame <= 360) && (frame % 60 >= 0 && frame % 60 <= 10)) {
    //     SDL_SetTextureAlphaMod(objTexture, 128);
    // }
    if (frame >= 50 && frame <= 60) {
        SDL_SetTextureAlphaMod(objTexture, ((-25.5*frame)+1530));
    }

    if (frame >= 110 && frame <= 120) {
        SDL_SetTextureAlphaMod(objTexture, ((-25.5*frame)+(1530*2)));
    }

    if (frame >= 170 && frame <= 180) {
        SDL_SetTextureAlphaMod(objTexture, ((-25.5*frame)+(1530*3)));
    }

    if (frame >= 230 && frame <= 240) {
        SDL_SetTextureAlphaMod(objTexture, ((-25.5*frame)+(1530*4)));
    }

    if (frame >= 290 && frame <= 300) {
        SDL_SetTextureAlphaMod(objTexture, ((-25.5*frame)+(1530*5)));
    }

    if (frame >= 350 && frame <= 360) {
        SDL_SetTextureAlphaMod(objTexture, ((-25.5*frame)+(1530*6)));
    }
//////////////////////////
    if (frame >= 60 && frame <= 70) {
        SDL_SetTextureAlphaMod(objTexture, ((25.5*frame)-1530));
    }

    if (frame >= 120 && frame <= 130) {
        SDL_SetTextureAlphaMod(objTexture, ((25.5*frame)-(1530*2)));
    }

    if (frame >= 180 && frame <= 190) {
        SDL_SetTextureAlphaMod(objTexture, ((25.5*frame)-(1530*3)));
    }

    if (frame >= 240 && frame <= 250) {
        SDL_SetTextureAlphaMod(objTexture, ((25.5*frame)-(1530*4)));
    }

    if (frame >= 300 && frame <= 310) {
        SDL_SetTextureAlphaMod(objTexture, ((25.5*frame)-(1530*5)));
    }

    if (frame >= 360) {
        SDL_SetTextureAlphaMod(objTexture, ((25.5*frame)-(1530*6)));
    }
    // if ((frame >= 40 && frame <= 60) || 
    //     (frame >= 100 && frame <= 120) || 
    //     (frame >= 160 && frame <= 180) || 
    //     (frame >= 220 && frame <= 240) || 
    //     (frame >= 280 && frame <= 300) || 
    //     (frame >= 340 && frame <= 360))  {
        
    //     int alpha_mod = ((-25.5 * frame) + (1530 * ((frame - 40) / 60)));
    //     SDL_SetTextureAlphaMod(objTexture, alpha_mod);
    //     std::cout << alpha_mod << std::endl;
    // }

    // if ((frame >= 60 && frame <= 80) ||
    //     (frame >= 120 && frame <= 140) ||
    //     (frame >= 180 && frame <= 200) ||
    //     (frame >= 240 && frame <= 260) ||
    //     (frame >= 300 && frame <= 320) ||
    //     (frame >= 360)) {

    //     int alpha_mod = ((25.5 * frame) - (1530 * ((frame - 50) / 60)));
    //     SDL_SetTextureAlphaMod(objTexture, alpha_mod);
    // }

    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

}