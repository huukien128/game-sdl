#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include <vector>
#include "Bomb.h"

class Enemy {
public:
    Enemy(SDL_Renderer* renderer, int x, int y);
    void update();
    void render(SDL_Renderer* renderer);
    void resetPosition();
    void reverseXDirection();
    void reverseYDirection();
    SDL_Rect getRect() const;

    void dropBomb();
    std::vector<Bomb*>& getBombs();
    void clearBombs();

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
    int speed;
    int x_direction;
     int y_direction;


    std::vector<Bomb*> bombs;
};

#endif
