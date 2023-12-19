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

	Rectangle() : X(0), Y(0), Height(0), Width(0) {}
	Rectangle(int x, int y, int w, int h) : X(x), Y(y), Height(h), Width(w) {}
	Rectangle(Point position, Point size);

	bool Contains(int x, int y);
	bool Contains(float x, float y);
	bool Contains(Point value);
	void Contains(Point& value, bool& result);
	bool Contains(Vector2& value);
	void Contains(Vector2& value, bool& result);
	bool Contains(Rectangle& value);
	void Contains(Rectangle& value, bool& result);

	void Inflate(int horizontalAmount, int verticalAmount);
	void Inflate(float horizontalAmount, float verticalAmount);
	bool Intersects(Rectangle& value);
	void Intersects(Rectangle& value, bool result);

	void Offset(int offsetX, int offsetY);
	void Offset(float offsetX, float offsetY);
	void Offset(Point& amount);
	void Offset(Vector2& amount);

	static Rectangle Intersect(Rectangle& value1, Rectangle& value2);
	static void Intersect(Rectangle& value1, Rectangle& value2, Rectangle& result);
	static Rectangle Union(Rectangle& value1, Rectangle& value2);
	static void Union(Rectangle& value1, Rectangle& value2, Rectangle& result);
};