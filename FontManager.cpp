#include "FontManager.hpp"

FontManager::FontManager() {
    TTF_Init();
    // m_path = "fonts/StampedPersonalUseRegular-ywJm3.ttf";
}

FontManager::~FontManager() {
    for (auto& f : m_fonts) {
        TTF_CloseFont(f.second);
    }
    TTF_Quit();
}

bool FontManager::loadFont(const std::string& fontPath, int fontSize, const std::string& key) {
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr) {
        printf("Failed to load font %s\n", fontPath.c_str());
        return false;
    }

    m_fonts[key] = font;
    return true;
}

void FontManager::setFont(const std::string fontPath){
    m_path = fontPath;
}

TTF_Font* FontManager::getFont(const std::string& key) {
    auto search = m_fonts.find(key);
    if (search != m_fonts.end()) {
        return search->second;
    }
    printf("Font not found for key %s\n", key.c_str());
    return nullptr;
}

void FontManager::renderText(SDL_Renderer* renderer, const char* text, int x, int y, int size, SDL_Color color) {
    // Set the font size
    TTF_Font* font = TTF_OpenFont(m_path.c_str(), size);
    if (!font) {
        // Handle error
        return;
    }

    // Render the text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);
    if (!textSurface) {
        TTF_CloseFont(font);
        // Handle error
        return;
    }

    // Convert the surface to a texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!texture) {
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        // Handle error
        return;
    }

    // Set the render draw color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Set the destination rectangle for the text
    SDL_Rect dstRect = { x, y, textSurface->w, textSurface->h };

    // Render the texture
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    // Clean up
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}
