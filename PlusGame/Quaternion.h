#pragma once
#include "Vector3.h"
#include "Matrix.h"
class Quaternion
{
public:
	float X;

	float Y;

	float Z;

	float W;

	Quaternion() :X(0), Y(0), Z(0), W(0) {}
	Quaternion(float x, float y, float z, float w) :X(x), Y(y), Z(z), W(w) {}
	Quaternion(Vector3 value, float w) :X(value.X), Y(value.Y), Z(value.Z), W(w) {}
	//Quaternion(Vector4 value) {}

	static const Quaternion Identity;

	// Assignment operator
	Quaternion& operator=(const Quaternion& other);

	// Quaternion operations
	static Quaternion Add(const Quaternion& quaternion1, const Quaternion& quaternion2);
	static void Add(const Quaternion& quaternion1, const Quaternion& quaternion2, Quaternion& result);

	static Quaternion Concatenate(const Quaternion& value1, const Quaternion& value2);
	static void Concatenate(const Quaternion& value1, const Quaternion& value2, Quaternion& result);

	void Conjugate();
	static void Conjugate(Quaternion& value);
	static void Conjugate(const Quaternion& value, Quaternion& result);

	static Quaternion CreateFromAxisAngle(const Vector3& axis, float angle);
	static void CreateFromAxisAngle(const Vector3& axis, float angle, Quaternion& result);

	static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	static void CreateFromYawPitchRoll(float yaw, float pitch, float roll, Quaternion& result);

	static Quaternion Divide(Quaternion& quaternion1, Quaternion& quaternion2);
	static void Divide(Quaternion& quaternion1, Quaternion& quaternion2, Quaternion& result);

	static float Dot(Quaternion& quaternion1, Quaternion& quaternion2);
	static void Dot(Quaternion& quaternion1, Quaternion& quaternion2, float& result);

	float Length();
	float LengthSquared();

	static Quaternion Lerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount);
	static void Lerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount, Quaternion& result);

	static Quaternion Slerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount);
	static void Slerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount, Quaternion& result);

	static Quaternion Subtract(Quaternion& quaternion1, Quaternion& quaternion2);
	static void Subtract(Quaternion& quaternion1, Quaternion& quaternion2, Quaternion& result);

	static Quaternion Multiply(Quaternion& quaternion1, Quaternion& quaternion2);
	static Quaternion Multiply(Quaternion& quaternion1, float scaleFactor);
	static void Multiply(Quaternion& quaternion1, float scaleFactor, Quaternion& result);
	static void Multiply(Quaternion& quaternion1, Quaternion& quaternion2, Quaternion& result);

	static void Negate(Quaternion& quaternion);

	void Negate();
	void Normalize();

	static Quaternion CreateFromRotationMatrix(Matrix& matrix);
	static void CreateFromRotationMatrix(Matrix& matrix, Quaternion& result);

	Quaternion operator+(const Quaternion& quaternion) const;
	Quaternion operator/(const Quaternion& quaternion) const;
	bool operator==(const Quaternion& quaternion) const;
	bool operator!=(const Quaternion& quaternion) const;
	Quaternion operator*(const Quaternion& quaternion) const;
	Quaternion operator*(float scaleFactor) const;
	Quaternion operator-(const Quaternion& quaternion) const;
	Quaternion operator-() const;

	//TODO implement the rest of the function that depend on Matrix
};

