#pragma once
#include "Point.h"

struct Rectangle
{
public:
	int X;

	int Y;

	int Width;

	int Height;

public:
	int GetRight();
	int GetLeft();
	int GetTop();
	int GetBottom();

	bool IsEmpty();

	Point GetLocation();
	Point GetSize();
	Point GetCenter();

	Rectangle(int x, int y, int w, int h) : X(x), Y(y), Height(h), Width(w) {}
	Rectangle(Point position, Point size);
};



