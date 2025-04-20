#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include <cstdlib>
#include <SDL_image.h>
#include "FontManager.h"
#include <fstream>
#include "SoundManager.h"
#include "Enemy.h"
#include "Bomb.h"

Game::Game()
    : window(nullptr), renderer(nullptr),
      menu(nullptr),
      background_ids(),
      backgroundTextures(),
      current_stage(0),
      running(false),
      isMenuActive(true),
      player(nullptr),
      score(0), highScore(0),
      font(nullptr),
      scoreTexture(nullptr),
      highScoreTexture(nullptr),
      gameOverFont(nullptr),
      isGameOver(false),
      level(1) {}

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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    menu = new Menu(renderer);

    background_ids = {"bgr1", "bgr2", "bgr3"};
    backgroundTextures.push_back(TextureManager::LoadTexture(renderer, "image/bgr.png"));
    backgroundTextures.push_back(TextureManager::LoadTexture(renderer, "image/bgr2.png"));
    backgroundTextures.push_back(TextureManager::LoadTexture(renderer, "image/bgr3.png"));

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

        if (isMenuActive) {
            menu->handleEvents(event);

            if (menu->isStartGameSelected() || menu->isPlayAgainSelected()) {
                restartGame();
                isMenuActive = false;
                isGameOver = false;
                menu->setGameOverMenu(true);
                menu->reset();
            } else if (menu->isExitSelected()) {
                running = false;
            }
        } else {
            player->handleInput(event);
        }
    }
}

void Game::update() {
    if (isMenuActive) return;

    if (isGameOver) {
        SDL_Delay(1000);
        isMenuActive = true;
        menu->reset();
        return;
    }

    player->update();
    level = 1 + (score / 500);

    for (Enemy* enemy : enemies) {
        if (rand() % 10000 < 5) {
            enemy->dropBomb();
        }
        enemy->update();

        for (Bomb* bomb : enemy->getBombs()) {
            SDL_Rect playerRect = player->getRect();
            SDL_Rect bombRect = bomb->getRect();
            if (SDL_HasIntersection(&playerRect, &bombRect)) {
                std::cout << "Player destroyed! Game Over!" << std::endl;
                SoundManager::getInstance().playSound("explosion");
                isGameOver = true;
                return;
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

    int textureCount = static_cast<int>(backgroundTextures.size());
    if (textureCount > 0) {
        current_stage = (score / 500) % textureCount;
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    if (isMenuActive) {
        menu->render();
    } else {
        SDL_Rect dest = {0, 0, 800, 600};
        SDL_RenderCopy(renderer, backgroundTextures[current_stage], NULL, &dest);

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
        SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);

        highScoreTexture = FontManager::RenderText(highScoreText, red, font, renderer);
        highScoreRect = {20, 40, 0, 0};
        SDL_QueryTexture(highScoreTexture, nullptr, nullptr, &highScoreRect.w, &highScoreRect.h);
        SDL_RenderCopy(renderer, highScoreTexture, nullptr, &highScoreRect);

        std::string levelText = "Level: " + std::to_string(level);
        SDL_Texture* levelTexture = FontManager::RenderText(levelText, red, font, renderer);
        SDL_Rect levelRect = {700, 20, 0, 0};
        SDL_QueryTexture(levelTexture, nullptr, nullptr, &levelRect.w, &levelRect.h);
        SDL_RenderCopy(renderer, levelTexture, nullptr, &levelRect);
        SDL_DestroyTexture(levelTexture);
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

void Game::restartGame() {
    score = 0;
    isGameOver = false;

    if (player) {
        delete player;
    }
    player = new Player(renderer);

    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    for (int i = 0; i < 12; ++i) {
        int x = rand() % 720;
        int y = rand() % 350;
        enemies.push_back(new Enemy(renderer, x, y));
    }
}

void Game::clean() {
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    delete player;
    player = nullptr;

    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (highScoreTexture) SDL_DestroyTexture(highScoreTexture);

    FontManager::CloseFont(font);
    FontManager::CloseFont(gameOverFont);
    SoundManager::getInstance().clean();

    for (auto& tex : backgroundTextures) {
        SDL_DestroyTexture(tex);
    }

    delete menu;
    menu = nullptr;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::isRunning() {
    return running;
}
