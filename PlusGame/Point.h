#pragma once
#include <string>
#include "Vector2.h"
struct Point
{
public:
	int X;
	int Y;

	Point(int x, int y) : X(x), Y(y) {}
	Point(int value) : X(value), Y(value) {}

	Point operator+(const Point& value2) const {
		return Point(X + value2.X, Y + value2.Y);
	}

	Point operator-(const Point& value2) const {
		return Point(X - value2.X, Y - value2.Y);
	}

	Point operator*(const Point& value2) const {
		return Point(X * value2.X, Y * value2.Y);
	}

	Point operator/(const Point& divisor) const {
		return Point(X / divisor.X, Y / divisor.Y);
	}

	bool operator==(const Point& other) const {
		return X == other.X && Y == other.Y;
	}

	bool operator!=(const Point& other) const {
		return !(*this == other);
	}

	size_t GetHashCode() const;
	std::string ToString() const;
	Vector2 ToVector2() const;
	void Deconstruct(int& x, int& y) const;
};

