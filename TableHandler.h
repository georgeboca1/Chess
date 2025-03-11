#pragma once
#include <array>
#include <optional>
#include <cstdio>
#include <vector>

#include "Piece.h"


class TableHandler
{
	//Using a single fixed-size array instead of an two-dimensional array allows us
	//to manage memory more efficiently, we have less memory fragmentation, faster speeds
	// row * 8 + col
	std::array<std::optional<Piece>, 64> board;

public:
	TableHandler();
	~TableHandler();

	void arrangePiecesOnBoard();
	Piece getPieceAtCoordinate(int x, int y);
	bool putPieceAtCoordinate(Piece piece, int x, int y);
	bool removePieceAtCoordinate(int x, int y);
	void debug_printTable();
};

