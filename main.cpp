#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include "TableHandler.h"
#include "Renderer.h"

int main() {
    Renderer renderer;
    renderer.drawBoard();
    renderer.present();
    return 0;
}
