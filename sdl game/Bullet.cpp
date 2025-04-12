#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet(SDL_Renderer* renderer, int x, int y)
    : renderer(renderer), speed(10) {
    texture = TextureManager::LoadTexture(renderer, "image/bullet.png");
    rect = {x, y, 50, 50};
}

void Bullet::update() {
    rect.y -= speed;
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

SDL_Rect Bullet::getRect() const {
    return rect;
}

bool Bullet::isOffScreen() const {
    return rect.y < 0;
}
