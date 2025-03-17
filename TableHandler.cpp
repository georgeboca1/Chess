#include <array>
#include <optional>
#include <cstdio>
#include <vector>

#include "TableHandler.h"
#include "Piece.h"



TableHandler::TableHandler() 
{
	this->board = new Piece*[8];
	for (int i = 0; i <= 7; i++)
	{
		this->board[i] = new Piece[8];
	}
	this->arrangePiecesOnBoard();
	printf("\nInitialized and arranged pieces on table");
}

TableHandler::~TableHandler() 
{
	delete[] this->board;
}

Piece TableHandler::getPieceAtCoordinate(int x, int y)
{
	if (this->board[x][y].getPieceType() != NONE)
	{
		return this->board[x][y];
	}
	else
		return Piece(NONE, NOCOLOR);
}

bool TableHandler::putPieceAtCoordinate(Piece piece, int x, int y)
{

	//if (this->board[y * 8 + x].has_value()) printf("Eaten a piece!\n");
	this->board[x][y] = piece;
	this->board[x][y].changePawnFirstMove(false);
	this->board[x][y].changeCoordinates(x, y);
	return true;

}

bool TableHandler::removePieceAtCoordinate(int x, int y)
{
	if (this->board[x][y].getPieceType() != NONE)
	{
		this->board[x][y] = Piece(NONE,NOCOLOR);
		return true;
	}

	return false;
}

void TableHandler::arrangePiecesOnBoard()
{
	const std::array<pieceType, 8> backRow = { ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK };

	for (size_t row = 0; row < 8; ++row) {
		for (size_t col = 0; col < 8; ++col) {
			board[row][col] = Piece(NONE,NOCOLOR);
		}
	}
	for (size_t col = 0; col < 8; ++col) {
		board[0][col] = Piece(backRow[col], BLACK);
		board[0][col].changeCoordinates(0, col);
		board[7][col] = Piece(backRow[col], WHITE);
		board[7][col].changeCoordinates(7, col);
	}

	for (size_t i = 0; i < 8; i++)
	{
		this->board[1][i] = Piece(PAWN, BLACK);
		board[1][i].changeCoordinates(1, i);
		this->board[6][i] = Piece(PAWN, WHITE);
		board[6][i].changeCoordinates(6, i);
	}
}

void TableHandler::debug_printTable()
{
	printf("\n");
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (this->board[i][j].getPieceType() != NONE) printf("%d ", this->board[i][j].getPieceType());
			else printf("  ");
		}
		printf("\n");
	}
	printf("\n");
}

Piece** TableHandler::getBoard()
{
	return this->board;
}