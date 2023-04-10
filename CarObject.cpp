#include"CarObject.hpp"

CarObject::CarObject(const char* texturesheet, SDL_Renderer* ren, int x, int y) : GameObject(texturesheet, ren, x, y) {
    angle = 0;
    stolen = false;
};


void CarObject::Update(){
    GameObject::Update();
    // if (stolen == false){

    // }
    moverRect = {x_pos, y_pos, srcRect.w/3, srcRect.h/3};
}

void CarObject::Update(char direction, int x, int y){
    GameObject::Update(direction, x, y);
    // if (angle <= 90){
    //     if (direction == 'r'){
    //         angle += 10;
    //     }
    // }
    // if (angle <= 180){
    //     if (direction == 'd'){
    //         angle += 10;
    //     }
    // }
}

void CarObject::Render(){
    // GameObject::Render();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &moverRect, angle, NULL, flip);
}