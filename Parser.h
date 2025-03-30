#pragma once
#include <vector>
#include <string>

static class Parser
{
public:
	static char* coordinatesToAlphabeticForm(int ox, int oy, int nx, int ny);
	static std::vector<int> alphabeticFormToCoordinates(std::string command);
	static std::string getAlphabeticFormFromString(std::string command);
};

