#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <filesystem>
#include "TableHandler.h"
#include "Renderer.h"
#include "Game.h"

int main() {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    Game game;
    game.init();
    game.loop();
    return 0;
}
