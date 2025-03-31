#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player {
public:
    Player(SDL_Renderer* renderer);
    void handleInput(const SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
    void resetPosition();
    SDL_Rect getRect();

private:
    SDL_Renderer* renderer;
    int speed;
    SDL_Rect rect;
};

#endif // PLAYER_H
