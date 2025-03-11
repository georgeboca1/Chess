#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
class Renderer
{
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::string title;
	int width, height;
	public:
	Renderer();
	~Renderer();

	void clear();
	void present();
	void drawBoard();
	void drawPieces();
	void drawInfo();
};

