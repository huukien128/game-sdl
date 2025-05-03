#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>

class Bullet {

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
    int speed;
public:
    Bullet(SDL_Renderer* renderer, int x, int y);
    void update();
    void render(SDL_Renderer* renderer);
    SDL_Rect getRect() const;
    bool isOffScreen() const;

};

#endif
