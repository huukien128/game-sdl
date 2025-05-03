#ifndef MENU_H
#define MENU_H

#include <SDL.h>

class Menu {

private:
    SDL_Renderer* renderer;
    SDL_Texture* playAgainTexture;
    SDL_Texture* exitTexture;
    SDL_Texture* startGameTexture;
    SDL_Texture* howToPlayTexture;
    SDL_Texture* menuBackground;
    SDL_Texture* howToPlayImage;
    SDL_Texture* backTexture;
    SDL_Rect playAgainRect;
    SDL_Rect exitRect;
    SDL_Rect startGameRect;
    SDL_Rect howToPlayRect;
    SDL_Rect backRect;
    bool playAgainSelected;
    bool exitSelected;
    bool startGameSelected;
    bool howToPlaySelected;
    bool isGameOverMenu;
    bool showHowToPlay;


public:
    Menu(SDL_Renderer* renderer);
    ~Menu();
    void handleEvents(SDL_Event& event);
    void render();
    void reset();
    bool isPlayAgainSelected() const { return playAgainSelected; }
    bool isExitSelected() const { return exitSelected; }
    bool isStartGameSelected() const { return startGameSelected; }
    bool isHowToPlaySelected() const { return howToPlaySelected; }
    void setGameOverMenu(bool value);
    void loadMenuItems();
    void freeTextures();

};

#endif
