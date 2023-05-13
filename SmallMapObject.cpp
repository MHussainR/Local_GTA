#include "SmallMapObject.hpp"

SmallMapObject::SmallMapObject(const char *textursheet, SDL_Renderer *ren, int x, int y) : MapObject(textursheet, ren, x, y)
{
    // Constructor initializes the SmallMapObject with the provided texture sheet, renderer, and coordinates.
}

void SmallMapObject::Update()
{
    // Update the source and mover rectangles based on the position of the SmallMapObject.
    srcRect = {x_pos, y_pos, 2400, 1600};
    moverRect = {0, 0, srcRect.w / 10, srcRect.h / 10};
    // Call the Update function of the base class MapObject.
    // MapObject::Update();
}

void SmallMapObject::Update(char direction, bool movex, bool movey)
{
    // Update the SmallMapObject's position based on the provided direction and movement flags.
    // Call the Update function of the base class MapObject.
    MapObject::Update(direction, movex, movey);
}

void SmallMapObject::draw_black_rect(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    // Draw a black rectangle with a white fill on the provided renderer at the specified position and dimensions.
    SDL_Rect rect = {x, y, w, h};

    // Draw the border
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rect);

    // Draw the fill
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    rect.x += 1;
    rect.y += 1;
    rect.w -= 2;
    rect.h -= 2;
    SDL_RenderFillRect(renderer, &rect);
}

void SmallMapObject::Update(char direction, bool movex, bool movey, int speedx, int speedy)
{
    // Update the SmallMapObject's position and game speed based on the provided direction, movement flags, and game speeds.
    this->game_speed_x = speedx;
    this->game_speed_y = speedy;

    // Check if the direction is not 'n' (no movement)
    if (direction != 'n')
    {
        // Call the Update function with the direction and movement flags
        Update(direction, movex, movey);
    }

    // Call the Update function to update the position and other properties
    Update();
}

void SmallMapObject::Render()
{
    // Render the SmallMapObject on the screen.
    // Draw a black rectangle as the background for the SmallMapObject.
    draw_black_rect(renderer, 0, 0, moverRect.w, moverRect.h);

    // Render the texture of the SmallMapObject using the source and mover rectangles.
    SDL_RenderCopy(renderer, objTexture, &srcRect, &moverRect);
}
