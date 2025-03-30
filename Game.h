#pragma once
#include <cstdio>
#include <string>

#include "TableHandler.h"
#include "Piece.h"
#include "Renderer.h"
#include "Stockfish.h"

class Game
{
private:
	TableHandler* table;
	Renderer* renderer;
	StockfishEngine stockfish;
	bool moveMade;
	bool pieceSelected;
	bool drawRedSquare;
	int redSquareX;
	int redSquareY;
	Piece selectedPiece;
	int windowWidth, windowHeight;
	bool playerTurn;
	int lastX, lastY, newX, newY;
	int stockFishDelay;

public:
	Game();
	~Game();
	void init();
	void loop();
};

