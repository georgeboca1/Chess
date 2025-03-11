#pragma once
#include <cstdio>

#include "TableHandler.h"
#include "Piece.h"
#include "Renderer.h"

class Game
{
private:
	TableHandler* table;
	Renderer* renderer;
public:
	Game();
	~Game();
	void init();
	void loop();
};

