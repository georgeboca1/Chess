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
	SDL_Rect boardRect;
	SDL_Texture* pieceTextures[12];

public:
	Renderer(const char* title, int width, int height);
	~Renderer();

	void clear();
	void present();
	void drawBoard();
	void drawPieces(std::array<std::optional<Piece>,64> pieces);
	void drawInfo();
};

