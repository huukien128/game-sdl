#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include<SDL_ttf.h>

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
    SDL_Texture* backgroundTexture;
    bool running;
    Player* player;
    std::vector<Enemy*> enemies;
    int score;
    int highScore;
    TTF_Font* font;
    SDL_Texture* scoreTexture = nullptr;
    SDL_Texture* highScoreTexture = nullptr;
    SDL_Rect scoreRect;
    SDL_Rect highScoreRect;
    void loadHighScore();
    void saveHighScore();
    TTF_Font* gameOverFont;
    bool isGameOver = false;

};

#endif
