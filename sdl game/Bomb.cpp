#include "Bomb.h"
#include "TextureManager.h"

Bomb::Bomb(SDL_Renderer* renderer, int x, int y)
    : renderer(renderer), speed(6) {
    texture = TextureManager::LoadTexture(renderer, "image/boom.png");
    rect = {x, y, 30, 30};
}

void Bomb::update() {
    rect.y += speed;
}

void Bomb::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

SDL_Rect Bomb::getRect() const {
    return rect;
}

bool Bomb::isOffScreen() const {
    return rect.y > 600;
}
