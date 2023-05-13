#include "CarObject.hpp"
#include <cmath>
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "Money.hpp"
// #include "SDL_rotozoom.h"

// #include "Shapes.hpp"

CarObject::CarObject(const char *texturesheet, SDL_Renderer *ren, int x, int y, std::string type) : GameObject(texturesheet, ren, x, y)
{
    angle = 0;
    stolen = false;
    flip = SDL_FLIP_NONE;
    shape = new Shapes();
    intersects = false;
    modification_state = false;
    mod_bg = TextureManager::LoadTexture("assets/car_mod_bg.png", renderer);
    mod_price = 0;
    mod_car_src = {616, 51, 200, 390};
    mod_car_move = {600, 400, mod_car_src.w, mod_car_src.h};
    this->type = type;

    // Set the source rectangle based on the car type
    if (type == "Normal")
        srcRect = {616, 51, 200, 390};
    else if (type == "Ambulance")
        srcRect = {281, 653, 289, 486};
    else if (type == "Taxi")
        srcRect = {62, 732, 182, 410};
    else if (type == "Small")
        srcRect = {1187, 50, 186, 232};
    else if (type == "Jeep")
        srcRect = {891, 51, 214, 397};
    else if (type == "MiniTruck")
        srcRect = {1491, 48, 171, 433};
    else if (type == "Police")
        srcRect = {1750, 41, 177, 399};
    else if (type == "Truck")
        srcRect = {275, 51, 317, 502};

    font = new FontManager();
    font->setFont("fonts/Orbitron-VariableFont_wght.ttf");

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
    // Update the mover rectangle based on the position and dimensions of the car object
    moverRect = {x_pos, y_pos, srcRect.w / 3, srcRect.h / 3};
}

void CarObject::Update(char direction, int x, int y, bool movex, bool movey)
{
    // Update the car object based on player input
    // GameObject::Update(direction, x, y);
    if (stolen == true)
    {
        GameObject::Update(direction, x, y);

        // Update the angle of rotation based on direction
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
        else if (angle <= 90 && angle - 5 >= 0)
        {
            if (direction == 'u' | direction == 'l')
            {
                angle -= 5;
            }
        }
        else if (angle + 5 <= 180 && angle >= 90)
        {
            if (direction == 'd' | direction == 'l')
            {
                angle += 5;
            }
        }
        else if (angle <= 180 && angle - 5 >= 90)
        {
            if (direction == 'r' | direction == 'u')
            {
                angle -= 5;
            }
        }
        else if (angle + 5 <= 270 && angle >= 180)
        {
            if (direction == 'l' | direction == 'u')
            {
                angle += 5;
            }
        }
        else if (angle <= 270 && angle - 5 >= 180)
        {
            if (direction == 'd' | direction == 'r')
            {
                angle -= 5;
            }
        }
        else if (angle + 5 <= 360 && angle >= 270)
        {
            if (direction == 'u' | direction == 'r')
            {
                angle += 5;
            }
        }
        else if (angle <= 360 && angle - 5 >= 270)
        {
            if (direction == 'l' | direction == 'd')
            {
                angle -= 5;
            }
        }

        // Wrap the angle value to keep it within the range of 0 to 360 degrees
        if (angle >= 360 - 5)
        {
            angle -= 360;
        }
        else if (angle <= 0)
        {
            angle += 360;
        }
    }
    else
    {
        // Move the car object based on the direction and player input
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
    }
}

void CarObject::Render(int x, int y)
{
    // Render the car object with rotation
    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &moverRect, angle, &pivot, flip);
}

void CarObject::Render()
{
    // Render the car object without rotation
    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &moverRect, angle, &pivot, flip);
}

bool CarObject::getStatus()
{
    // Get the status of the car object (whether it is stolen or not)
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
        }
    }
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

        if (angle >= 360 - 5)
        {
            angle -= 360;
        }
        else if (angle <= 0)
        {
            angle += 360;
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

void CarObject::Rotation(int x, int y)
{
    float theta;
    // if (angle > 0)
    //     theta = ((angle+5) * 180) / M_PI;
    // else
    theta = ((angle)*M_PI) / 180;

    float sin = std::sin(theta);
    float cos = std::cos(theta);

    float w_0 = (moverRect.x - pivot.x - x) * cos - (moverRect.y - pivot.y - y) * sin;
    float h_0 = (moverRect.x - pivot.x - x) * sin + (moverRect.y - pivot.y - y) * cos;

    float w_1 = (moverRect.x + moverRect.w - pivot.x - x) * cos - (moverRect.y - pivot.y - y) * sin;
    float h_1 = (moverRect.x + moverRect.w - pivot.x - x) * sin + (moverRect.y - pivot.y - y) * cos;

    float w_2 = (moverRect.x - pivot.x - x) * cos - (moverRect.y + moverRect.h - pivot.y - y) * sin;
    float h_2 = (moverRect.x - pivot.x - x) * sin + (moverRect.y + moverRect.h - pivot.y - y) * cos;

    float w_3 = (moverRect.x + moverRect.w - pivot.x - x) * cos - (moverRect.y + moverRect.h - pivot.y - y) * sin;
    float h_3 = (moverRect.x + moverRect.w - pivot.x - x) * sin + (moverRect.y + moverRect.h - pivot.y - y) * cos;

    shape->Draw_circle(renderer, x - w_0, y - h_0, 5);
    shape->Draw_circle(renderer, x - w_1, y - h_1, 5);
    shape->Draw_circle(renderer, x - w_2, y - h_2, 5);
    shape->Draw_circle(renderer, x - w_3, y - h_3, 5);

    // std::cout << moverRect.x << "   " << moverRect.y << std::endl;
}

void CarObject::modification(Money *m)
{
    static int turn = 0;
    static int keyPress = 0;

    switch (abs(turn))
    {
    case 0:
        mod_car_src = {616, 51, 200, 390};
        type = "Normal";
        mod_price = 25000;
        break;
    case 1:
        mod_car_src = {281, 653, 289, 486};
        type = "Ambulance";
        mod_price = 60000;
        break;
    case 2:
        mod_car_src = {62, 732, 182, 410};
        type = "Taxi";
        mod_price = 20000;
        break;
    case 3:
        mod_car_src = {1187, 50, 186, 232};
        type = "Small";
        mod_price = 10000;
        break;
    case 4:
        mod_car_src = {891, 51, 214, 397};
        type = "Jeep";
        mod_price = 65000;
        break;
    case 5:
        mod_car_src = {1491, 48, 171, 433};
        type = "MiniTruck";
        mod_price = 100000;
        break;
    case 6:
        mod_car_src = {1750, 41, 177, 399};
        type = "Police";
        mod_price = 90000;
        break;
    case 7:
        mod_car_src = {275, 51, 317, 502};
        type = "Truck";
        mod_price = 120000;
        break;
    default:
        break;
    }

    turn = turn % 8;
    if (keyPress == 1)
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_LEFT:
                turn--;
                break;
            case SDLK_RIGHT:
                turn++;
                break;
            case SDLK_RETURN:
                if (m->getMoney() >= mod_price)
                {
                    modification_state = false;
                    m->setMoney(m->getMoney() - mod_price);
                    if (type == "Normal")
                        srcRect = {616, 51, 200, 390};
                    else if (type == "Ambulance")
                        srcRect = {281, 653, 289, 486};
                    else if (type == "Taxi")
                        srcRect = {62, 732, 182, 410};
                    else if (type == "Small")
                        srcRect = {1187, 50, 186, 232};
                    else if (type == "Jeep")
                        srcRect = {891, 51, 214, 397};
                    else if (type == "MiniTruck")
                        srcRect = {1491, 48, 171, 433};
                    else if (type == "Police")
                        srcRect = {1750, 41, 177, 399};
                    else if (type == "Truck")
                        srcRect = {275, 51, 317, 502};
                }
                else
                {
                    modification_state = false;
                }
                break;
            case SDLK_g:
                modification_state = false;
                break;
            default:
                break;
            }
        }
    }
    if (Game::event.type == SDL_KEYUP)
        keyPress = 1;
    else
        keyPress = 0;

    mod_car_move = {600 - mod_car_src.w / 2, 400 - mod_car_src.h / 2, mod_car_src.w, mod_car_src.h};
}

bool CarObject::get_modification_state()
{
    return modification_state;
}

void CarObject::set_modification_state(bool var)
{
    modification_state = var;
}

void CarObject::modification_render()
{
    char buffer[10];
    sprintf(buffer, "%d", mod_price);
    SDL_Rect sr = {0, 0, 1200, 800};
    SDL_RenderCopy(renderer, mod_bg, &sr, &sr);
    SDL_RenderCopy(renderer, objTexture, &mod_car_src, &mod_car_move);
    font->renderText(renderer, buffer, 550, 100, 25, {255, 255, 255, 255});
}