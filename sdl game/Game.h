#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "Player.h"
#include "Enemy.h"

class Game {
public:
    Game();
    ~Game();
    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;  // Biến lưu background
    bool running;
    Player player;
    std::vector<Enemy*> enemies;
};

#endif // GAME_H
