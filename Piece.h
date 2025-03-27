#pragma once
#include <vector>
#include <array>
#include <optional>

class Piece; // Forward declaration

typedef enum 
{
	NONE = 0,
	PAWN = 1,
	KING = 2,
	QUEEN = 3,
	ROOK = 4,
	KNIGHT = 5,
	BISHOP = 6,
} pieceType;

typedef enum 
{
	WHITE = 0,
	BLACK = 1,
	NOCOLOR = 2
} pieceColor;

typedef enum 
{
	NO_VALUE = 0,
	PAWN_VALUE = 1,
	KNIGHT_VALUE = 3,
	BISHOP_VALUE = 3,
	ROOK_VALUE = 5,
	QUEEN_VALUE = 9
} pieceValue;

pieceValue getPieceValueFromType(pieceType type);
static bool isMoveValid(int x, int y);
bool isKinginCheck(Piece** pieces, pieceColor color);


class Piece
{
	pieceType type;
	pieceColor color;
	pieceValue value;
	bool isPawnFirstMove;
	int coordinates[2];

public:
	Piece(pieceType _type, pieceColor _color);
	Piece();
	~Piece();

	const pieceType getPieceType();
	bool modifyPieceType(pieceType _type);
	const pieceColor getPieceColor();
	const pieceValue getPieceValue();
	void changePawnFirstMove(bool b);
	bool getPawnFirstMove();
	bool changeCoordinates(int x, int y);
	std::vector<std::vector<int>> getValidMoves(Piece** table, bool isForCheck);
	int getX();
	int getY();
};
