#include "Player.h"

Player::Player(SDL_Renderer* renderer) : renderer(renderer), speed(10), rect{300, 500, 50, 50} {}

void Player::handleInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                rect.x -= speed;
                break;
            case SDLK_RIGHT:
                rect.x += speed;
                break;
        }
    }
}

void Player::update() {
    if (rect.x < 0) rect.x = 0;
    if (rect.x > 800 - rect.w) rect.x = 800 - rect.w;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Player::resetPosition() {
    rect = {300, 500, 50, 50};
}

SDL_Rect Player::getRect() {
    return rect;
}
