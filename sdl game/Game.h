#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Menu.h"
#include <SDL_ttf.h>
#include <string>

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Menu* menu;
    std::vector<std::string> background_ids;
    std::vector<SDL_Texture*> backgroundTextures;
    int current_stage;
    bool running;
    bool isMenuActive;
    Player* player;
    std::vector<Enemy*> enemies;
    int score;
    int highScore;
    TTF_Font* font;
    SDL_Texture* scoreTexture;
    SDL_Texture* highScoreTexture;
    SDL_Rect scoreRect;
    SDL_Rect highScoreRect;
    TTF_Font* gameOverFont;
    bool isGameOver;
    int level;

public:
    Game();
    ~Game();
    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    void onGameOver();
    bool isRunning();
    void loadHighScore();
    void saveHighScore();
    void restartGame();

};

#endif
