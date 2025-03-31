#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>

class Enemy {
public:
    Enemy(SDL_Renderer* renderer, int x, int y);
    void update();
    void render(SDL_Renderer* renderer);
    void resetPosition();
    SDL_Rect getRect();

private:
    SDL_Renderer* renderer;
    int speed;
    SDL_Rect rect;
};

#endif // ENEMY_H
