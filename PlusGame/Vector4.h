#pragma once
#include "MathHelper.h"
#include <cmath>
#include "Vector2.h"
#include "Matrix.h"

class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;

public:
	Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
	Vector4(float value) : X(value), Y(value), Z(value), W(value) {}
	Vector4(Vector3 vector, float value) : X(vector.X), Y(vector.Y), Z(vector.Z), W(value) {}
	Vector4() : X(0), Y(0), Z(0), W(0) {}

	friend Vector4 operator-(Vector4& value);

	// Binary addition
	friend Vector4 operator+(Vector4& value1, Vector4& value2);

	// Binary subtraction
	friend Vector4 operator-(Vector4& value1, Vector4& value2);

	// Component-wise multiplication
	friend Vector4 operator*(Vector4& value1, Vector4& value2);

	// Scalar multiplication
	friend Vector4 operator*(Vector4& value, float scaleFactor);
	friend Vector4 operator*(float scaleFactor, Vector4& value);

	// Component-wise division
	friend Vector4 operator/(Vector4& value1, Vector4& value2);

	// Scalar division
	friend Vector4 operator/(Vector4& value, float divider);

	// Equality comparison
	friend bool operator==(Vector4& value1, Vector4& value2);

	// Inequality comparison
	friend bool operator!=(Vector4& value1, Vector4& value2);

	// Other member functions
	static Vector4 Barycentric(Vector4& value1, Vector4& value2, Vector4& value3, float amount1, float amount2);
	static void Barycentric(Vector4& value1, Vector4& value2, Vector4& value3, float amount1, float amount2, Vector4& result);

	Vector4 CatmullRom(Vector4& value1, Vector4& value2, Vector4& value3, Vector4& value4, float amount);
	void CatmullRom(Vector4& value1, Vector4& value2, Vector4& value3, Vector4& value4, float amount, Vector4& result);

	void Ceiling();
	static void Ceiling(Vector4& value);
	static void Ceiling(Vector4& value, Vector4& result);

	Vector4 Clamp(Vector4& value1, Vector4& min, Vector4 max);
	static void Clamp(Vector4& value, Vector4& min, Vector4& max, Vector4& result);

	float Distance(Vector4& value1, Vector4& value2);

	static void Distance(Vector4& value1, Vector4& value2, float& result);

	static float DistanceSquared(Vector4& value1, Vector4& value2);

	static void DistanceSquared(Vector4& value1, Vector4& value2, float& result);

	float Dot(Vector4& value1, Vector4& value2);

	static void Dot(Vector4& value1, Vector4& value2, float& result);

	void Floor();
	static void Floor(Vector4& value);
	static void Floor(Vector4& value, Vector4& result);

	Vector4 Hermite(Vector4& value1, Vector4& tangent1, Vector4& value2, Vector4& tangent2, float amount);

	static void Hermite(Vector4& value1, Vector4& tangent1, Vector4& value2, Vector4& tangent2, float amount, Vector4& result);

	float Length();
	float LengthSquared();

	Vector4 Lerp(Vector4 value1, Vector4 value2, float amount);
	static void Lerp(Vector4& value1, Vector4& value2, float amount, Vector4& result);

	Vector4 LerpPrecise(Vector4& value1, Vector4& value2, float amount);
	static void LerpPrecise(Vector4& value1, Vector4& value2, float amount, Vector4& result);

	Vector4 Max(Vector4& value1, Vector4& value2);
	static void Max(Vector4& value1, Vector4& value2, Vector4& result);

	Vector4 Min(Vector4& value1, Vector4& value2);
	static void Min(Vector4& value1, Vector4& value2, Vector4& result);

	void Negate(Vector4& value);
	void Negate();

	void Normalize();
	void Normalize(Vector4& value);
	static void Normalize(Vector4& value, Vector4& result);

	void Round();

	Vector4 SmoothStep(Vector4& value1, Vector4& value2, float amount);
	static void SmoothStep(Vector4& value1, Vector4& value2, float amount, Vector4& result);

	static Vector4 Transform(Vector2 value, Matrix matrix);
	static Vector4 Transform(Vector2& value, Quaternion& rotation);
	static Vector4 Transform(Vector3& value, Matrix& matrix);
	static Vector4 Transform(Vector3& value, Quaternion& rotation);
	static Vector4 Transform(Vector4& value, Matrix& matrix);
	static Vector4 Transform(Vector4& value, Quaternion& rotation);
	static void Transform(Vector2& value, Matrix& matrix, Vector4& result);
	static void Transform(Vector2& value, Quaternion& rotation, Vector4& result);
	static void Transform(Vector3& value, Matrix& matrix, Vector4& result);
	static void Transform(Vector3& value, Quaternion& rotation, Vector4& result);
	static void Transform(Vector4& value, Matrix& matrix, Vector4& result);
	static void Transform(Vector4& value, Quaternion& rotation, Vector4& result);
	static void Transform(Vector4* sourceArray, int sourceIndex, Matrix& matrix, Vector4* destinationArray, int destinationIndex, int length);
	static void Transform(Vector4* sourceArray, int sourceIndex, Quaternion& rotation, Vector4* destinationArray, int destinationIndex, int length);
	static void Transform(Vector4* sourceArray, Matrix& matrix, Vector4* destinationArray);
	static void Transform(Vector4* sourceArray, Quaternion rotation, Vector4* destinationArray);

	//TODO complete the transform region
};

