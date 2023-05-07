#include "Shapes.hpp"
#include <cmath>

Shapes::Shapes() {}

void Shapes::Draw_circle(SDL_Renderer *renderer, int x, int y, int radius)
{
    int diameter = radius * 2;
    int x_pos = radius - 1;
    int y_pos = 0;
    int tx = 1;
    int ty = 1;
    int error = tx - diameter;

    // Set the drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    while (x_pos >= y_pos)
    {
        // octant 1
        SDL_RenderDrawLine(renderer, x + x_pos, y - y_pos, x - x_pos, y - y_pos);
        // octant 2
        SDL_RenderDrawLine(renderer, x + y_pos, y - x_pos, x - y_pos, y - x_pos);
        // octant 3
        SDL_RenderDrawLine(renderer, x - y_pos, y - x_pos, x - x_pos, y - y_pos);
        // octant 4
        SDL_RenderDrawLine(renderer, x - x_pos, y - y_pos, x - y_pos, y + x_pos);
        // octant 5
        SDL_RenderDrawLine(renderer, x - x_pos, y + y_pos, x + x_pos, y + y_pos);
        // octant 6
        SDL_RenderDrawLine(renderer, x - y_pos, y + x_pos, x + y_pos, y + x_pos);
        // octant 7
        SDL_RenderDrawLine(renderer, x + y_pos, y + x_pos, x + x_pos, y + y_pos);
        // octant 8
        SDL_RenderDrawLine(renderer, x + x_pos, y + y_pos, x + y_pos, y - x_pos);

        if (error <= 0)
        {
            y_pos++;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            x_pos--;
            tx += 2;
            error += tx - diameter;
        }
    }

    // Set the drawing color back to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void Shapes::Draw_Line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{

    SDL_Color originalColor;
    SDL_GetRenderDrawColor(renderer, &originalColor.r, &originalColor.g, &originalColor.b, &originalColor.a);

    // Set the draw color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Draw the line
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    // Reset the draw color to the original color
    SDL_SetRenderDrawColor(renderer, originalColor.r, originalColor.g, originalColor.b, originalColor.a);
}

float Shapes::Distance(float x1, float y1, float x2, float y2)
{
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

void Shapes::draw_rect(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};

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