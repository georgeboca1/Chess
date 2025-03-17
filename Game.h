#pragma once
#include <cstdio>

#include "TableHandler.h"
#include "Piece.h"
#include "Renderer.h"

class Game
{
private:
	TableHandler* table;
	Renderer* renderer;
	bool moveMade;
	bool pieceSelected;
	bool drawRedSquare;
	int redSquareX;
	int redSquareY;
	Piece selectedPiece;
	int windowWidth, windowHeight;
	bool playerTurn;

public:
	Game();
	~Game();
	void init();
	void loop();
};

