#pragma once

class Point
{
public:
	Point():coord_X(0), coord_Y(0) {}
	Point(int x, int y):coord_X(x), coord_Y(y) {}
	Point(const Point& point):coord_X(point.coord_X), coord_Y(point.coord_Y) {}

	int coord_X = 0, coord_Y = 0;
};