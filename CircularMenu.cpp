#include "CircularMenu.hpp"
#include <cmath>

CircularMenu::CircularMenu(SDL_Renderer *renderer, int centred_x, int centred_y)
{
    this->renderer = renderer;
    this->menu_texture = TextureManager::LoadTexture("assets/circular menu.png", renderer);
    this->glow = TextureManager::LoadTexture("assets/circular menu_3.png", renderer);
    this->ar = TextureManager::LoadTexture("assets/AR.png", renderer);
    this->hg = TextureManager::LoadTexture("assets/HG.png", renderer);
    this->sg = TextureManager::LoadTexture("assets/SG.png", renderer);
    this->radius = 550;
    this->centerX = centred_x;
    this->centerY = centred_y;
    moverRect.x = centred_x - radius / 2;
    moverRect.y = centred_y - radius / 2;
    moverRect2.x = centred_x - (1200) / 2;
    moverRect2.y = centred_y - (1200) / 2;
    this->NUM_GUNS = 3;
    this->sectors = (2 * M_PI) / NUM_GUNS;
    this->is_open = false;
}

std::string CircularMenu::getGun(double _angle, int _radius)
{
    if (this->is_open)
    {
        if(_radius < 275 && _radius > ((this->radius - 298) / 2))
        {
            if (_angle > 0)
            {
                _angle = _angle - 360;
            }

            _angle = -_angle;
            _angle = _angle * (M_PI / 180);
            int region = _angle / sectors;
            switch (region)
            {
            case 0:
                return "AR";
                break;
            case 1:
                return "HG";
                break;
            case 2:
                return "SG";
                break;
            }
        }
    }
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
            double startAngle = (region * sectors);
            double endAngle = ((region + 1) * sectors);
            int x = centerX + (1000 * cos(startAngle));
            int y = centerY + (1000 * sin(startAngle));
            int x2 = centerX + (1000 * cos(endAngle));
            int y2 = centerY + (1000 * sin(endAngle));

            // if (x<x2 && y<y2)
            // {
            // moverRect2.x = x;
            // moverRect2.y = y;
            // = {x, y, x2, y2};
            // }
            // else if (x2 < x && y < y2)
            // {
            //     moverRect2 = {x2, y, x, y2};
            // }
            // else if (x < x2 && y2 < y)
            // {
            //     moverRect2 = {x, y2, x2, y};
            // }
            // else if (x2 < x && y2 < y)
            // {
            //     moverRect2 = {x2, y2, x, y};
            // }
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
            angle2 = ((region * 2 * M_PI) / NUM_GUNS);
            for (int i = 0; i < numSegments; i++)
            {
                int point1x = centerX + (int)(((radius-1) / 2) * cos(angle2));
                int point1y = centerY - (int)(((radius-1) / 2) * sin(angle2));
                angle2 += angleStep;
                int point2x = centerX + (int)(((radius-1) / 2) * cos(angle2));
                int point2y = centerY - (int)(((radius-1) / 2) * sin(angle2));

                SDL_RenderDrawLine(renderer, point1x, point1y, point2x, point2y);
            }
            angle2 = ((region * 2 * M_PI) / NUM_GUNS);
            for (int i = 0; i < numSegments; i++)
            {
                int point1x = centerX + (int)(((radius+1) / 2) * cos(angle2));
                int point1y = centerY - (int)(((radius+1) / 2) * sin(angle2));
                angle2 += angleStep;
                int point2x = centerX + (int)(((radius+1) / 2) * cos(angle2));
                int point2y = centerY - (int)(((radius+1) / 2) * sin(angle2));

                SDL_RenderDrawLine(renderer, point1x, point1y, point2x, point2y);
            }
            angle2 = ((region * 2 * M_PI) / NUM_GUNS);
            for (int i = 0; i < numSegments; i++)
            {
                int point1x = centerX + (int)(((radius + 2) / 2) * cos(angle2));
                int point1y = centerY - (int)(((radius + 2) / 2) * sin(angle2));
                angle2 += angleStep;
                int point2x = centerX + (int)(((radius + 2) / 2) * cos(angle2));
                int point2y = centerY - (int)(((radius + 2) / 2) * sin(angle2));

                SDL_RenderDrawLine(renderer, point1x, point1y, point2x, point2y);
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            // int segments = (int)(abs((((region + 1) * 2 * M_PI) / NUM_GUNS) - ((region * 2 * M_PI) / NUM_GUNS)) / (M_PI / 180.0)) * 2;
            // float angleStep = (((region + 1) * sectors) - (region * sectors)) / segments;
            // std::vector<SDL_FPoint> vertices;
            // for (int i = 0; i <= segments; ++i)
            // {
            //     float angle = (region * sectors) + angleStep * i;
            //     float x = centerX + radius * cos(angle);
            //     float y = centerY + radius * sin(angle);

            //     vertices.push_back({x, y});
            // }

            // SDL_SetTextureBlendMode(glow, SDL_BLENDMODE_BLEND);
            // for (size_t i = 0; i < vertices.size() - 1; ++i)
            // {
            //     SDL_Rect tt = {(int)(vertices[i].x - 4 / 2), (int)(vertices[i].y - 4 / 2), 4, 4};
            //     SDL_RenderCopyEx(renderer, glow, &srcRect2, &tt , atan2(vertices[i + 1].y - vertices[i].y, vertices[i + 1].x - vertices[i].x) * 180.0 / M_PI, NULL, SDL_FLIP_NONE);
            // }
            // SDL_RenderCopy(renderer, glow, &srcRect2, &moverRect2);

        }
        moverAR = {radius - 200, radius - 50, 40, 40};
        SDL_RenderCopy(renderer, ar, NULL, &moverAR);
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