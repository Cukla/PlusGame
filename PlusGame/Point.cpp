#include "Point.h"

Point::Point(int x, int y)
{
	this->X = x;
	this->Y = y;
}

Point::Point(int value)
{
	X = value;
	Y = value;
}

size_t Point::GetHashCode() const {
	size_t hash = 17;
	hash = hash * 23 + std::hash<int>()(X);
	hash = hash * 23 + std::hash<int>()(Y);
	return hash;
}

std::string Point::ToString() const {
	return "{X:" + std::to_string(X) + " Y:" + std::to_string(Y) + "}";
}

Vector2 Point::ToVector2() const {
	return Vector2(X, Y);
}

void Point::Deconstruct(int& x, int& y) const {
	x = X;
	y = Y;
}
