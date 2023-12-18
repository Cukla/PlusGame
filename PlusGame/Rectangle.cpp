#include "Rectangle.h"

int Rectangle::GetRight()
{
	return X + Width;
}

int Rectangle::GetLeft()
{
	return X;
}

int Rectangle::GetTop()
{
	return Y;
}

int Rectangle::GetBottom()
{
	return Y + Height;
}

bool Rectangle::IsEmpty()
{
	return ((((this->Width == 0) && (this->Height == 0)) && (this->X == 0)) && (this->Y == 0));;
}

Point Rectangle::GetLocation()
{
	return Point(X, Y);
}

Point Rectangle::GetSize()
{
	return Point(Width, Height);
}

Point Rectangle::GetCenter()
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
