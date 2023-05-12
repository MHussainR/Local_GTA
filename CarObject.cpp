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
    // shape = new Shapes();
    // pivot = {moverRect.w/2, moverRect.h/4};
    // car_speed = 2;
    mod_car_src = {616, 51, 200, 390};
    mod_car_move = {600, 400, mod_car_src.w, mod_car_src.h};
    this->type = type;
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

        if (angle >= 360 - 5)
        {
            angle -= 360;
        }
        else if (angle <= 0)
        {
            angle += 360;
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
        // if (intersects = false)
        // {
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
            // }
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
    // shape->draw_rect(renderer, moverRect.x, moverRect.y, moverRect.w, moverRect.h);
    // SDL_RenderDrawRect(renderer, &moverRect);
    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &moverRect, angle, &pivot, flip);
    // Rotation(x, y);
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // Rotation();
    // shape->Draw_circle(renderer, x_pos, y_pos, 100);

    // SDL_RenderDrawRect(renderer, &moverRect);
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // shape->Draw_circle(renderer, x_pos+moverRect.w/4, y_pos+moverRect.h/4, 75);
}

// void CarObject::Render(SDL_Rect rect)
// {
//     // GameObject::Render();

//     SDL_RenderCopyEx(renderer, objTexture, &srcRect, &moverRect, angle, &pivot, flip);
//     Rotation(rect);
// }

void CarObject::Render()
{
    // GameObject::Render();

    SDL_RenderCopyEx(renderer, objTexture, &srcRect, &moverRect, angle, &pivot, flip);
    // Rotation();
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

// void CarObject::Rotation(SDL_Rect p_moverRect)
// {
//     float theta;
//     // if (angle > 0)
//     //     theta = ((angle+5) * 180) / M_PI;
//     // else
//     theta = ((angle)*180) / M_PI;

//     // float sin = std::sin(theta);
//     // float cos = std::cos(theta);

//     // float w_0 = (moverRect.x - pivot.x)*cos - (moverRect.y - pivot.y)*sin;
//     // float h_0 = (moverRect.x - pivot.x)*sin + (moverRect.y - pivot.y)*cos;

//     // float w_1 = (moverRect.x + moverRect.w - pivot.x)*cos - (moverRect.y - pivot.y)*sin;
//     // float h_1 = (moverRect.x + moverRect.w - pivot.x)*sin + (moverRect.y - pivot.y)*cos;

//     // float w_2 = (moverRect.x - pivot.x)*cos - (moverRect.y + moverRect.h - pivot.y)*sin;
//     // float h_2 = (moverRect.x - pivot.x)*sin + (moverRect.y + moverRect.h - pivot.y)*cos;

//     // float w_3 = (moverRect.x + moverRect.w - pivot.x)*cos - (moverRect.y + moverRect.h - pivot.y)*sin;
//     // float h_3 = (moverRect.x + moverRect.w - pivot.x)*sin + (moverRect.y + moverRect.h - pivot.y)*cos;

//     // // float w_0 = (pivot.x)*cos - (pivot.y)*sin;
//     // // float h_0 = (pivot.x)*sin + (pivot.y)*cos;

//     // // float w_1 = (moverRect.w)*cos;
//     // // float h_1 = (moverRect.w)*sin;

//     // // float w_2 = -(moverRect.h)*sin;
//     // // float h_2 = (moverRect.h)*cos;

//     // // float w_3 = (moverRect.w)*cos - (moverRect.h)*sin;
//     // // float h_3 = (moverRect.w)*sin + (moverRect.h)*cos;

//     // shape->Draw_circle(renderer, pivot.x + w_0, pivot.y + h_0, 5);
//     // shape->Draw_circle(renderer, pivot.x + w_1, pivot.y + h_1, 5);
//     // shape->Draw_circle(renderer, pivot.x + w_2, pivot.y + h_2, 5);
//     // shape->Draw_circle(renderer, pivot.x + w_3, pivot.y + h_3, 5);

//     // std::cout << moverRect.x << "   " << moverRect.y << std::endl;

//     SDL_Rect bbox1 = {0, 0, p_moverRect.w, p_moverRect.h};
//     SDL_Rect bbox2 = {0, 0, moverRect.w, moverRect.h};

//     SDL_Point corners1[4] = {{bbox1.x, bbox1.y}, {bbox1.x + bbox1.w, bbox1.y}, {bbox1.x + bbox1.w, bbox1.y + bbox1.h}, {bbox1.x, bbox1.y + bbox1.h}};
//     SDL_Point corners2[4] = {{bbox2.x, bbox2.y}, {bbox2.x + bbox2.w, bbox2.y}, {bbox2.x + bbox2.w, bbox2.y + bbox2.h}, {bbox2.x, bbox2.y + bbox2.h}};

//     for (int i = 0; i < 4; ++i)
//     {
//         SDL_Point &p1 = corners1[i];
//         SDL_Point &p2 = corners2[i];

//         // Rotate the points around their centers
//         SDL_Point tmp1 = {p1.x - bbox1.w / 2, p1.y - bbox1.h / 2};
//         SDL_Point tmp2 = {p2.x - bbox2.w / 2, p2.y - bbox2.h / 2};

//         RotatePoint(tmp1, 0);
//         RotatePoint(tmp2, theta);

//         p1.x = tmp1.x + bbox1.w / 2 + p_moverRect.x;
//         p1.y = tmp1.y + bbox1.h / 2 + p_moverRect.y;

//         p2.x = tmp2.x + bbox2.w / 2 + moverRect.x;
//         p2.y = tmp2.y + bbox2.h / 2 + moverRect.y;
//     }

//     // Check for intersection between the rotated rectangles
//     SDL_Rect rect1_rotated = {corners1[0].x, corners1[0].y, corners1[2].x - corners1[0].x, corners1[2].y - corners1[0].y};
//     SDL_Rect rect2_rotated = {corners2[0].x, corners2[0].y, corners2[2].x - corners2[0].x, corners2[2].y - corners2[0].y};

//     intersects = SDL_IntersectRect(&rect1_rotated, &rect2_rotated, NULL);
//     if (intersects)
//         std::cout << "intersecting"<< std::endl;
//     else
//         std::cout << "not intersecting"<< std::endl;
// }

// void CarObject::RotatePoint(SDL_Point &point, double rad)
// {
//     // double rad = angle * M_PI / 180.0;
//     int x = point.x;
//     int y = point.y;
//     point.x = static_cast<int>(x * std::cos(rad) - y * std::sin(rad));
//     point.y = static_cast<int>(x * std::sin(rad) + y * std::cos(rad));
// }(

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
                } else {
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