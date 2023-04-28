#pragma once
#include <string>
#include <map>
// #include "game.hpp"
#include <SDL_ttf.h>

class FontManager {
public:
    FontManager();
    ~FontManager();
    static FontManager& instance() {
        static FontManager fm;
        return fm;
    }

    bool loadFont(const std::string& fontPath, int fontSize, const std::string& key);
    TTF_Font* getFont(const std::string& key);
    void renderText(SDL_Renderer* renderer, const char* text, int x, int y, int size, SDL_Color color);
    void setFont(const std::string fontPath);

private:
    
    std::map<std::string, TTF_Font*> m_fonts;
    std::string m_path;
};