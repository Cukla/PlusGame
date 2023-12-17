#include "Rectangle.h"

int Rectangle::getRight()
{
	return X + Width;
}

int Rectangle::getLeft()
{
	return X;
}

int Rectangle::getTop()
{
	return Y;
}

int Rectangle::getBottom()
{
	return Y + Height;
}

bool Rectangle::isEmpty()
{
	return ((((this->Width == 0) && (this->Height == 0)) && (this->X == 0)) && (this->Y == 0));;
}

Point Rectangle::getLocation()
{
	return Point(X, Y);
}

Point Rectangle::getSize()
{
	return Point(Width, Height);
}

Point Rectangle::getCenter()
{
	return Point(this->X + (this->Width / 2), this->Y + (this->Height / 2));
}

Rectangle::Rectangle(Point position, Point size)
{
	X = position.X;
	Y = position.Y;
	Width = size.X;
	Height = size.Y;
}
