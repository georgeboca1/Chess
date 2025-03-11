#pragma once
#include <vector>

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
	BLACK = 1
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

class Piece
{
	pieceType type;
	pieceColor color;
	pieceValue value;
	bool isPawnFirstMove;
	int coordinates[2];

public:
	Piece(pieceType _type, pieceColor _color);
	~Piece();

	const pieceType getPieceType();
	bool modifyPieceType(pieceType _type);
	const pieceColor getPieceColor();
	const pieceValue getPieceValue();
	void changePawnFirstMove(bool b);
	bool getPawnFirstMove();
	bool changeCoordinates(int x, int y);
	bool isMoveValid(int x, int y);
};

