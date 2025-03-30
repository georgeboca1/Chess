#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <array>
#include <optional>
#include <vector>
#include "Renderer.h"
#include "Piece.h"

Renderer::Renderer(const char* title, int width, int height)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->squareSizeX = this->width / 8;
	this->squareSizeY = this->height / 8;

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

    this->moveTexture = IMG_LoadTexture(this->renderer, "img\\utils\\validMove.png");
    this->moveTexture2 = IMG_LoadTexture(this->renderer, "img\\utils\\validMoveWithPiece.png");
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

void Renderer::drawPieces(Piece** pieces)
{
	for (int i = 0; i <= 7; i++)
	{
        for (int j = 0; j <= 7; j++)
        {
            if (pieces[i][j].getPieceType() != NONE)
            {
                SDL_Rect rect = { pieces[i][j].getY() * this->squareSizeX + 10, pieces[i][j].getX() * this->squareSizeY + 10, 80, 80};
                switch (pieces[i][j].getPieceColor())
                {
                case BLACK:
                    switch (pieces[i][j].getPieceType())
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
                    switch (pieces[i][j].getPieceType())
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

void Renderer::drawPressedRectangle(int x, int y)
{
	SDL_Rect rect = { (x / squareSizeX) * squareSizeX + 1 , (y / squareSizeY) * squareSizeY + 1, squareSizeX, squareSizeY};
	SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 0);
    SDL_RenderDrawRect(this->renderer, &rect);
}

void Renderer::getWindowSize(int* width, int* height)
{
	*width = this->width;
	*height = this->height;
}

void Renderer::drawValidMoves(Piece piece, Piece** pieces)
{
	std::vector<std::vector<int>> validMoves = piece.getValidMoves(pieces, false);
    float dx = this->squareSizeX / 4;
    float dy = this->squareSizeY / 4;
    float offsetX = (this->squareSizeX - dx) / 2;
    float offsetY = (this->squareSizeY - dy) / 2;

	for (auto& move : validMoves)
	{
        if (pieces[move[1]][move[0]].getPieceType() != NONE)
        {
            SDL_Rect rect =
            {
                1 + move[0] * this->squareSizeX,
                1 + move[1] * this->squareSizeY,
                this->squareSizeX, this->squareSizeY
            };
            SDL_RenderCopy(this->renderer, this->moveTexture2, nullptr, &rect);
        }
        else
        {
            SDL_Rect rect =
            {
                move[0] * this->squareSizeX + offsetX,
                move[1] * this->squareSizeY + offsetY,
                dx, dy
            };
            SDL_RenderCopy(this->renderer, this->moveTexture, nullptr, &rect);
        }
	}
}

void Renderer::drawCheck(int x, int y)
{
	SDL_Rect rect = { x * this->squareSizeX, y * this->squareSizeY, this->squareSizeX, this->squareSizeY };
	SDL_SetRenderDrawColor(this->renderer, 255, 123, 123, 255);
	SDL_RenderDrawRect(this->renderer, &rect);
}