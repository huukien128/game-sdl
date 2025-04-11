#include "Enemy.h"
#include "TextureManager.h"
#include <cstdlib>
#include<algorithm>

Enemy::Enemy(SDL_Renderer* renderer, int x, int y)
    : renderer(renderer), speed(3), direction(1) {
    texture = TextureManager::LoadTexture(renderer, "image/enemy.png");
    rect = {x, y, 50, 50};
}

void Enemy::update() {
    rect.x += direction * speed;
    if (rect.x < 0 || rect.x > 800) {
        reverseDirection();
    }

    for (Bomb* bomb : bombs) {
        bomb->update();
    }

    bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](Bomb* b) {
        if (b->isOffScreen()) {
            delete b;
            return true;
        }
        return false;
    }), bombs.end());
}

void Enemy::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    for (Bomb* bomb : bombs) {
        bomb->render(renderer);
    }
}

void Enemy::resetPosition() {
    rect.x = rand() % 500 + 250;
    rect.y = rand() % 350     ;

}

void Enemy::reverseDirection() {
    direction = -direction;
}

SDL_Rect Enemy::getRect() const {
    return rect;
}

void Enemy::dropBomb() {
    bombs.push_back(new Bomb(renderer, rect.x + rect.w / 2, rect.y + rect.h));
}

std::vector<Bomb*>& Enemy::getBombs() {
    return bombs;
}

void Enemy::clearBombs() {
    for (Bomb* bomb : bombs) delete bomb;
    bombs.clear();
}
