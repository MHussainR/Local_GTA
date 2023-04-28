#include "CarObject.hpp"
// #include "Shapes.hpp"

CarObject::CarObject(const char *texturesheet, SDL_Renderer *ren, int x, int y, std::string type) : GameObject(texturesheet, ren, x, y)
{
    angle = 0;
    stolen = false;
    flip = SDL_FLIP_NONE;
    // shape = new Shapes();
    // pivot = {moverRect.w/2, moverRect.h/4};
    // car_speed = 2;
    if (type == "Normal")
        srcRect = {616, 51, 200, 390};
    else if (type == "Ambulance")
        srcRect = {281, 653, 289, 486};
    else if (type == "Taxi")
        srcRect = {62, 732, 182, 410};

    pivot = {srcRect.w / 6, srcRect.h / 12};
};

CarObject::CarObject(const char *texturesheet, SDL_Renderer *ren, int x, int y) : GameObject(texturesheet, ren, x, y)
{
    angle = 0;
    stolen = false;
    flip = SDL_FLIP_NONE;
    pivot = {srcRect.w / 6, srcRect.h / 12};
};

void CarObject::Update()
{
    // GameObject::Update();
    // if (stolen == false){

    // }
    moverRect = {x_pos, y_pos, srcRect.w / 3, srcRect.h / 3};
}

// void CarObject::Update(char direction, int x, int y, int map_pos_x, int map_pos_y){
//     if (stolen == true){
//         GameObject::Update(direction, x, y);
//     } else {
//         x_pos = x_pos + x;
//         y_pos = y_pos + y;

//     }
// }

void CarObject::Update(char direction, int x, int y, bool movex, bool movey)
{
    // GameObject::Update(direction, x, y);
    if (stolen == true)
    {
        GameObject::Update(direction, x, y);
        if (y_pos > 400)
        {
            inside_box_y = false;
        }
        if (x_pos > 600)
        {
            inside_box_x = false;
        }
        if (angle + 5 <= 90 && angle >= 0)
        {
            if (direction == 'r' | direction == 'd')
            {
                angle += 5;
            }
        }
        if (angle <= 90 && angle - 5 >= 0)
        {
            if (direction == 'u' | direction == 'l')
            {
                angle -= 5;
            }
        }
        if (angle + 5 <= 180 && angle >= 90)
        {
            if (direction == 'd' | direction == 'l')
            {
                angle += 5;
            }
        }
        if (angle <= 180 && angle - 5 >= 90)
        {
            if (direction == 'r' | direction == 'u')
            {
                angle -= 5;
            }
        }
        if (angle + 5 <= 270 && angle >= 180)
        {
            if (direction == 'l' | direction == 'u')
            {
                angle += 5;
            }
        }
        if (angle <= 270 && angle - 5 >= 180)
        {
            if (direction == 'd' | direction == 'r')
            {
                angle -= 5;
            }
        }
        if (angle + 5 <= 360 && angle >= 270)
        {
            if (direction == 'u' | direction == 'r')
            {
                angle += 5;
            }
        }
        if (angle <= 360 && angle - 5 >= 270)
        {
            if (direction == 'l' | direction == 'd')
            {
                angle -= 5;
            }
        }

        // if (angle == 360){
        //     angle = 0;
        // } else if (angle == 0) {
        //     angle = 360;
        // }
        // if (angle+5 <= 180 && angle >= 90){
        //     if (direction == 'd'){
        //         angle += 5;
        //     } else if (direction == 'r'){
        //         angle -= 5;
        //     }
        // }
        // if (angle+5 <= 270 && angle >= 180){
        //     if (direction == 'l'){
        //         angle += 5;
        //     } else if (direction == 'd'){
        //         angle -= 5;
        //     }
        // }
        // if (direction == 'u'){
        //     if (angle != 0)

        // }
    }
    else
    {
        if (movey == false)
        {
            if (direction == 'u')
            {
                if (y != 0)
                    y_pos += car_speed;
            }
            else if (direction == 'd')
            {
                if (y != 3200)
                    y_pos -= car_speed;
            }
        }
        if (movex == false)
        {
            if (direction == 'l')
            {
                if (x != 0)
                    x_pos += car_speed;
            }
            else if (direction == 'r')
            {
                if (x != 4800)
                    x_pos -= car_speed;
            }
        }
        // moverRect = {x_pos-srcRect.w/6, y_pos-srcRect.h/6, srcRect.w/3, srcRect.h/3};
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
    // SDL_Rect rect = {x-x_pos-srcRect.w/6, y-y_pos-srcRect.h/6, 100, 100};
    // SDL_RenderDrawRect(renderer, &rect);
}

void CarObject::Render(int x, int y)
{
    // GameObject::Render();

    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &moverRect, angle, &pivot, flip);
    // shape->Draw_circle(renderer, x_pos+moverRect.w/4, y_pos+moverRect.h/4, 75);
}

void CarObject::Render()
{
    // GameObject::Render();

    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &moverRect, angle, &pivot, flip);
}

bool CarObject::getStatus()
{
    return stolen;
}

void CarObject::setStatus(int x, int y)
{
    if (stolen == true)
    {
        stolen = false;
    }
    else if (abs((x - x_pos - moverRect.w / 4) * (x - x_pos - moverRect.w / 4)) + abs((y - y_pos - moverRect.h / 4) * (y - y_pos - moverRect.h / 4)) <= 75 * 75)
    {
        if (stolen == false)
        {
            stolen = true;
            // car_speed = 5;
            // x_pos = 600;
            // y_pos = 400;
            // inside_box_x = true;
            // inside_box_y = true;
        }
        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    // CarObject::draw_circle(renderer, x-x_pos-moverRect.w/4, y-y_pos-moverRect.h/4, 75);

    // CarObject::draw_circle(renderer, x-x_pos, y-y_pos, 100);
    // std::cout << abs((x-x_pos-moverRect.w/4)*(x-x_pos-moverRect.w/4)) + abs((y-y_pos-moverRect.h/4)*(y-y_pos-moverRect.h/4)) << std::endl;
}

void CarObject::Reset()
{
    x_pos = 600 * 2;
    y_pos = 400 * 2;
    angle = 0;
    stolen = false;
}

void CarObject::setStatus(bool val)
{
    stolen = val;
}

void CarObject::set_speed(char direction)
{
    this->direction = direction;
    if (direction == 'n')
    {
        this->dx = 0;
        this->dy = 0;
    }
    else if (direction == 'r')
    {
        this->dx = 5;
        this->dy = 0;
    }
    else if (direction == 'l')
    {
        this->dx = -5;
        this->dy = 0;
    }
    else if (direction == 'u')
    {
        this->dx = 0;
        this->dy = -5;
    }
    else if (direction == 'd')
    {
        this->dx = 0;
        this->dy = 5;
    }
}

void CarObject::Update(int speedx, int speedy)
{
    if (stolen)
    {
        if (angle + 5 <= 90 && angle >= 0)
        {
            if (direction == 'r' | direction == 'd')
            {
                angle += 5;
            }
        }
        if (angle <= 90 && angle - 5 >= 0)
        {
            if (direction == 'u' | direction == 'l')
            {
                angle -= 5;
            }
        }
        if (angle + 5 <= 180 && angle >= 90)
        {
            if (direction == 'd' | direction == 'l')
            {
                angle += 5;
            }
        }
        if (angle <= 180 && angle - 5 >= 90)
        {
            if (direction == 'r' | direction == 'u')
            {
                angle -= 5;
            }
        }
        if (angle + 5 <= 270 && angle >= 180)
        {
            if (direction == 'l' | direction == 'u')
            {
                angle += 5;
            }
        }
        if (angle <= 270 && angle - 5 >= 180)
        {
            if (direction == 'd' | direction == 'r')
            {
                angle -= 5;
            }
        }
        if (angle + 5 <= 360 && angle >= 270)
        {
            if (direction == 'u' | direction == 'r')
            {
                angle += 5;
            }
        }
        if (angle <= 360 && angle - 5 >= 270)
        {
            if (direction == 'l' | direction == 'd')
            {
                angle -= 5;
            }
        }
        
        if (speedx != 0)
        {
            if (speedx < 0)
            {
                this->dx = -5;
                this->direction = 'l';
            }
            else
            {
                this->dx = 5;
                this->direction = 'r';
            }
            this->dy = 0;
        }
        else if (speedy != 0)
        {
            if (speedy < 0)
            {
                this->dy = -5;
                this->direction = 'u';
            }
            else
            {
                this->dy = 5;
                this->direction = 'd';
            }
            this->dx = 0;
        }
        else
        {
            this->dy = 0;
            this->dx = 0;
            this->direction = 'n';
        }
        // y_pos = y_pos + this->dy;
        // x_pos = x_pos + this->dx;
    }
    else
    {
        if (this->direction == 'n')
        {
            y_pos = y_pos - speedy;
            x_pos = x_pos - speedx;
        }
        else if (this->direction == 'l' || this->direction == 'r')
        {
            y_pos = y_pos - speedy;
            x_pos = x_pos - speedx + this->dx;
        }
        else if (this->direction == 'u' || this->direction == 'd')
        {
            y_pos = y_pos - speedy + this->dy;
            x_pos = x_pos - speedx;
        }
    }
    Update();
}