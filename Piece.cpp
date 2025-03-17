#include "Piece.h"
#include <vector>
#include <array>
#include <optional>

static bool isMoveValid(int x, int y) {
	if (x <= 8 && x >= 0 && y <= 8 && y >= 0)
		return true;
	return false;
}

pieceValue getPieceValueFromType(pieceType type) 
{
	switch (type) 
	{
		case NONE: return NO_VALUE;
		case KING: return NO_VALUE;
		case PAWN: return PAWN_VALUE;
		case ROOK: return ROOK_VALUE;
		case BISHOP: return BISHOP_VALUE;
		case KNIGHT: return KNIGHT_VALUE;
		case QUEEN: return QUEEN_VALUE;
		default: return NO_VALUE;
	}
}

Piece::Piece(pieceType _type, pieceColor _color) 
{
	this->type = _type;
	this->color = _color;
	this->value = getPieceValueFromType(_type);
	this->isPawnFirstMove = true;
	this->coordinates[0] = 0;
	this->coordinates[1] = 0;
}


Piece::Piece()
{
	this->isPawnFirstMove = true;
	this->coordinates[0] = 0;
	this->coordinates[1] = 0;
}
Piece::~Piece()
{
	// ...
}

const pieceType Piece::getPieceType() {
	return this->type;
}

bool Piece::modifyPieceType(pieceType _type) 
{
	if (this->type == PAWN) {
		this->type = _type;
		return true;
	}
	return false; // In chess, only pawns can modify their type when reaching the other end of the table.
	// We return false to let the caller know we are not able to accept their modify request.
}

const pieceColor Piece::getPieceColor()
{
	return this->color;
}

const pieceValue Piece::getPieceValue()
{
	return this->value;
}

void Piece::changePawnFirstMove(bool b)
{
	this->isPawnFirstMove = b;
}

bool Piece::getPawnFirstMove()
{
	return this->isPawnFirstMove;
}

std::vector<std::vector<int>> Piece::getValidMoves(Piece** pieces)
{
	std::vector<std::vector<int>> validMoves;
	switch (this->type)
	{
		case PAWN:
			switch (this->color)
			{
				case BLACK:
					if (isMoveValid(this->coordinates[0] + 2, this->coordinates[1]) && this->isPawnFirstMove && pieces[this->coordinates[0] + 2][this->coordinates[1]].getPieceType() == NONE)
					{
						validMoves.push_back({ this->coordinates[1], this->coordinates[0] + 1 });
						validMoves.push_back({ this->coordinates[1], this->coordinates[0] + 2 });
						break;
					}
					if (isMoveValid(this->coordinates[0] + 1,this->coordinates[1]) && pieces[this->coordinates[0] + 1][this->coordinates[1]].getPieceType() == NONE)
					{
						validMoves.push_back({ this->coordinates[1], this->coordinates[0] + 1 });
					}
					if (isMoveValid(this->coordinates[0] + 1, this->coordinates[1] - 1) && pieces[this->coordinates[0] + 1][this->coordinates[1] - 1].getPieceType() != NONE)
					{
						validMoves.push_back({ this->coordinates[1] - 1, this->coordinates[0] + 1 });
					}
					if (isMoveValid(this->coordinates[0] + 1, this->coordinates[1] + 1) && pieces[this->coordinates[0] + 1][this->coordinates[1] + 1].getPieceType() != NONE)
					{
						validMoves.push_back({ this->coordinates[1] + 1, this->coordinates[0] + 1 });
					}
					break;
				case WHITE:
					if (isMoveValid(this->coordinates[0] - 2, this->coordinates[1]) && this->isPawnFirstMove && !pieces[this->coordinates[0] - 2][this->coordinates[1]].getPieceType() != NONE)
					{
						validMoves.push_back({ this->coordinates[1], this->coordinates[0] - 1 });
						validMoves.push_back({ this->coordinates[1], this->coordinates[0] - 2 });
						break;
					}
					if (isMoveValid(this->coordinates[0] - 1, this->coordinates[1]) && pieces[this->coordinates[0] - 1][this->coordinates[1]].getPieceType() == NONE)
					{
						validMoves.push_back({ this->coordinates[1], this->coordinates[0] - 1 });
					}
					if (isMoveValid(this->coordinates[0] - 1, this->coordinates[1] - 1) && pieces[this->coordinates[0] - 1][this->coordinates[1] - 1].getPieceType() != NONE)
					{
						validMoves.push_back({ this->coordinates[1] - 1, this->coordinates[0] - 1 });
					}
					if (isMoveValid(this->coordinates[0] - 1, this->coordinates[1] + 1) && pieces[this->coordinates[0] - 1][this->coordinates[1] + 1].getPieceType() != NONE)
					{
						validMoves.push_back({ this->coordinates[1] + 1, this->coordinates[0] - 1 });
					}
			}
			break;
		default:
			break;
	}
	return validMoves;
}

bool Piece::changeCoordinates(int x, int y)
{
	this->coordinates[0] = x;
	this->coordinates[1] = y;
	return true;
}

int Piece::getX()
{
	return this->coordinates[0];
}

int Piece::getY()
{
	return this->coordinates[1];
}