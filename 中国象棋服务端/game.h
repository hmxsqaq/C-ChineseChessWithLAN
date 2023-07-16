#pragma once

#include <string>
enum SelectState
{
	SelectChess, PutChess
};

struct Grid
{
	int Id;
	bool IsRed;
	int x;
	int y;
};

void LoadGridImage();

void InitGame();

void PrintMap();

std::string SelectChessPiece();

void InputInformationAndMoveChess(std::string information);

std::string OutputInformation(Grid& current, Grid& target);