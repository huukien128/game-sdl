#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include<SDL_ttf.h>
#include<string>


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
    std::vector<std::string> background_ids;
    std::vector<SDL_Texture*> backgroundTextures;
    int current_stage ;
    int background_scroll ;
    const float scroll_speed ;
    bool running;
    Player* player;
   std::vector<Enemy*> enemies;
   int score;
   int highScore;
   TTF_Font* font;
   SDL_Texture* scoreTexture;
   SDL_Texture* highScoreTexture;
   SDL_Rect scoreRect;
   SDL_Rect highScoreRect;
   void loadHighScore();
   void saveHighScore();
   TTF_Font* gameOverFont;
   bool isGameOver;

};

#endif
