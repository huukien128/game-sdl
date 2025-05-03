#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class FontManager {
public:
    static TTF_Font* LoadFont(const std::string& fileName, int fontSize);
    static void CloseFont(TTF_Font* font);
    static SDL_Texture* RenderText(const std::string& message, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);
};

#endif
