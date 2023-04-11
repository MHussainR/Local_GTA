#include"CarObject.hpp"

CarObject::CarObject(const char* texturesheet, SDL_Renderer* ren, int x, int y) : GameObject(texturesheet, ren, x, y) {
    angle = 0;
    stolen = false;
    flip = SDL_FLIP_NONE;
    // car_speed = 2;
};


void CarObject::Update(){
    // GameObject::Update();
    // if (stolen == false){

    // }
    moverRect = {x_pos, y_pos, srcRect.w/3, srcRect.h/3};
}

// void CarObject::Update(char direction, int x, int y, int map_pos_x, int map_pos_y){
//     if (stolen == true){
//         GameObject::Update(direction, x, y);
//     } else {
//         x_pos = x_pos + x;
//         y_pos = y_pos + y;

//     }
// }
void CarObject::draw_circle(SDL_Renderer *renderer, int x, int y, int radius) {
    int diameter = radius * 2;
    int x_pos = radius - 1;
    int y_pos = 0;
    int tx = 1;
    int ty = 1;
    int error = tx - diameter;
    
    while (x_pos >= y_pos) {
        // octant 1
        SDL_RenderDrawPoint(renderer, x + x_pos, y - y_pos);
        // octant 2
        SDL_RenderDrawPoint(renderer, x + y_pos, y - x_pos);
        // octant 3
        SDL_RenderDrawPoint(renderer, x - y_pos, y - x_pos);
        // octant 4
        SDL_RenderDrawPoint(renderer, x - x_pos, y - y_pos);
        // octant 5
        SDL_RenderDrawPoint(renderer, x - x_pos, y + y_pos);
        // octant 6
        SDL_RenderDrawPoint(renderer, x - y_pos, y + x_pos);
        // octant 7
        SDL_RenderDrawPoint(renderer, x + y_pos, y + x_pos);
        // octant 8
        SDL_RenderDrawPoint(renderer, x + x_pos, y + y_pos);

        if (error <= 0) {
            y_pos++;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            x_pos--;
            tx += 2;
            error += tx - diameter;
        }
    }

}
void CarObject::Update(char direction, int x, int y, bool movex, bool movey){
    // GameObject::Update(direction, x, y);
    if (stolen == true){
        GameObject::Update(direction, x, y);
        if (y_pos > 400){
            inside_box_y = false;
        }
        // if (angle <= 90){
        //     if (direction == 'r'){
        //         angle += 2;
        //     }
        // }
    } else {
        if (movey == false){
            if (direction == 'u'){
                if (y != 0)
                    y_pos += car_speed;
            } else if (direction == 'd'){
                if (y != 3200)
                    y_pos -= car_speed;
            }
        } 
        if (movex == false){
            if (direction == 'l'){
                if (x!= 0)
                    x_pos += car_speed;
            } else if (direction == 'r'){
                if (x != 4800)
                    x_pos -= car_speed;
            }
        }
        moverRect = {x_pos-srcRect.w/6, y_pos-srcRect.h/6, srcRect.w/3, srcRect.h/3};
    }
    // std::cout << inside_box_y << std::endl;
    
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
    
    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &moverRect, angle, NULL, flip);
}

bool CarObject::getStatus(){
    return stolen;
}


void CarObject::setStatus(int x, int y){
    if (stolen == true){
        stolen = false;
    } else if (abs((x-x_pos-srcRect.w/6)*(x-x_pos-srcRect.w/6)) + abs((y_pos-srcRect.h/6)*(y-y_pos-srcRect.h/6)) <= 150*150){
        if (stolen == false){
            stolen = true;
            // car_speed = 5;
            // x_pos = 600;
            // y_pos = 400;
            // inside_box_x = true;
            // inside_box_y = true;
        }
    } 
    
    // CarObject::draw_circle(renderer, x-x_pos, y-y_pos, 100);
    std::cout << x_pos << "   "  << y_pos << std::endl;
}

void CarObject::Reset(){
    x_pos = 600*2;
    y_pos = 400*2;
}


void CarObject::set_speed(int speed){
    this->car_speed = speed;
}