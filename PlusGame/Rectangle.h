#pragma once
#include "Point.h"

struct Rectangle
{
public:
	/// <summary>
   /// The x coordinate of the top-left corner of this <see cref="Rectangle"/>.
   /// </summary> 
	int X;

	/// <summary>
	/// The y coordinate of the top-left corner of this <see cref="Rectangle"/>.
	/// </summary> 
	int Y;

	/// <summary>
	/// The width of this <see cref="Rectangle"/>.
	/// </summary> 
	int Width;

	/// <summary>
	/// The height of this <see cref="Rectangle"/>.
	/// </summary> 
	int Height;

public:
	int getRight();
	int getLeft();
	int getTop();
	int getBottom();

	bool isEmpty();

	Point getLocation();
	Point getSize();
	Point getCenter();

	Rectangle(int x, int y, int w, int h) : X(x), Y(y), Height(h), Width(w) {}
	Rectangle(Point position, Point size);
};



