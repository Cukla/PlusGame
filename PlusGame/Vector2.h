#pragma once
#include <cmath>
#include "MathHelper.h"
#include <string>
#include "Point.h"

struct Vector2
{
public:
	float X;
	float Y;

public:
	Vector2(float x, float y) : X(x), Y(y) {}
	Vector2(float value) : X(value), Y(value) {}

	friend Vector2 operator-(const Vector2& value);

	// Binary addition
	friend Vector2 operator+(const Vector2& value1, const Vector2& value2);

	// Binary subtraction
	friend Vector2 operator-(const Vector2& value1, const Vector2& value2);

	// Component-wise multiplication
	friend Vector2 operator*(const Vector2& value1, const Vector2& value2);

	// Scalar multiplication
	friend Vector2 operator*(const Vector2& value, float scaleFactor);
	friend Vector2 operator*(float scaleFactor, const Vector2& value);

	// Component-wise division
	friend Vector2 operator/(const Vector2& value1, const Vector2& value2);

	// Scalar division
	friend Vector2 operator/(const Vector2& value, float divider);

	// Equality comparison
	friend bool operator==(const Vector2& value1, const Vector2& value2);

	// Inequality comparison
	friend bool operator!=(const Vector2& value1, const Vector2& value2);

	static Vector2 Add(Vector2 value1, Vector2 value2);
	static void Add(Vector2& value1, Vector2& value2, Vector2& result);

	static Vector2 Barycentric(Vector2 value1, Vector2 value2, Vector2 value3, float amount1, float amount2);
	static void Barycentric(Vector2& value1, Vector2& value2, Vector2& value3, float amount1, float amount2, Vector2& result);

	static Vector2 CatmullRom(Vector2 value1, Vector2 value2, Vector2 value3, Vector2 value4, float amount);
	static void CatmullRom(Vector2& value1, Vector2& value2, Vector2& value3, Vector2& value4, float amount, Vector2& result);

	void Ceiling();
	static Vector2 Ceiling(Vector2 value);
	static void Ceiling(Vector2& value, Vector2& result);

	static Vector2 Clamp(Vector2 value1, Vector2 min, Vector2 max);
	static void Clamp(Vector2& value1, Vector2& min, Vector2& max, Vector2& result);

	static float Distance(Vector2 value1, Vector2 value2);
	static void Distance(Vector2& value1, Vector2& value2, float& result);

	static float DistanceSquared(Vector2 value1, Vector2 value2);
	static void DistanceSquared(Vector2& value1, Vector2& value2, float& result);

	static Vector2 Divide(Vector2 value1, Vector2 value2);
	static void Divide(Vector2& value1, Vector2& value2, Vector2& result);

	static Vector2 Divide(Vector2 value1, float divider);
	static void Divide(Vector2& value1, float divider, Vector2& result);

	static float Dot(Vector2 value1, Vector2 value2);
	static void Dot(Vector2& value1, Vector2& value2, float& result);

	bool Equals(Vector2 other);

	void Floor();
	static Vector2 Floor(Vector2 value);
	static void Floor(Vector2& value, Vector2& result);

	int GetHashCode();

	static Vector2 Hermite(Vector2 value1, Vector2 tangent1, Vector2 value2, Vector2 tangent2, float amount);
	static void Hermite(Vector2& value1, Vector2& tangent1, Vector2& value2, Vector2& tangent2, float amount, Vector2& result);

	float Length();
	float LengthSquared();

	static Vector2 Lerp(Vector2 value1, Vector2 value2, float amount);
	static void Lerp(Vector2& value1, Vector2& value2, float amount, Vector2& result);

	static Vector2 LerpPrecise(Vector2 value1, Vector2 value2, float amount);
	static void LerpPrecise(Vector2& value1, Vector2& value2, float amount, Vector2& result);

	static Vector2 Max(Vector2 value1, Vector2 value2);
	static void Max(Vector2& value1, Vector2& value2, Vector2& result);

	static Vector2 Min(Vector2 value1, Vector2 value2);
	static void Min(Vector2& value1, Vector2& value2, Vector2& result);

	static Vector2 Multiply(Vector2 value1, Vector2 value2);
	static void Multiply(Vector2& value1, Vector2& value2, Vector2& result);

	static Vector2 Multiply(Vector2 value1, float scaleFactor);
	static void Multiply(Vector2& value1, float scaleFactor, Vector2& result);

	static Vector2 Negate(Vector2 value);
	static void Negate(Vector2& value, Vector2& result);

	void Normalize();
	static Vector2 Normalize(Vector2 value);
	static void Normalize(Vector2& value, Vector2& result);

	static Vector2 Reflect(Vector2 vector, Vector2 normal);
	static void Reflect(Vector2& vector, Vector2& normal, Vector2& result);

	void Round();
	static Vector2 Round(Vector2 value);
	static void Round(Vector2& value, Vector2& result);

	static Vector2 SmoothStep(Vector2 value1, Vector2 value2, float amount);
	static void SmoothStep(Vector2& value1, Vector2& value2, float amount, Vector2& result);

	static Vector2 Subtract(Vector2 value1, Vector2 value2);
	static void Subtract(Vector2& value1, Vector2& value2, Vector2& result);

	std::string ToString();

	Point ToPoint();

	//TODO Implement the rest of the methods that used Matrix and use Quarterion
};

