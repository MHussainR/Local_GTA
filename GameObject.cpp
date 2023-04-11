#include "GameObject.hpp"
#include "TextureManager.hpp"
#include<iostream>


GameObject::GameObject(const char *textursheet, SDL_Renderer *ren, int x, int y)
{
    renderer = ren;
    objTexture = TextureManager::LoadTexture(textursheet, ren);


    x_pos = x;
    y_pos = y;
    inside_box_x = false;
    inside_box_y = false;
}

void GameObject::Update()
{
    // x_pos++;
    // y_pos++;

    // srcRect = {771, 48, 136, 192};
    moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};
}

void GameObject::Update(char direction){
    if (direction == 'u'){
        // if (moverRect.y <= 400)
            y_pos -= 5;
        // std::cout << moverRect.y << std::endl;
    } else if (direction == 'd'){
        // if (moverRect.y >= 3600)
            y_pos += 5;
    } else if (direction == 'l'){
        // if (moverRect.x <= 600)
            x_pos -= 5;
    } else if (direction == 'r'){
        // if (moverRect.x >= 5400)
            x_pos += 5;
    }
    // moverRect = {x_pos, y_pos, srcRect.w, srcRect.h};
}

void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &moverRect);
}

int GameObject::getXpos(){
    return x_pos;
}

int GameObject::getYpos(){
    return y_pos;
}

SDL_Texture* GameObject::getObjTexture(){
    return objTexture;
}

void GameObject::Update(char direction, int x, int y){
    if (x <= 0){
        if (x_pos <= 600){
            inside_box_x = true;
        } else {
            if (direction == 'l'){
                x_pos -= 5;
                inside_box_x = true;
            }
            inside_box_x = false;
        }
    }
    if (x >= 4800){
        if (x_pos >= 600){
            inside_box_x = true;
        } else {
            if (direction == 'r'){
                x_pos += 5;
                inside_box_x = true;
            }
            inside_box_x = false;
        }
    }
    if (y <= 0){
        if (y_pos <= 400){
            inside_box_y = true;
        } else {
            if (direction == 'u'){
                y_pos -= 5;
                inside_box_y = true;
            } 
            inside_box_y = false;
        }
    }
    if (y >= 3200){
        if (y_pos >= 400){
            inside_box_y = true;
        } else {
            if (direction == 'd'){
                y_pos += 5;
                inside_box_y = true;
            }
            inside_box_y = false;
        }
    }

    if (inside_box_y){
        if (direction == 'u'){
            // if (y_pos != 400)
                y_pos -= 5;
            // std::cout << moverRect.y << std::endl;
        } else if (direction == 'd'){
            // if (y_pos != 3600)
                y_pos += 5;
        } 
    }
    if (inside_box_x){
        if (direction == 'l'){
            // if (x_pos != 600)
                x_pos -= 5;
                // std::cout << moverRect.x << std::endl;
        } else if (direction == 'r'){
            // if (x_pos <= 600)
                x_pos += 5;
                
        }
    }

    // std::cout << x_pos << " " << y_pos << std::endl;
}

void GameObject::Reset(){
    
}