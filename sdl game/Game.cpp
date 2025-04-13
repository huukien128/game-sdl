#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include <cstdlib>
#include<SDL_image.h>
#include "FontManager.h"
#include <fstream>
#include "SoundManager.h"

Game::Game()
    : window(nullptr), renderer(nullptr),
      background_ids(), backgroundTextures(),
      current_stage(0), background_scroll(0), scroll_speed(1),
      running(false), player(nullptr),
      score(0), highScore(0),font(nullptr),
       scoreTexture(nullptr),
      highScoreTexture(nullptr),
      gameOverFont(nullptr),
      isGameOver(false) {}


Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) return false;
    if (TTF_Init() == -1) return false;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return false;
     loadHighScore();

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    background_ids = {"bgr1", "bgr2", "bgr3"};
    backgroundTextures.push_back(TextureManager::LoadTexture(renderer, "image/bgr.png"));
    backgroundTextures.push_back(TextureManager::LoadTexture(renderer, "image/bgr2.png"));
    backgroundTextures.push_back(TextureManager::LoadTexture(renderer, "image/bgr3.png"));
    player = new Player(renderer);

    for (int i = 0; i < 12; ++i) {
        int x = rand() % 800;
        int y = rand() %250;
        enemies.push_back(new Enemy(renderer, x, y));
    }
    font = FontManager::LoadFont("Font/font.ttf", 15);
    gameOverFont = FontManager::LoadFont("Font/font2.ttf", 48);
    SoundManager::getInstance().loadMusic("bgm", "sound/bgr.mp3");
    SoundManager::getInstance().playMusic("bgm", -1);
    SoundManager::getInstance().loadSound("explosion", "sound/exp.wav");
    SoundManager::getInstance().loadSound("shoot", "sound/shoot.wav");
    SoundManager::getInstance().loadSound("hit", "sound/hit.mp3");

    running = true;
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = false;
        player->handleInput(event);
    }
}

void Game::update() {
    player->update();

    for (Enemy* enemy : enemies) {
        if (rand() % 10000 < 25) enemy->dropBomb();
        enemy->update();

        for (Bomb* bomb : enemy->getBombs()) {
                SDL_Rect playerRect = player->getRect();
                SDL_Rect bombRect = bomb->getRect();
          if (SDL_HasIntersection(&playerRect, &bombRect)) {
                std::cout << "Player destroyed! Game Over!" << std::endl;
                 SoundManager::getInstance().playSound("explosion");
                isGameOver = true;
                running = false;
            }
        }
    }

    for (Bullet* bullet : player->getBullets()) {
        for (Enemy* enemy : enemies) {
                SDL_Rect bulletRect = bullet->getRect();
                SDL_Rect enemyRect = enemy->getRect();
           if (SDL_HasIntersection(&bulletRect, &enemyRect)) {
                SoundManager::getInstance().playSound("hit");
                player->removeBullet(bullet);
                enemy->resetPosition();
                 score += 10;
              if (score > highScore) {
                 highScore = score;
                     }
                break;
            }
        }
    }
  background_scroll += scroll_speed;
    if (background_scroll >= 600) {
        background_scroll = 0;
    }
    int new_stage = score / 300;

    current_stage = new_stage % backgroundTextures.size();
}
void Game::render() {
    SDL_RenderClear(renderer);
   SDL_Rect dest1 = {0, background_scroll, 800, 600};
   SDL_Rect dest2 = {0, background_scroll - 600, 800, 600};

SDL_RenderCopy(renderer, backgroundTextures[current_stage], NULL, &dest1);
SDL_RenderCopy(renderer, backgroundTextures[current_stage], NULL, &dest2);

    player->render(renderer);

    for (Enemy* enemy : enemies) {
        enemy->render(renderer);
    }

  std::string scoreText = "Score: " + std::to_string(score);
  std::string highScoreText = "High Score: " + std::to_string(highScore);
  if (scoreTexture) SDL_DestroyTexture(scoreTexture);
  if (highScoreTexture) SDL_DestroyTexture(highScoreTexture);
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color red = {255, 0, 0, 255};

  scoreTexture = FontManager::RenderText(scoreText, white, font, renderer);
  scoreRect = {20, 10, 0, 0};
  SDL_QueryTexture(scoreTexture, nullptr, nullptr, &scoreRect.w, &scoreRect.h);

    if (scoreTexture) {
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
}

  highScoreTexture = FontManager::RenderText(highScoreText, red , font, renderer);
  highScoreRect = {20, 40, 0, 0};
  SDL_QueryTexture(highScoreTexture, nullptr, nullptr, &highScoreRect.w, &highScoreRect.h);

   if (highScoreTexture) {
    SDL_RenderCopy(renderer, highScoreTexture, nullptr, &highScoreRect);
}

  if (isGameOver) {
    SDL_Texture* gameOverTexture = FontManager::RenderText("GAME OVER", red, gameOverFont, renderer);
        SDL_Rect gameOverRect={350,300,0,0};
        SDL_QueryTexture(gameOverTexture, nullptr, nullptr, &gameOverRect.w, &gameOverRect.h);
        SDL_RenderCopy(renderer, gameOverTexture, nullptr, &gameOverRect);
        SDL_DestroyTexture(gameOverTexture);
}

if (isGameOver) {
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
}


    SDL_RenderPresent(renderer);
}
void Game::loadHighScore() {
    std::ifstream file("highscore1.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    } else {
        highScore = 0;
    }
}
void Game::saveHighScore() {
    std::ofstream file("highscore1.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}
void Game::clean() {
    for (Enemy* enemy : enemies) {
        enemy->clearBombs();
        delete enemy;
    }
    enemies.clear();
    delete player;
    saveHighScore();
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (highScoreTexture) SDL_DestroyTexture(highScoreTexture);
    FontManager::CloseFont(font);
    SoundManager::getInstance().clean();
    for (auto& tex : backgroundTextures) {
    SDL_DestroyTexture(tex);
}
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



bool Game::isRunning() {
    return running;
}
