#include "TextureManager.hpp"

SDL_Texture *TextureManager::LoadTexture(const char *texture, SDL_Renderer *ren)
{
    // Load the image file and create an SDL surface
    SDL_Surface *tempSurface = IMG_Load(texture);

    // Create an SDL texture from the loaded surface
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempSurface);

    // Free the loaded surface from memory
    SDL_FreeSurface(tempSurface);

    // Return the created texture
    return tex;
}
