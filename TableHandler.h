#pragma once
#include <array>
#include <optional>
#include <cstdio>
#include <vector>

#include "Piece.h"


class TableHandler
{

	Piece** board;

public:
	TableHandler();
	~TableHandler();

	void arrangePiecesOnBoard();
	Piece getPieceAtCoordinate(int x, int y);
	bool putPieceAtCoordinate(Piece piece, int x, int y);
	std::vector<int> getPieceCoordinates(pieceType type, pieceColor color);
	bool removePieceAtCoordinate(int x, int y);
	void debug_printTable();
	Piece** getBoard();
	
};

