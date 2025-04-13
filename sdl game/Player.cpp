#include "Player.h"
#include "TextureManager.h"
#include <algorithm>
#include"SoundManager.h"
Player::Player(SDL_Renderer* renderer)
    : renderer(renderer), rect{300, 500, 75, 75}, speed(80) {
    texture = TextureManager::LoadTexture(renderer, "image/player.png");
}

void Player::handleInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                rect.x -= speed;
                break;
            case SDLK_RIGHT:
                rect.x += speed;
                break;
            case SDLK_SPACE:

                fire();
                break;
        }
    }
}

void Player::update() {
    if (rect.x < 0) rect.x = 0;
    if (rect.x > 750) rect.x = 750;

    for (size_t i = 0; i < bullets.size(); ++i) {
        bullets[i]->update();
        if (bullets[i]->isOffScreen()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            --i;
        }
    }
}

void Player::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    for (Bullet* bullet : bullets) {
        bullet->render(renderer);
    }
}

void Player::fire() {
    bullets.push_back(new Bullet(renderer, rect.x + rect.w/5.5 , rect.y));
     SoundManager::getInstance().playSound("shoot");
}

SDL_Rect Player::getRect() const {
    return rect;
}

std::vector<Bullet*>& Player::getBullets() {
    return bullets;
}

void Player::removeBullet(Bullet* bullet) {
    auto it = std::find(bullets.begin(), bullets.end(), bullet);
    if (it != bullets.end()) {
        delete *it;
        bullets.erase(it);
    }
}
