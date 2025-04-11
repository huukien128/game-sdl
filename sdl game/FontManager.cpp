#include "FontManager.h"
#include <iostream>

TTF_Font* FontManager::LoadFont(const std::string& fileName, int fontSize) {
    TTF_Font* font = TTF_OpenFont(fileName.c_str(), fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    return font;
}

void FontManager::CloseFont(TTF_Font* font) {
    if (font) {
        TTF_CloseFont(font);
    }
}

SDL_Texture* FontManager::RenderText(const std::string& message, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
    if (!surface) {
        std::cerr << "TTF_RenderText Error: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

