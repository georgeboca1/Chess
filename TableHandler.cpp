#include <array>
#include <optional>
#include <cstdio>
#include <vector>

#include "TableHandler.h"
#include "Piece.h"



TableHandler::TableHandler() 
{
	this->arrangePiecesOnBoard();
	printf("\nInitialized and arranged pieces on table");
}

TableHandler::~TableHandler() 
{

}

Piece TableHandler::getPieceAtCoordinate(int x, int y)
{
	if (this->board[x * 8 + y].has_value())
	{
		return this->board[x * 8 + y].value();
	}
	else
		return Piece(NONE, BLACK);
}

bool TableHandler::putPieceAtCoordinate(Piece piece, int x, int y)
{
	if (piece.isMoveValid(x, y))
	{
		if (this->board[x * 8 + y].has_value()) printf("Eaten a piece!\n");
		this->board[x * 8 + y] = piece;
		return true;
	}
	return false;
}

bool TableHandler::removePieceAtCoordinate(int x, int y)
{
	if (this->board[x * 8 + y].has_value())
	{
		this->board[x * 8 + y].reset();
		return true;
	}

	return false;
}

void TableHandler::arrangePiecesOnBoard()
{
	const std::array<pieceType, 8> backRow = { ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK };

	for (size_t col = 0; col < 8; ++col) {
		board[col] = Piece(backRow[col], BLACK);
		board[col]->changeCoordinates(col, 0);
		board[56 + col] = Piece(backRow[col], WHITE);
		board[56 + col]->changeCoordinates(col, 8);
	}

	for (size_t i = 0; i < 8; i++)
	{
		this->board[8 + i] = Piece(PAWN, BLACK);
		board[8 + i]->changeCoordinates(1,i);
		this->board[48 + i] = Piece(PAWN, WHITE);
		board[48 + i]->changeCoordinates(7, i);
	}
}

void TableHandler::debug_printTable()
{
	for (int i = 0; i < 64; i++)
	{
		if (i != 0 && i % 8 == 0) printf("\n");
		if (this->board[i].has_value()) printf("%d ", this->board[i]->getPieceType());
	}
}

std::array<std::optional<Piece>, 64> TableHandler::getBoard() 
{
	return this->board;
}