#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <string>

class TextureManager {
public:
    static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath);
};

#endif
