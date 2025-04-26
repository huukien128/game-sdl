#include "Enemy.h"
#include "TextureManager.h"
#include <cstdlib>
#include<algorithm>

Enemy::Enemy(SDL_Renderer* renderer, int x, int y)
    : renderer(renderer), speed(3), x_direction(1) , y_direction(0){
    texture = TextureManager::LoadTexture(renderer, "image/enemy3.png");
    rect = {x, y, 80, 80};
}

void Enemy::update() {
    rect.x += x_direction * speed;
    rect.y += x_direction * speed/2;
    if (rect.x+rect.w <0 || rect.x+rect.w > 880) {
        reverseXDirection();
    }
     if (rect.y+rect.h <500 || rect.y+rect.h >600) {
        reverseYDirection();
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
    rect.x = rand() % 720;
    rect.y = rand() % 350     ;

}

void Enemy::reverseXDirection() {
    x_direction = -x_direction;
}
void Enemy::reverseYDirection() {
    y_direction = -y_direction;
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
void Enemy::setSpeed(float s) {
    speed = s;
}

