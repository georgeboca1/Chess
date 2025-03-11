#include "Piece.h"
#include <vector>

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

bool Piece::isMoveValid(int _x, int _y)
{

	switch (this->type)
	{
	case PAWN:
		if (this->isPawnFirstMove && _x == this->coordinates[0] && _y == this->coordinates[1] + 2) 
			return true; // First move, 2 in front
		for (int i = -1; i <= 1; i++) 
			if (_x == this->coordinates[0] + i && _y == this->coordinates[1] + 1) return true; // Diagonal moves + 1 in front
		return false;
		break;
	case KING:
		for (int i = -1; i <= 1; i++)
		{
			if (_x == this->coordinates[0] + i && _y == this->coordinates[1] + 1) return true; // Diagonal moves + 1 in front
			if (_x == this->coordinates[0] + i && _y == this->coordinates[1] - 1) return true; // Diagonal moves - 1 in back
		}

		if (_x == this->coordinates[0] - 1 && _y == this->coordinates[1]) return true; // Horizontal moves
		if (_x == this->coordinates[0] + 1 && _y == this->coordinates[1]) return true; // Horizontal moves
		return false;

		break;
	case QUEEN:
		if (abs(_x - this->coordinates[0]) == abs(_y - this->coordinates[1])) return true; // Diagonal moves
		if (_x == this->coordinates[0] || _y == this->coordinates[1]) return true; // Horizontal or vertical moves
		return false;
		break;
	case ROOK:
		if (_x == this->coordinates[0] || _y == this->coordinates[1]) return true; // Horizontal or vertical moves
		break;
	case KNIGHT:
		// L moves
		if ((_x == this->coordinates[0] + 2 || _x == this->coordinates[0] - 2) && (_y == this->coordinates[1] + 1 || _y == this->coordinates[1] - 1)) return true;
		if ((_x == this->coordinates[0] + 1 || _x == this->coordinates[0] - 1) && (_y == this->coordinates[1] + 2 || _y == this->coordinates[1] - 2)) return true;
		return false;
		break;
	case BISHOP:
		if (abs(_x - this->coordinates[0]) == abs(_y - this->coordinates[1])) return true; // Diagonal moves
		return false;
		break;
	default:
		return false;
		break;
	}
}

bool Piece::changeCoordinates(int x, int y)
{
	this->coordinates[0] = x;
	this->coordinates[1] = y;
	return true;
}