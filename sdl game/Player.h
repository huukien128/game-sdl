#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <vector>
#include "Bullet.h"

class Player {

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
    int speed;
    std::vector<Bullet*> bullets;
public:
    Player(SDL_Renderer* renderer);
    void handleInput(const SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
    void fire();
    SDL_Rect getRect() const;
    std::vector<Bullet*>& getBullets();
    void removeBullet(Bullet* bullet);

};

#endif
