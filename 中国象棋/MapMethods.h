#pragma once

#include <iostream>
#include <math.h>

struct Grid;
//{
//	int Id;
//	bool IsRed;
//	int x, y;
//};

bool CanMoveToTarget(const Grid(&map)[10][9], const Grid& current, int targetX, int targetY);

void ApplyMove(Grid& current, Grid& target);