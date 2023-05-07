#include "CircularMenu.hpp"
#include <cmath>

CircularMenu::CircularMenu(SDL_Renderer *renderer, int centred_x, int centred_y)
{
    this->renderer = renderer;
    this->menu_texture = TextureManager::LoadTexture("assets/circular menu.png", renderer);
    this->radius = 550;
    this->centerX = centred_x;
    this->centerY = centred_y;
    moverRect.x = centred_x - radius / 2;
    moverRect.y = centred_y - radius / 2;
    this->NUM_GUNS = 8;
    this->sectors = (2 * M_PI) / NUM_GUNS;
    this->is_open = false;
}

void CircularMenu::Render(double _angle, int _radius)
{
    if (this->is_open)
    {
        SDL_RenderCopy(renderer, menu_texture, &srcRect, &moverRect);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Color color;
        for (int i = 0; i < NUM_GUNS; i++)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            float angle = (i * 2 * M_PI) / NUM_GUNS;
            int x1 = centerX + (((radius - 278) / 2) * cos(angle)); //+ radius * cos(angle);
            int y1 = centerY + (((radius - 278) / 2) * sin(angle)); //+ radius * sin(angle);
            int x2 = centerX + ((radius - 20) / 2) * cos(angle);
            int y2 = centerY + ((radius - 20) / 2) * sin(angle);

            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        if (_radius < 275 && _radius > ((this->radius - 298) / 2))
        {
            if (_angle > 0)
            {
                _angle = _angle - 360;
            }
            _angle = -_angle;
            _angle = _angle * (M_PI / 180);
            int region = _angle / sectors;
            SDL_SetRenderDrawColor(renderer, 77, 77, 255, 255);
            int numSegments = (int)(abs((((region + 1) * 2 * M_PI) / NUM_GUNS) - ((region * 2 * M_PI) / NUM_GUNS)) / (M_PI / 180.0)) * 2;
            double angleStep = (((((region + 1) * sectors)) - ((region * sectors)))) / numSegments;
            double angle2 = ((region * 2 * M_PI) / NUM_GUNS);
            for (int i = 0; i < numSegments; i++)
            {
                int point1x = centerX + (int)((radius / 2) * cos(angle2));
                int point1y = centerY - (int)((radius / 2) * sin(angle2));
                angle2 += angleStep;
                int point2x = centerX + (int)((radius / 2) * cos(angle2));
                int point2y = centerY - (int)((radius / 2) * sin(angle2));

                SDL_RenderDrawLine(renderer, point1x, point1y, point2x, point2y);
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
    }
}

void CircularMenu::setState(bool isOpen)
{
    this->is_open = isOpen;
}

bool CircularMenu::getState()
{
    return this->is_open;
}