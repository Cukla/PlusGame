#pragma once
#include "Vector2.h"
struct Vector3
{
public:
	float X;
	float Y;
	float Z;

public:
	Vector3() : X(0), Y(0), Z(0) {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3(float value) : X(value), Y(value), Z(value) {}
	Vector3(Vector2 xy, float z) : X(xy.X), Y(xy.Y), Z(z) {}

	// Static members  
	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Right;
	static const Vector3 Left;
	static const Vector3 Forward;
	static const Vector3 Backward;

	// Operator overloads
	Vector3& operator=(const Vector3& other);
	Vector3 operator+(const Vector3& other) const;
	Vector3& operator+=(const Vector3& other);
	Vector3 operator-(const Vector3& other) const;
	Vector3& operator-=(const Vector3& other);
	Vector3 operator*(float scalar) const;
	Vector3& operator*=(float scalar);
	Vector3 operator/(float scalar) const;
	Vector3& operator/=(float scalar);
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	void Round();
	void Normalize();
	void Ceiling();
	void Floor();

	// Static methods
	static Vector3 Add(Vector3 value1, Vector3 value2);
	static void Add(Vector3& value1, Vector3& value2, Vector3& result);
	static Vector3 Barycentric(Vector3 value1, Vector3 value2, Vector3 value3, float amount1, float amount2);
	static void Barycentric(Vector3& value1, Vector3& value2, Vector3& value3, float amount1, float amount2, Vector3& result);
	static Vector3 CatmullRom(Vector3 value1, Vector3 value2, Vector3 value3, Vector3 value4, float amount);
	static void CatmullRom(Vector3& value1, Vector3& value2, Vector3& value3, Vector3& value4, float amount, Vector3& result);
	static Vector3 Ceiling(Vector3 value);
	static void Ceiling(Vector3& value, Vector3& result);
	static Vector3 Clamp(Vector3 value1, Vector3 min, Vector3 max);
	static void Clamp(Vector3& value1, Vector3& min, Vector3& max, Vector3& result);
	static Vector3 Cross(Vector3 vector1, Vector3 vector2);
	static void Cross(Vector3& vector1, Vector3& vector2, Vector3& result);
	static float Distance(Vector3 value1, Vector3 value2);
	static void Distance(Vector3& value1, Vector3& value2, float& result);
	static float DistanceSquared(Vector3 value1, Vector3 value2);
	static void DistanceSquared(Vector3& value1, Vector3& value2, float& result);
	static Vector3 Divide(Vector3 value1, Vector3 value2);
	static Vector3 Divide(Vector3 value1, float divider);
	static void Divide(Vector3& value1, float divider, Vector3& result);
	static void Divide(Vector3& value1, Vector3& value2, Vector3& result);
	static float Dot(Vector3 value1, Vector3 value2);
	static void Dot(Vector3& value1, Vector3& value2, float& result);
	static Vector3 Floor(Vector3 value);
	static void Floor(Vector3& value, Vector3& result);
	static Vector3 Hermite(Vector3 value1, Vector3 tangent1, Vector3 value2, Vector3 tangent2, float amount);
	static void Hermite(Vector3& value1, Vector3& tangent1, Vector3& value2, Vector3& tangent2, float amount, Vector3& result);
	static float Length(Vector3& vector);
	static float LengthSquared(Vector3& vector);
	float LengthSquared();
	static Vector3 Lerp(Vector3 value1, Vector3 value2, float amount);
	static void Lerp(Vector3& value1, Vector3& value2, float amount, Vector3& result);
	static Vector3 LerpPrecise(Vector3 value1, Vector3 value2, float amount);
	static void LerpPrecise(Vector3& value1, Vector3& value2, float amount, Vector3& result);
	static Vector3 Max(Vector3 value1, Vector3 value2);
	static void Max(Vector3& value1, Vector3& value2, Vector3& result);
	static Vector3 Min(Vector3 value1, Vector3 value2);
	static void Min(Vector3& value1, Vector3& value2, Vector3& result);
	static Vector3 Multiply(Vector3 value1, Vector3 value2);
	static Vector3 Multiply(Vector3 value1, float scaleFactor);
	static void Multiply(Vector3& value1, float scaleFactor, Vector3& result);
	static void Multiply(Vector3& value1, Vector3& value2, Vector3& result);
	Vector3 Negate();
	static Vector3 Negate(Vector3 value);
	static void Negate(Vector3& value, Vector3& result);
	static Vector3 Normalize(Vector3 value);
	static void Normalize(Vector3& value, Vector3& result);
	static Vector3 Reflect(Vector3 vector, Vector3 normal);
	static void Reflect(Vector3& vector, Vector3& normal, Vector3& result);
	static Vector3 Round(Vector3 value);
	static void Round(Vector3& value, Vector3& result);
	static Vector3 SmoothStep(Vector3 value1, Vector3 value2, float amount);
	static void SmoothStep(Vector3& value1, Vector3& value2, float amount, Vector3& result);
	static Vector3 Subtract(Vector3 value1, Vector3 value2);
	static void Subtract(Vector3& value1, Vector3& value2, Vector3& result);

	//TODO implement Transform
};

