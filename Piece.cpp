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
	this->type = NONE;
	this->color = NOCOLOR;
	this->value = NO_VALUE;
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

std::vector<std::vector<int>> Piece::getValidMoves(Piece** pieces, bool isForCheck)
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
					if (!isForCheck)
					{
						if (isMoveValid(x + 2, y) && this->isPawnFirstMove && pieces[x + 2][y].getPieceType() == NONE && !isSameColor(*this, pieces[x + 2][y]))
						{
							validMoves.push_back({ y, x + 1 });
							validMoves.push_back({ y, x + 2 });
							break;
						}
						if (isMoveValid(x + 1, y) && pieces[x + 1][y].getPieceType() == NONE  && !isSameColor(*this, pieces[x + 1][y]))
						{
							validMoves.push_back({ y, x + 1 });
						}
						if (isMoveValid(x + 1, y - 1) && pieces[x + 1][y - 1].getPieceType() != NONE && pieces[x + 1][y - 1].getPieceType() != KING &&  !isSameColor(*this, pieces[x + 1][y - 1]))
						{
							validMoves.push_back({ y - 1, x + 1 });
						}
						if (isMoveValid(x + 1, y + 1) && pieces[x + 1][y + 1].getPieceType() != NONE && pieces[x + 1][y + 1].getPieceType() != KING && !isSameColor(*this, pieces[x + 1][y + 1]))
						{
							validMoves.push_back({ y + 1, x + 1 });
						}
					}
					else
					{
						if (isMoveValid(x + 1, y - 1) && !isSameColor(*this, pieces[x + 1][y - 1]))
						{
							validMoves.push_back({ y - 1, x + 1 });
						}
						if (isMoveValid(x + 1, y + 1) && !isSameColor(*this, pieces[x + 1][y + 1]))
						{
							validMoves.push_back({ y + 1, x + 1 });
						}
					}
					break;
				case WHITE:
					if (!isForCheck)
					{
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
						if (isMoveValid(x - 1, y - 1) && pieces[x - 1][y - 1].getPieceType() != NONE && pieces[x - 1][y - 1].getPieceType() != KING && !isSameColor(*this, pieces[x - 1][y - 1]))
						{
							validMoves.push_back({ y - 1, x - 1 });
						}
						if (isMoveValid(x - 1, y + 1) && pieces[x - 1][y + 1].getPieceType() != NONE && pieces[x - 1][y + 1].getPieceType() != KING && !isSameColor(*this, pieces[x - 1][y + 1]))
						{
							validMoves.push_back({ y + 1, x - 1 });
						}
					}
					else
					{
						if (isMoveValid(x - 1, y - 1) && !isSameColor(*this, pieces[x + 1][y - 1]))
						{
							validMoves.push_back({ y - 1, x + 1 });
						}
						if (isMoveValid(x - 1, y + 1) && !isSameColor(*this, pieces[x + 1][y + 1]))
						{
							validMoves.push_back({ y + 1, x + 1 });
						}
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
						if (!isSameColor(*this, pieces[x + i][y]) && pieces[x + i][y].getPieceType() != KING) validMoves.push_back({y, x + i});
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
						if (!isSameColor(*this, pieces[x + i][y]) && pieces[x + i][y].getPieceType() != KING) validMoves.push_back({ y, x + i});
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
						if (!isSameColor(*this, pieces[x][y + i]) && pieces[x][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x });;
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
						if (!isSameColor(*this, pieces[x][y + i]) && pieces[x][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x });
						break;
					}
				}
			}
			break;
		case KNIGHT:
			if (isMoveValid(x + 2, y + 1) && !isSameColor(*this, pieces[x+2][y+1]) && pieces[x + 2][y + 1].getPieceType() != KING)
			{
				validMoves.push_back({ y + 1, x + 2 });

			}
			if (isMoveValid(x + 2, y - 1) && !isSameColor(*this, pieces[x + 2][y - 1]) && pieces[x + 2][y - 1].getPieceType() != KING)
			{
				validMoves.push_back({ y - 1, x + 2 });

			}
			if (isMoveValid(x - 2, y + 1) && !isSameColor(*this, pieces[x - 2][y + 1]) && pieces[x - 2][y + 1].getPieceType() != KING)
			{
				validMoves.push_back({ y + 1, x - 2 });
				
			}
			if (isMoveValid(x - 2, y - 1) && !isSameColor(*this, pieces[x - 2][y - 1]) && pieces[x - 2][y - 1].getPieceType() != KING)
			{
				validMoves.push_back({ y - 1, x - 2 });
			}
			if (isMoveValid(x + 1, y + 2) && !isSameColor(*this, pieces[x + 1][y + 2]) && pieces[x + 1][y + 2].getPieceType() != KING)
			{
				validMoves.push_back({ y + 2, x + 1 });
			}
			if (isMoveValid(x + 1, y - 2) && !isSameColor(*this, pieces[x + 1][y - 2]) && pieces[x + 1][y - 2].getPieceType() != KING)
			{
				validMoves.push_back({ y - 2, x + 1 });
			}
			if (isMoveValid(x - 1, y + 2) && !isSameColor(*this, pieces[x - 1][y + 2]) && pieces[x - 1][y + 2].getPieceType() != KING)
			{
				validMoves.push_back({ y + 2, x - 1 });
			}
			if (isMoveValid(x - 1, y - 2) && !isSameColor(*this, pieces[x - 1][y - 2]) && pieces[x - 1][y - 2].getPieceType() != KING)
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
						if (!isSameColor(*this, pieces[x + i][y + i]) && pieces[x + i][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x + i });
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
						if (!isSameColor(*this, pieces[x + i][y + i]) && pieces[x + i][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x + i });
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
						if (!isSameColor(*this, pieces[x - i][y + i]) && pieces[x - i][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x - i });
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
						if (!isSameColor(*this, pieces[x - i][y + i]) && pieces[x - i][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x - i });
						break;
					}
				}
			}
			break;
		case KING:
			if (isForCheck)
			{
				for (int dx = -1; dx <= 1; dx++)
				{
					for (int dy = -1; dy <= 1; dy++)
					{
						if (dx == 0 && dy == 0) continue;
						int newX = x + dx;
						int newY = y + dy;
						if (isMoveValid(newX, newY))
						{
							validMoves.push_back({ newY, newX });
						}
					}
				}
			}
			else
			{
				for (int dx = -1; dx <= 1; dx++)
				{
					for (int dy = -1; dy <= 1; dy++)
					{
						if (dx == 0 && dy == 0) continue;
						int newX = x + dx;
						int newY = y + dy;
						if (isMoveValid(newX, newY) && !isSameColor(*this, pieces[newX][newY]))
						{
							bool isGuarded = false;
							for (int i = 0; i < 8; i++)
							{
								for (int j = 0; j < 8; j++)
								{
									if (pieces[i][j].getPieceColor() != this->color)
									{
										std::vector<std::vector<int>> opponentMoves = pieces[i][j].getValidMoves(pieces, true);
										for (const auto& move : opponentMoves)
										{
											if (move[0] == newY && move[1] == newX)
											{
												isGuarded = true;
												break;
											}
										}
									}
									if (isGuarded) break;
								}
								if (isGuarded) break;
							}
							if (!isGuarded)
							{
								validMoves.push_back({ newY, newX });
							}
						}
					}
				}
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
						if (!isSameColor(*this, pieces[x + i][y]) && pieces[x + i][y].getPieceType() != KING) validMoves.push_back({ y, x + i });
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
						if (!isSameColor(*this, pieces[x + i][y]) && pieces[x + i][y].getPieceType() != KING) validMoves.push_back({ y, x + i });
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
						if (!isSameColor(*this, pieces[x][y + i]) && pieces[x][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x });;
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
						if (!isSameColor(*this, pieces[x][y + i]) && pieces[x][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x });
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
						if (!isSameColor(*this, pieces[x + i][y + i]) && pieces[x + i][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x + i });
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
						if (!isSameColor(*this, pieces[x + i][y + i]) && pieces[x + i][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x + i });
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
						if (!isSameColor(*this, pieces[x - i][y + i]) && pieces[x - i][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x - i });
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
						if (!isSameColor(*this, pieces[x - i][y + i]) && pieces[x - i][y + i].getPieceType() != KING) validMoves.push_back({ y + i, x - i });
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

bool isKinginCheck(Piece** pieces, pieceColor color)
{
	std::vector<int> kingCoords;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces[i][j].getPieceType() == KING && pieces[i][j].getPieceColor() == color)
			{
				kingCoords = { i, j };
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::vector<std::vector<int>> available_moves = pieces[i][j].getValidMoves(pieces, false);
			for (int k = 0; k < available_moves.size(); k++)
			{
				if (pieces[kingCoords[0]][kingCoords[1]].getPieceColor() != pieces[i][j].getPieceColor())
				{
					if (available_moves[k][0] == kingCoords[1] && available_moves[k][1] == kingCoords[0])
					{
						return true;
					}
				}
			}
		
		}
	}
	return false;
}