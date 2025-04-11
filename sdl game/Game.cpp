#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include <cstdlib>
#include<SDL_image.h>
#include "FontManager.h"
#include <fstream>

Game::Game() : window(nullptr), renderer(nullptr), backgroundTexture(nullptr), running(false), player(nullptr),score(0), highScore(0),
    scoreTexture(nullptr), highScoreTexture(nullptr) {}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) return false;
    if (TTF_Init() == -1) return false;
     loadHighScore();

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    backgroundTexture = TextureManager::LoadTexture(renderer, "image/bgr.jpg");
    player = new Player(renderer);

    for (int i = 0; i < 10; ++i) {
        int x = rand() % 500 + 150;
        int y = rand() % 200;
        enemies.push_back(new Enemy(renderer, x, y));
    }
    font = FontManager::LoadFont("Font/font.ttf", 24);
    if (!font) {
    std::cerr << "Failed to load font.\n";
    return false;
    }

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
                running = false;
            }
        }
    }

    for (Bullet* bullet : player->getBullets()) {
        for (Enemy* enemy : enemies) {
                SDL_Rect bulletRect = bullet->getRect();
                SDL_Rect enemyRect = enemy->getRect();
           if (SDL_HasIntersection(&bulletRect, &enemyRect)) {
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
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    player->render(renderer);

    for (Enemy* enemy : enemies) {
        enemy->render(renderer);
    }
  std::string scoreText = "Score: " + std::to_string(score);
  std::string highScoreText = "High Score: " + std::to_string(highScore);
  if (scoreTexture) SDL_DestroyTexture(scoreTexture);
  if (highScoreTexture) SDL_DestroyTexture(highScoreTexture);
  SDL_Color white = {255, 255, 255, 255};
  scoreTexture = FontManager::RenderText(scoreText, white, font, renderer);
  highScoreTexture = FontManager::RenderText(highScoreText, white, font, renderer);
   scoreRect = {20, 10, 0, 0};
   highScoreRect = {20, 40, 0, 0};

  SDL_QueryTexture(scoreTexture, nullptr, nullptr, &scoreRect.w, &scoreRect.h);
  SDL_QueryTexture(highScoreTexture, nullptr, nullptr, &highScoreRect.w, &highScoreRect.h);
  if (scoreTexture) {
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
}
  if (highScoreTexture) {
    SDL_RenderCopy(renderer, highScoreTexture, nullptr, &highScoreRect);
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
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



bool Game::isRunning() {
    return running;
}
