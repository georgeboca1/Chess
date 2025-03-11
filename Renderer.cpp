#include "Renderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

Renderer::Renderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s ", SDL_GetError());
        return;
    }
    this->window = SDL_CreateWindow("SDL2 Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Window could not be created! SDL_Error: %s ", SDL_GetError());
        SDL_Quit();
        return;
    }

	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s ", SDL_GetError());
        SDL_Quit();
        return;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("IMG_Init could not be created! SDL_Error: %s ", IMG_GetError());
        SDL_Quit();
    }

}

Renderer::~Renderer()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Renderer::drawBoard()
{
    SDL_Texture* texture = IMG_LoadTexture(this->renderer, "img/board.png");
	SDL_Rect dstRect = { 0, 0, width, height };
    SDL_RenderCopy(this->renderer, texture, nullptr, &dstRect);
}

void Renderer::drawPieces()
{

}

void Renderer::drawInfo()
{

}

void Renderer::clear()
{
	SDL_RenderClear(renderer);
}

void Renderer::present()
{
    SDL_RenderPresent(this->renderer);
    SDL_Delay(2000);
}