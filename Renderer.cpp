#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <array>
#include <optional>
#include "Renderer.h"
#include "Piece.h"

Renderer::Renderer(const char* title, int width, int height)
{
	this->title = title;
	this->width = width;
	this->height = height;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s ", SDL_GetError());
        return;
    }
    this->window = SDL_CreateWindow(this->title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        this->width, this->height, SDL_WINDOW_SHOWN);

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
    printf("\nSuccesfully initialized SDL and SDL_image");
    this->boardTexture = IMG_LoadTexture(this->renderer, "img\\board\\blue2.png");
    if (!this->boardTexture)
        printf("Failed to load board image! SDL_Error: %s ", SDL_GetError());
    this->boardRect = { 0, 0, this->width, this->height };

	this->pieceTextures[0] = IMG_LoadTexture(this->renderer, "img\\pieces\\bB.png");
	this->pieceTextures[1] = IMG_LoadTexture(this->renderer, "img\\pieces\\bK.png");
    this->pieceTextures[2] = IMG_LoadTexture(this->renderer, "img\\pieces\\bN.png");
    this->pieceTextures[3] = IMG_LoadTexture(this->renderer, "img\\pieces\\bP.png");
    this->pieceTextures[4] = IMG_LoadTexture(this->renderer, "img\\pieces\\bQ.png");
    this->pieceTextures[5] = IMG_LoadTexture(this->renderer, "img\\pieces\\bR.png");
    this->pieceTextures[6] = IMG_LoadTexture(this->renderer, "img\\pieces\\wB.png");
    this->pieceTextures[7] = IMG_LoadTexture(this->renderer, "img\\pieces\\wK.png");
    this->pieceTextures[8] = IMG_LoadTexture(this->renderer, "img\\pieces\\wN.png");
    this->pieceTextures[9] = IMG_LoadTexture(this->renderer, "img\\pieces\\wP.png");
    this->pieceTextures[10] = IMG_LoadTexture(this->renderer, "img\\pieces\\wQ.png");
    this->pieceTextures[11] = IMG_LoadTexture(this->renderer, "img\\pieces\\wR.png");

    for (int i = 0; i < 12; i++)
	{
		if (!this->pieceTextures[i])
			printf("\nFailed to load piece image! SDL_Error: %s ", SDL_GetError());
	}
	printf("\nLoaded all textures");
}

Renderer::~Renderer()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Renderer::drawBoard()
{
    
    SDL_RenderCopy(this->renderer, this->boardTexture, nullptr, &this->boardRect);
}

void Renderer::drawPieces(std::array<std::optional<Piece>, 64> pieces)
{
	for (int i = 0; i < 64; i++)
	{
		if (pieces[i].has_value())
		{
			SDL_Rect rect = { i % 8 * this->width / 8 + 10, i / 8 * this->height / 8, 80, 80 };
            switch (pieces[i]->getPieceColor())
            {
			    case BLACK:
                    switch (pieces[i]->getPieceType())
                    {
                        case PAWN:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[3], nullptr, &rect);
                            break;
                        case QUEEN:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[4], nullptr, &rect);
                            break;
                        case ROOK:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[5], nullptr, &rect);
                            break;
                        case KING:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[1], nullptr, &rect);
                            break;
                        case BISHOP:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[0], nullptr, &rect);
                            break;
                        case KNIGHT:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[2], nullptr, &rect);
                            break;

                    }
                    break;
                case WHITE:
                    switch (pieces[i]->getPieceType())
                    {
                        case PAWN:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[9], nullptr, &rect);
                            break;
                        case QUEEN:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[10], nullptr, &rect);
                            break;
                        case ROOK:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[11], nullptr, &rect);
                            break;
                        case KING:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[7], nullptr, &rect);
                            break;
                        case BISHOP:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[6], nullptr, &rect);
                            break;
                        case KNIGHT:
                            SDL_RenderCopy(this->renderer, this->pieceTextures[8], nullptr, &rect);
                            break;
                    }
                    break;
            }
		}
	}
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
}