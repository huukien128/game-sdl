#ifndef BOMB_H
#define BOMB_H

#include <SDL.h>

class Bomb {
public:
    Bomb(SDL_Renderer* renderer, int x, int y);
    void update();
    void render(SDL_Renderer* renderer);
    SDL_Rect getRect() const;
    bool isOffScreen() const;

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
    int speed;
};

#endif
