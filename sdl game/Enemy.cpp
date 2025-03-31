#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, int x, int y) : renderer(renderer), speed(2), rect{x, y, 50, 50} {}

void Enemy::update() {
    rect.y += speed;
    if (rect.y > 600) {
        resetPosition();
    }
}

void Enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Enemy::resetPosition() {
    rect.x = rand() % 750;
    rect.y = rand() % 500 - 600;
}

SDL_Rect Enemy::getRect() {
    return rect;
}
