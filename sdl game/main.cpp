#include <SDL.h>
#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init("SDL Game", 800, 600)) {
        return -1;
    }

    while (game.isRunning()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    return 0;
}
