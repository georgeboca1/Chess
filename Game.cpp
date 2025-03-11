#include <cstdio>

#include "Game.h"
#include "TableHandler.h"
#include "Piece.h"
#include "Renderer.h"

Game::Game()
{
	this->renderer = new Renderer("Chess", 800, 700);
	this->table = new TableHandler();
}

Game::~Game()
{
	delete this->renderer;
	delete this->table;
}

void Game::init()
{
    this->table->arrangePiecesOnBoard();
}

void Game::loop()
{
    bool isRunning = true;
    SDL_Event event;
    Uint32 startTicks = SDL_GetTicks();
    int frameRateCount = 0;

    // Main loop
    while (isRunning) {
        // Handle events

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        Uint64 start = SDL_GetPerformanceCounter();
        this->renderer->clear();
        this->renderer->drawBoard();
        this->renderer->drawPieces(this->table->getBoard());

        this->renderer->present();

        Uint64 end = SDL_GetPerformanceCounter();
        if (frameRateCount % 10 == 0) {
            float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
            printf("FPS: %f\n", 1 / elapsed);
        }

        frameRateCount++;
        SDL_Delay(6);
        
    }


}
