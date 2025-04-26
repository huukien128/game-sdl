#include "Menu.h"
#include "FontManager.h"
#include "TextureManager.h"
#include <iostream>

Menu::Menu(SDL_Renderer* renderer)
    : renderer(renderer),
      playAgainTexture(nullptr),
      exitTexture(nullptr),
      startGameTexture(nullptr),
      howToPlayTexture(nullptr),
      menuBackground(nullptr),
      howToPlayImage(nullptr),
      backTexture(nullptr),
      playAgainSelected(false),
      exitSelected(false),
      startGameSelected(false),
      howToPlaySelected(false),
      isGameOverMenu(false),
      showHowToPlay(false) {
    loadMenuItems();
}

Menu::~Menu() {
    freeTextures();
}

void Menu::loadMenuItems() {
    freeTextures();

    SDL_Color white = {255, 255, 255, 255};

    if (isGameOverMenu) {
        playAgainTexture = FontManager::RenderText("Play Again", white, FontManager::LoadFont("Font/font2.ttf", 30), renderer);
        playAgainRect = {320, 195, 0, 0};
        SDL_QueryTexture(playAgainTexture, nullptr, nullptr, &playAgainRect.w, &playAgainRect.h);
    } else {
        startGameTexture = FontManager::RenderText("Start Game", white, FontManager::LoadFont("Font/font2.ttf", 30), renderer);
        startGameRect = {320, 200, 0, 0};
        SDL_QueryTexture(startGameTexture, nullptr, nullptr, &startGameRect.w, &startGameRect.h);
    }

    howToPlayTexture = FontManager::RenderText("How to Play", white, FontManager::LoadFont("Font/font2.ttf", 30), renderer);
    howToPlayRect = {320, 250, 0, 0};
    SDL_QueryTexture(howToPlayTexture, nullptr, nullptr, &howToPlayRect.w, &howToPlayRect.h);

    exitTexture = FontManager::RenderText("Exit", white, FontManager::LoadFont("Font/font2.ttf", 30), renderer);
    exitRect = {320, 300, 0, 0};
    SDL_QueryTexture(exitTexture, nullptr, nullptr, &exitRect.w, &exitRect.h);

    menuBackground = TextureManager::LoadTexture(renderer, "image/menu.jpg");
    howToPlayImage = TextureManager::LoadTexture(renderer, "image/howtoplay.png");

    backTexture = FontManager::RenderText("Back", white, FontManager::LoadFont("Font/font2.ttf", 28), renderer);
    backRect = {350, 520, 0, 0};
    SDL_QueryTexture(backTexture, nullptr, nullptr, &backRect.w, &backRect.h);
}

void Menu::freeTextures() {
    if (playAgainTexture) SDL_DestroyTexture(playAgainTexture);
    if (exitTexture) SDL_DestroyTexture(exitTexture);
    if (startGameTexture) SDL_DestroyTexture(startGameTexture);
    if (howToPlayTexture) SDL_DestroyTexture(howToPlayTexture);
    if (menuBackground) SDL_DestroyTexture(menuBackground);
    if (howToPlayImage) SDL_DestroyTexture(howToPlayImage);
    if (backTexture) SDL_DestroyTexture(backTexture);
    playAgainTexture = exitTexture = startGameTexture = howToPlayTexture = menuBackground = howToPlayImage = backTexture = nullptr;
}

void Menu::handleEvents(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (showHowToPlay) {
            if (x >= backRect.x && x <= backRect.x + backRect.w &&
                y >= backRect.y && y <= backRect.y + backRect.h) {
                showHowToPlay = false;
            }
            return;
        }

        if (isGameOverMenu) {
            if (x >= playAgainRect.x && x <= playAgainRect.x + playAgainRect.w &&
                y >= playAgainRect.y && y <= playAgainRect.y + playAgainRect.h) {
                playAgainSelected = true;
            }
        } else {
            if (x >= startGameRect.x && x <= startGameRect.x + startGameRect.w &&
                y >= startGameRect.y && y <= startGameRect.y + startGameRect.h) {
                startGameSelected = true;
            }

            if (x >= howToPlayRect.x && x <= howToPlayRect.x + howToPlayRect.w &&
                y >= howToPlayRect.y && y <= howToPlayRect.y + howToPlayRect.h) {
                howToPlaySelected = true;
                showHowToPlay = true;
            }
        }

        if (x >= exitRect.x && x <= exitRect.x + exitRect.w &&
            y >= exitRect.y && y <= exitRect.y + exitRect.h) {
            exitSelected = true;
        }
    }
}

void Menu::render() {
    if (menuBackground) {
        SDL_Rect bgRect = {0, 0, 800, 600};
        SDL_RenderCopy(renderer, menuBackground, nullptr, &bgRect);
    }

    if (showHowToPlay && howToPlayImage) {
        SDL_Rect helpRect = {100, 50, 600, 450};
        SDL_RenderCopy(renderer, howToPlayImage, nullptr, &helpRect);

        SDL_RenderCopy(renderer, backTexture, nullptr, &backRect);
        return;
    }

    if (isGameOverMenu) {
        SDL_RenderCopy(renderer, playAgainTexture, nullptr, &playAgainRect);
    } else {
        SDL_RenderCopy(renderer, startGameTexture, nullptr, &startGameRect);
    }

    SDL_RenderCopy(renderer, howToPlayTexture, nullptr, &howToPlayRect);
    SDL_RenderCopy(renderer, exitTexture, nullptr, &exitRect);
}

void Menu::reset() {
    playAgainSelected = false;
    exitSelected = false;
    startGameSelected = false;
    howToPlaySelected = false;
    showHowToPlay = false;
}

void Menu::setGameOverMenu(bool value) {
    isGameOverMenu = value;
    loadMenuItems();
}
