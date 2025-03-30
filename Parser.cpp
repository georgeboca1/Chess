#include "Parser.h"
#include <stdio.h>
#include <string>

char* Parser::coordinatesToAlphabeticForm(int oy, int ox, int ny, int nx)
{
	char* result = new char[5]; // Allocate space for 4 characters + null terminator
	result[0] = (char)(oy + 'a'); // Convert ox to alphabetic character
	result[1] = (char)(7 - ox + '1'); // Convert oy to numeric character from 1 to 8
	result[2] = (char)(nx + 'a'); // Convert nx to alphabetic character
	result[3] = (char)(7 - ny + '1'); // Convert ny to numeric character from 1 to 8
	result[4] = '\0'; // Null terminator for the string
	return result;
}

std::vector<int> Parser::alphabeticFormToCoordinates(std::string command)
{
	int ox, oy, nx, ny;
	std::string move = command.substr(0, command.find(" ponder"));
	size_t pos = move.find("bestmove");
	if (pos == 0)
		move = move.erase(0, 9);

	const char* cmove = move.c_str();

	oy = cmove[0] - 'a'; // Convert alphabetic character to numeric index
	ox = ('8' - cmove[1]); // Convert numeric character to index
	ny = cmove[2] - 'a'; // Convert alphabetic character to numeric index
	nx = ('8' - cmove[3]); // Convert numeric character to index
	printf("Parser: %s to ox: %d, oy: %d, nx: %d, ny: %d\n", move.c_str(), ox, oy, nx, ny);

	return { ox, oy, nx, ny };
}

std::string Parser::getAlphabeticFormFromString(std::string command)
{
	int ox, oy, nx, ny;
	std::string move = command.substr(0, command.find(" ponder"));
	size_t pos = move.find("bestmove");
	if (pos == 0)
		move = move.erase(0, 9);

	return move;
}