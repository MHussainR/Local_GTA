#include "SmallMapObject.hpp"


SmallMapObject::SmallMapObject(const char *textursheet, SDL_Renderer *ren, int x, int y):MapObject(textursheet, ren, x, y){
    
}

void SmallMapObject::Update(){
    srcRect = {x_pos, y_pos, 2400, 1600};
    moverRect = {0, 0, srcRect.w/10, srcRect.h/10};
    // MapObject::Update();
}

void SmallMapObject::Update(char direction, bool movex, bool movey){
    MapObject::Update(direction, movex, movey);
}

void SmallMapObject::draw_black_rect(SDL_Renderer* renderer, int x, int y, int w, int h) {
    SDL_Rect rect = { x, y, w, h };
    
    // draw the border
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rect);

    // draw the fill
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    rect.x += 1;
    rect.y += 1;
    rect.w -= 2;
    rect.h -= 2;
    SDL_RenderFillRect(renderer, &rect);
}


void SmallMapObject::Render(){
    // SDL_Rect rect = {0, 0, moverRect.w, moverRect.h};
    // SDL_RenderDrawRect(renderer, &rect);
    draw_black_rect(renderer, 0, 0, moverRect.w, moverRect.h);
    SDL_RenderCopy(renderer, objTexture, &srcRect, &moverRect);
}