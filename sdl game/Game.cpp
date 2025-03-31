#include "Game.h"
#include <cstdlib>
#include <SDL_image.h>  // Để sử dụng IMG_Load

Game::Game() : window(nullptr), renderer(nullptr), backgroundTexture(nullptr), running(false), player(renderer) {}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        return false;
    }

    // Tải hình nền
    backgroundTexture = IMG_LoadTexture(renderer, "image/bgr.jpg");
    if (!backgroundTexture) {
        return false;  // Kiểm tra nếu không tải được hình ảnh
    }

    // Tạo 5 máy bay địch
    for (int i = 0; i < 5; ++i) {
        enemies.push_back(new Enemy(renderer, rand() % 750, rand() % 500 - 600));
    }

    running = true;
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        player.handleInput(event);
    }
}

void Game::update() {
    player.update();

    // Kiểm tra va chạm với máy bay địch
    SDL_Rect playerRect = player.getRect();
    for (Enemy* enemy : enemies) {
        SDL_Rect enemyRect = enemy->getRect();
        if (SDL_HasIntersection(&playerRect, &enemyRect)) {
            player.resetPosition();
            enemy->resetPosition();
        }
    }

    // Cập nhật máy bay địch
    for (Enemy* enemy : enemies) {
        enemy->update();
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    // Vẽ nền
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    player.render(renderer);

    for (Enemy* enemy : enemies) {
        enemy->render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyTexture(backgroundTexture);  // Hủy texture của background
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Xóa các đối tượng enemy
    for (Enemy* enemy : enemies) {
        delete enemy;
    }

    SDL_Quit();
}

bool Game::isRunning() {
    return running;
}
