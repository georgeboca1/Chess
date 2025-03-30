#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <array>
#include <optional>
#include "Piece.h"
class Renderer
{
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	const char* title;
	int width, height;
	SDL_Texture* boardTexture;
	SDL_Texture* pieceTextures[12];
	SDL_Texture* moveTexture;
	SDL_Texture* moveTexture2;
	SDL_Rect boardRect;
	int squareSizeX;
	int squareSizeY;

public:
	Renderer(const char* title, int width, int height);
	~Renderer();

	void clear();
	void present();
	void drawBoard();
	void drawPieces(Piece** pieces);
	void drawInfo();
	void getMousePosition(int* x, int* y);
	void getWindowSize(int* x, int* y);
	void drawPressedRectangle(int x, int y);
	void drawValidMoves(Piece piece,Piece** pieces);
	void drawCheck(int x, int y);
};

