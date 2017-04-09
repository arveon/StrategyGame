#pragma once
#include <vector>

struct SimplePoint
{
	int x, y, val;
	SimplePoint() {}
	SimplePoint(int X, int Y, int value) { x = X; y = Y; val = value; }
	SimplePoint(int X, int Y, int value, std::vector<SimplePoint*> neighbours);
	std::vector<SimplePoint*> neighbours;
};
