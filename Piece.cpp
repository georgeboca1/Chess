#include "Piece.h"
#include <vector>
#include <array>
#include <optional>

static bool isMoveValid(int x, int y) {
	if (x < 8 && x >= 0 && y < 8 && y >= 0)
		return true;
	return false;
}
static bool isSameColor(Piece piece1, Piece piece2) {
	if (piece1.getPieceColor() == piece2.getPieceColor())
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
	int x = this->coordinates[0];
	int y = this->coordinates[1];
	switch (this->type)
	{
		case PAWN:
			switch (this->color)
			{
				case BLACK:
					if (isMoveValid(x + 2, y) && this->isPawnFirstMove && pieces[x + 2][y].getPieceType() == NONE && !isSameColor(*this, pieces[x + 2][y]))
					{
						validMoves.push_back({ y, x + 1 });
						validMoves.push_back({ y, x + 2 });
						break;
					}
					if (isMoveValid(x + 1,y) && pieces[x + 1][y].getPieceType() == NONE && !isSameColor(*this, pieces[x + 1][y]))
					{
						validMoves.push_back({ y, x + 1 });
					}
					if (isMoveValid(x + 1, y - 1) && pieces[x + 1][y - 1].getPieceType() != NONE && !isSameColor(*this, pieces[x + 1][y - 1]))
					{
						validMoves.push_back({ y - 1, x + 1 });
					}
					if (isMoveValid(x + 1, y + 1) && pieces[x + 1][y + 1].getPieceType() != NONE && !isSameColor(*this, pieces[x + 1][y + 1]))
					{
						validMoves.push_back({ y + 1, x + 1 });
					}
					break;
				case WHITE:
					if (isMoveValid(x - 2, y) && this->isPawnFirstMove && !pieces[x - 2][y].getPieceType() != NONE && !isSameColor(*this, pieces[x - 2][y]))
					{
						validMoves.push_back({ y, x - 1 });
						validMoves.push_back({ y, x - 2 });
						break;
					}
					if (isMoveValid(x - 1, y) && pieces[x - 1][y].getPieceType() == NONE && !isSameColor(*this, pieces[x - 1][y]))
					{
						validMoves.push_back({ y, x - 1 });
					}
					if (isMoveValid(x - 1, y - 1) && pieces[x - 1][y - 1].getPieceType() != NONE && !isSameColor(*this, pieces[x - 1][y - 1]))
					{
						validMoves.push_back({ y - 1, x - 1 });
					}
					if (isMoveValid(x - 1, y + 1) && pieces[x - 1][y + 1].getPieceType() != NONE && !isSameColor(*this, pieces[x - 1][y + 1]))
					{
						validMoves.push_back({ y + 1, x - 1 });
					}
					break;
			}
			break;
		case ROOK:
			for (int i = 1; i < 8; i++)
			{
				if (isMoveValid(x + i, y) )
				{
					if (pieces[x + i][y].getPieceType() == NONE && !isSameColor(*this, pieces[x + i][y]))
					{
						validMoves.push_back({ y, x + i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x + i][y])) validMoves.push_back({ y, x + i });
						break;
					}
				}
			}
			for (int i = -1; i > -8; i--)
			{
				if (isMoveValid(x + i, y))
				{
					if (pieces[x + i][y].getPieceType() == NONE && !isSameColor(*this, pieces[x + i][y]))
					{
						validMoves.push_back({ y, x + i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x + i][y])) validMoves.push_back({ y, x + i});
						break;
					}
				}
			}
			for (int i = 1; i < 8; i++)
			{
				if (isMoveValid(x, y + i))
				{
					if (pieces[x][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x][y + i]))
					{
						validMoves.push_back({ y + i, x });
					}
					else
					{
						if (!isSameColor(*this, pieces[x][y + i])) validMoves.push_back({ y + i, x });;
						break;
					}
				}
			}
			for (int i = -1; i > -8; i--)
			{
				if (isMoveValid(x, y + i))
				{
					if (pieces[x][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x][y + i]))
					{
						validMoves.push_back({ y + i, x });
					}
					else
					{
						if (!isSameColor(*this, pieces[x][y + i])) validMoves.push_back({ y + i, x });
						break;
					}
				}
			}
			break;
		case KNIGHT:
			if (isMoveValid(x + 2, y + 1) && !isSameColor(*this, pieces[x+2][y+1]))
			{
				validMoves.push_back({ y + 1, x + 2 });

			}
			if (isMoveValid(x + 2, y - 1) && !isSameColor(*this, pieces[x + 2][y - 1]))
			{
				validMoves.push_back({ y - 1, x + 2 });

			}
			if (isMoveValid(x - 2, y + 1) && !isSameColor(*this, pieces[x - 2][y + 1]))
			{
				validMoves.push_back({ y + 1, x - 2 });
				
			}
			if (isMoveValid(x - 2, y - 1) && !isSameColor(*this, pieces[x - 2][y - 1]))
			{
				validMoves.push_back({ y - 1, x - 2 });
			}
			if (isMoveValid(x + 1, y + 2) && !isSameColor(*this, pieces[x + 1][y + 2]))
			{
				validMoves.push_back({ y + 2, x + 1 });
			}
			if (isMoveValid(x + 1, y - 2) && !isSameColor(*this, pieces[x + 1][y - 2]))
			{
				validMoves.push_back({ y - 2, x + 1 });
			}
			if (isMoveValid(x - 1, y + 2) && !isSameColor(*this, pieces[x - 1][y + 2]))
			{
				validMoves.push_back({ y + 2, x - 1 });
			}
			if (isMoveValid(x - 1, y - 2) && !isSameColor(*this, pieces[x - 1][y - 2]))
			{
				validMoves.push_back({ y - 2, x - 1 });
			}
			break;
		case BISHOP:
			for (int i = 1; i < 8; i++)
			{
				if (isMoveValid(x + i, y + i))
				{
					if (pieces[x + i][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x + i][y + i]))
					{
						validMoves.push_back({ y + i, x + i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x + i][y + i])) validMoves.push_back({ y + i, x + i });
						break;
					}
				}
			}
			for (int i = -1; i > -8; i--)
			{
				if (isMoveValid(x + i, y + i))
				{
					if (pieces[x + i][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x + i][y + i]))
					{
						validMoves.push_back({ y + i, x + i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x + i][y + i])) validMoves.push_back({ y + i, x + i });
						break;
					}
				}
			}
			for (int i = 1; i < 8; i++)
			{
				if (isMoveValid(x - i, y + i))
				{
					if (pieces[x - i][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x - i][y + i]))
					{
						validMoves.push_back({ y + i, x - i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x - i][y + i])) validMoves.push_back({ y + i, x - i });
						break;
					}
				}
			}
			for (int i = -1; i > -8; i--)
			{
				if (isMoveValid(x - i, y + i))
				{
					if (pieces[x - i][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x - i][y + i]))
					{
						validMoves.push_back({ y + i, x - i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x - i][y + i])) validMoves.push_back({ y + i, x - i });
						break;
					}
				}
			}
		case KING:
			if (isMoveValid(x + 1, y) && !isSameColor(*this, pieces[x + 1][y]))
			{
				validMoves.push_back({ y, x + 1 });
			}
			if (isMoveValid(x - 1, y) && !isSameColor(*this, pieces[x - 1][y]))
			{
				validMoves.push_back({ y, x - 1 });
			}
			if (isMoveValid(x, y + 1) && !isSameColor(*this, pieces[x][y + 1]))
			{
				validMoves.push_back({ y + 1, x });
			}
			if (isMoveValid(x, y - 1) && !isSameColor(*this, pieces[x][y - 1]))
			{
				validMoves.push_back({ y - 1, x });
			}
			if (isMoveValid(x + 1, y + 1) && !isSameColor(*this, pieces[x + 1][y + 1]))
			{
				validMoves.push_back({ y + 1, x + 1 });
			}
			if (isMoveValid(x + 1, y - 1) && !isSameColor(*this, pieces[x + 1][y - 1]))
			{
				validMoves.push_back({ y - 1, x + 1 });
			}
			if (isMoveValid(x - 1, y + 1) && !isSameColor(*this, pieces[x - 1][y + 1]))
			{
				validMoves.push_back({ y + 1, x - 1 });
			}
			if (isMoveValid(x - 1, y - 1) && !isSameColor(*this, pieces[x - 1][y - 1]))
			{
				validMoves.push_back({ y - 1, x - 1 });
			}
			break;
		case QUEEN:
			for (int i = 1; i < 8; i++)
			{
				if (isMoveValid(x + i, y))
				{
					if (pieces[x + i][y].getPieceType() == NONE && !isSameColor(*this, pieces[x + i][y]))
					{
						validMoves.push_back({ y, x + i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x + i][y])) validMoves.push_back({ y, x + i });
						break;
					}
				}
			}
			for (int i = -1; i > -8; i--)
			{
				if (isMoveValid(x + i, y))
				{
					if (pieces[x + i][y].getPieceType() == NONE && !isSameColor(*this, pieces[x + i][y]))
					{
						validMoves.push_back({ y, x + i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x + i][y])) validMoves.push_back({ y, x + i });
						break;
					}
				}
			}
			for (int i = 1; i < 8; i++)
			{
				if (isMoveValid(x, y + i))
				{
					if (pieces[x][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x][y + i]))
					{
						validMoves.push_back({ y + i, x });
					}
					else
					{
						if (!isSameColor(*this, pieces[x][y + i])) validMoves.push_back({ y + i, x });;
						break;
					}
				}
			}
			for (int i = -1; i > -8; i--)
			{
				if (isMoveValid(x, y + i))
				{
					if (pieces[x][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x][y + i]))
					{
						validMoves.push_back({ y + i, x });
					}
					else
					{
						if (!isSameColor(*this, pieces[x][y + i])) validMoves.push_back({ y + i, x });
						break;
					}
				}
			}
			for (int i = 1; i < 8; i++)
			{
				if (isMoveValid(x + i, y + i))
				{
					if (pieces[x + i][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x + i][y + i]))
					{
						validMoves.push_back({ y + i, x + i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x + i][y + i])) validMoves.push_back({ y + i, x + i });
						break;
					}
				}
			}
			for (int i = -1; i > -8; i--)
			{
				if (isMoveValid(x + i, y + i))
				{
					if (pieces[x + i][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x + i][y + i]))
					{
						validMoves.push_back({ y + i, x + i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x + i][y + i])) validMoves.push_back({ y + i, x + i });
						break;
					}
				}
			}
			for (int i = 1; i < 8; i++)
			{
				if (isMoveValid(x - i, y + i))
				{
					if (pieces[x - i][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x - i][y + i]))
					{
						validMoves.push_back({ y + i, x - i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x - i][y + i])) validMoves.push_back({ y + i, x - i });
						break;
					}
				}
			}
			for (int i = -1; i > -8; i--)
			{
				if (isMoveValid(x - i, y + i))
				{
					if (pieces[x - i][y + i].getPieceType() == NONE && !isSameColor(*this, pieces[x - i][y + i]))
					{
						validMoves.push_back({ y + i, x - i });
					}
					else
					{
						if (!isSameColor(*this, pieces[x - i][y + i])) validMoves.push_back({ y + i, x - i });
						break;
					}
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