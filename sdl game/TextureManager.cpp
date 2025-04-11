#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* renderer, const std::string& filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        std::cerr << "Failed to load texture: " << filePath << ", Error: " << IMG_GetError() << std::endl;
    }
    return texture;
}
