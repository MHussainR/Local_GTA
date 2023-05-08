#include "RayCaster.hpp"
#include <cmath>
#include <iostream>
#include "Textures/wall1.ppm"
#include "Textures/wall11.ppm"
#include "Textures/rockywall.ppm"
#include "Textures/wall_textures.ppm"
// 1, police wall
// 2, police door
// 3, police window
// 4, brick wall
// 5, red gate middle
// 6, red gate right
// 7, red gate left


RayCaster::RayCaster(SDL_Renderer *ren)
{
    renderer = ren;
    inside = false;
    x_pos = 600;
    y_pos = 750;
    shape = new Shapes();
    mapX = 30;
    mapY = 20;
    mapS = 40;
    angle = -M_PI_2;
    mapview = false;
    deltax = std::cos(angle) * 5;
    deltay = std::sin(angle) * 5;
}

RayCaster::~RayCaster(){
    delete shape;
}

void RayCaster::Update(int val)
{
    static int temp = 0;
    if (temp == 1)
    {
        if (val > 1)
        {
            inside = true;
            if (val == 2) // parking
            {
                for (int i = 0; i < 600; i++)
                    map[i] = map_parking[i];
            }
            else if (val == 3) // police station
            {
                for (int i = 0; i < 600; i++)
                    map[i] = map_police_station[i];
            }
            else if (val == 4) // houses
            {
                for (int i = 0; i < 600; i++)
                    map[i] = map_house[i];
            }
        }
    }
    if (val == 1)
        temp = 1;
    else
        temp = 0;

    if (Game::event.type == SDL_KEYDOWN)
    {
        if (Game::event.key.keysym.sym == SDLK_g)
        {
            inside = false;
            angle = -M_PI_2;
            x_pos = 600;
            y_pos = 740;
        }
    }
    // std::cout << angle << '\n';
}

void RayCaster::Update2(int val)
{
    static int temp = 0;
    if (temp == 1)
    {
        if (val == 2)
            inside = true;
    }
    if (val == 1)
        temp = 1;
    else
        temp = 0;

    int xo = 0;
    if (deltax < 0)
    {
        xo = -20;
    }
    else
    {
        xo = 20;
    }
    int yo = 0;
    if (deltay < 0)
    {
        yo = -20;
    }
    else
    {
        yo = 20;
    }
    int ipx = x_pos / 40, ipx_add_xo = (x_pos + xo) / 40, ipx_sub_xo = (x_pos - xo) / 40;
    int ipy = y_pos / 40, ipy_add_yo = (y_pos + yo) / 40, ipy_sub_yo = (y_pos - yo) / 40;

    if (Game::event.type == SDL_KEYDOWN)
    {
        if (Game::event.key.keysym.sym == SDLK_g)
        {
            inside = false;
        }

        else if (Game::event.key.keysym.sym == SDLK_UP)
        {
            if (map[ipy * mapX + ipx_add_xo] == 0)
            {
                x_pos += deltax;
            }
            if (map[ipy_add_yo * mapX + ipx] == 0)
            {
                y_pos += deltay;
            }
            if (map[ipy_add_yo * mapX + ipx] == -1)
            {
                inside = false;
                x_pos = 600;
                y_pos = 740;
                angle = -M_PI_2;
            }
            // x_pos += deltax;
            // y_pos += deltay;
        }
        else if (Game::event.key.keysym.sym == SDLK_DOWN)
        {
            if (map[ipy * mapX + ipx_sub_xo] == 0)
            {
                x_pos -= deltax;
            }
            if (map[ipy_sub_yo * mapX + ipx] == 0)
            {
                y_pos -= deltay;
            }
            // x_pos -= deltax;
            // y_pos -= deltay;
        }
        else if (Game::event.key.keysym.sym == SDLK_LEFT)
        {
            angle -= 0.03;
            if (angle <= 0)
            {
                angle += M_PI * 2;
            }
            deltax = std::cos(angle) * 5;
            deltay = std::sin(angle) * 5;
        }
        else if (Game::event.key.keysym.sym == SDLK_RIGHT)
        {
            angle += 0.03;
            if (angle >= M_PI * 2)
            {
                angle -= M_PI * 2;
            }
            deltax = std::cos(angle) * 5;
            deltay = std::sin(angle) * 5;
        }
        if (Game::event.key.keysym.sym == SDLK_TAB)
        {
            mapview = true;
        }
    }
    if (Game::event.type == SDL_KEYUP)
    {
        if (Game::event.key.keysym.sym == SDLK_TAB)
        {
            mapview = false;
        }
    }
    // std::cout << angle << '\n';
}

void RayCaster::drawRays3d()
{
    int mh, mv, red, green, blue, mm;
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, disT, shade;
    ra = angle - 0.0174533 * 30;
    if (ra < 0)
    {
        ra += 2 * M_PI;
    }
    if (ra > 2 * M_PI)
    {
        ra -= 2 * M_PI;
    }

    for (r = 0; r < 120; r++)
    {
        //---Check Horizontal Lines---
        float disH = 1000000, hx = x_pos, hy = y_pos;
        dof = 0;
        float aTan = -1 / std::tan(ra);
        if (ra > M_PI)
        {
            ry = (((int)y_pos / 40) * 40) - 0.0001;
            rx = (y_pos - ry) * aTan + x_pos;
            yo = -40;
            xo = -yo * aTan;
        }
        if (ra < M_PI)
        {
            ry = (((int)y_pos / 40) * 40) + 40;
            rx = (y_pos - ry) * aTan + x_pos;
            yo = 40;
            xo = -yo * aTan;
        }
        if (ra == 0 || ra == M_PI)
        {
            rx = x_pos;
            ry = y_pos;
            dof = 30;
        } // looking straight left or right

        while (dof < 30)
        {
            mx = (rx / 40);
            my = (ry / 40);
            mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] > 0)
            {
                mh = map[mp];
                hx = rx;
                hy = ry;
                disH = shape->Distance(x_pos, y_pos, hx, hy);
                dof = 30; // hit wall
            }
            else
            {
                rx += xo;
                ry += yo;
                dof += 1; // next line
            }
        }

        //---Check Vertical Lines---
        float disV = 1000000, vx = x_pos, vy = y_pos;
        dof = 0;
        float nTan = -std::tan(ra);
        if (ra > M_PI_2 && ra < 3 * M_PI_2)
        {
            rx = (((int)x_pos / 40) * 40) - 0.0001;
            ry = (x_pos - rx) * nTan + y_pos;
            xo = -40;
            yo = -xo * nTan;
        } // looking left
        if (ra < M_PI_2 || ra > 3 * M_PI_2)
        {
            rx = (((int)x_pos / 40) * 40) + 40;
            ry = (x_pos - rx) * nTan + y_pos;
            xo = 40;
            yo = -xo * nTan;
        } // looking right
        if (ra == 0 || ra == M_PI)
        {
            rx = x_pos;
            ry = y_pos;
            dof = 30;
        } // looking straight up or down
        while (dof < 30)
        {
            mx = (rx / 40);
            my = (ry / 40);
            mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] > 0)
            {
                mv = map[mp];
                vx = rx;
                vy = ry;
                disV = shape->Distance(x_pos, y_pos, vx, vy);
                dof = 30; // hit wall
            }
            else
            {
                rx += xo;
                ry += yo;
                dof += 1; // next line
            }
        }

        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disT = disV;
            shade = 0.5;
            mm = mv - 1;
            // if (mv == 2)
            // SDL_SetRenderDrawColor(renderer, 255, 100, 100, SDL_ALPHA_OPAQUE);
            // else
            // SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        }
        if (disH < disV)
        {
            rx = hx;
            ry = hy;
            disT = disH;
            shade = 1;
            mm = mh - 1;
            // if (mh == 2)
            // SDL_SetRenderDrawColor(renderer, 255 * 0.7, 100 * 0.7, 100 * 0.7, SDL_ALPHA_OPAQUE);
            // else
            // SDL_SetRenderDrawColor(renderer, 255 * 0.7, 255 * 0.7, 255 * 0.7, SDL_ALPHA_OPAQUE);
        }

        // 3D walls
        float ca = angle - ra;
        if (ca < 0)
        {
            ca += 2 * M_PI;
        }
        if (ca > 2 * M_PI)
        {
            ca -= 2 * M_PI;
        }
        disT = disT * std::cos(ca); // fix fisheye
        float lineH = (mapS * 800) / disT;
        float ty_step = 20.0 / (float)lineH;
        float ty_off = 0;
        if (lineH > 800)
        {
            ty_off = (lineH - 800) / 2.0;
            lineH = 800;
        }                              // line height
        float line0 = 400 - lineH / 2; // line offset

        //---draw walls---
        int y;
        float ty = ty_off * ty_step + mm * 20;
        float tx; //= (int)(rx / 2) % 20;
        if (shade == 1)
        {
            tx = (int)(rx / 2) % 20;
            if (ra > M_PI)
            {
                tx = 19 - tx;
            }
        }
        else
        {
            tx = (int)(ry / 2) % 20;
            if (ra > M_PI_2 && ra < 3 * M_PI_2)
            {
                tx = 19 - tx;
            }
        }

        for (y = 0; y < lineH; y++)
        {
            int pixel = ((int)ty * 20 + (int)tx) * 3;
            red = wall_textures[pixel + 0] * shade;
            green = wall_textures[pixel + 1] * shade;
            blue = wall_textures[pixel + 2] * shade;
            if (mapview)
                SDL_RenderDrawLine(renderer, x_pos, y_pos, rx, ry);
            else
            {
                SDL_SetRenderDrawColor(renderer, int(red), int(green), int(blue), SDL_ALPHA_OPAQUE);
                SDL_Rect re = {r * 10, y + line0, 10, 10};
                SDL_RenderFillRect(renderer, &re);
            }
            ty += ty_step;
        }

        ra += 0.0174533 * 0.5;
        if (ra < 0)
        {
            ra += 2 * M_PI;
        }
        if (ra > 2 * M_PI)
        {
            ra -= 2 * M_PI;
        }

        // if (map[mp] == -1)
        //     inside = false;
    }
}

bool RayCaster::getState()
{
    return inside;
}

void RayCaster::Render()
{
    if (mapview)
    {
        int x, y, xo, yo;
        for (y = 0; y < mapY; y++)
        {
            for (x = 0; x < mapX; x++)
            {
                if (map[y * mapX + x] > 0)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                    xo = x * mapS;
                    yo = y * mapS;
                    shape->draw_rect(renderer, xo, yo, mapS, mapS);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 76, 76, 76, 0);
                }
            }
        }
        drawRays3d();
        shape->draw_rect(renderer, x_pos - 5, y_pos - 5, 10, 10);
        SDL_SetRenderDrawColor(renderer, 76, 76, 76, 0);
    }
    else
    {
        SDL_Rect re = {0, 0, 1200, 400};
        SDL_SetRenderDrawColor(renderer, 0, 0, 200, 0);
        SDL_RenderFillRect(renderer, &re);
        re = {0, 400, 1200, 400};
        SDL_SetRenderDrawColor(renderer, 0, 200, 0, 0);
        SDL_RenderFillRect(renderer, &re);
        drawRays3d();
    }

    // SDL_SetRenderDrawColor(renderer, 76, 76, 76, 0);
    // shape->draw_rect(renderer, x_pos, y_pos, 50, 50);
    // shape->Draw_Line(renderer, x_pos, y_pos, x_pos + deltax * 5, y_pos + deltay * 5);
}