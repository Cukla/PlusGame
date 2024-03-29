#include "Vector4.h"

Vector4 operator-(const Vector4& value) {
	return Vector4(-value.X, -value.Y, -value.Z, -value.W);
}

Vector4 operator+(Vector4& value1, const Vector4& value2) {
	value1.X += value2.X;
	value1.Y += value2.Y;
	value1.Z += value2.Z;
	value1.W += value2.W;
	return value1;
}

Vector4 operator-(Vector4& value1, const Vector4& value2) {
	value1.X -= value2.X;
	value1.Y -= value2.Y;
	value1.Z -= value2.Z;
	value1.W -= value2.W;
	return value1;
}

Vector4 operator*(Vector4& value1, const Vector4& value2) {
	value1.X *= value2.X;
	value1.Y *= value2.Y;
	value1.Z *= value2.Z;
	value1.W *= value2.W;
	return value1;
}

Vector4 operator*(Vector4& value, float scaleFactor) {
	value.X *= scaleFactor;
	value.Y *= scaleFactor;
	value.Z *= scaleFactor;
	value.W *= scaleFactor;
	return value;
}

Vector4 operator*(float scaleFactor, Vector4& value) {
	value.X *= scaleFactor;
	value.Y *= scaleFactor;
	value.Z *= scaleFactor;
	value.W *= scaleFactor;
	return value;
}

Vector4 operator/(Vector4& value1, const Vector4& value2) {
	value1.X /= value2.X;
	value1.Y /= value2.Y;
	value1.Z /= value2.Z;
	value1.W /= value2.W;
	return value1;
}

Vector4 operator/(Vector4& value, float divider) {
	float factor = 1.0f / divider;
	value.X *= factor;
	value.Y *= factor;
	value.Z *= factor;
	value.W *= factor;
	return value;
}

bool operator==(const Vector4& value1, const Vector4& value2) {
	return value1.X == value2.X && value1.Y == value2.Y && value1.Z == value2.Z && value1.W == value2.W;
}

bool operator!=(const Vector4& value1, const Vector4& value2) {
	return value1.X != value2.X || value1.Y != value2.Y || value1.Z != value2.Z && value1.W != value2.W;
}

Vector4 Vector4::Barycentric(Vector4& value1, Vector4& value2, Vector4& value3, float amount1, float amount2)
{
	return Vector4(
		MathHelper::Barycentric(value1.X, value2.X, value3.X, amount1, amount2),
		MathHelper::Barycentric(value1.Y, value2.Y, value3.Y, amount1, amount2),
		MathHelper::Barycentric(value1.Z, value2.Z, value3.Z, amount1, amount2),
		MathHelper::Barycentric(value1.W, value2.W, value3.W, amount1, amount2));
}

void Vector4::Barycentric(Vector4& value1, Vector4& value2, Vector4& value3, float amount1, float amount2, Vector4& result)
{
	result.X = MathHelper::Barycentric(value1.X, value2.X, value3.X, amount1, amount2);
	result.Y = MathHelper::Barycentric(value1.Y, value2.Y, value3.Y, amount1, amount2);
	result.Z = MathHelper::Barycentric(value1.Z, value2.Z, value3.Z, amount1, amount2);
	result.W = MathHelper::Barycentric(value1.W, value2.W, value3.W, amount1, amount2);
}

Vector4 Vector4::CatmullRom(Vector4& value1, Vector4& value2, Vector4& value3, Vector4& value4, float amount)
{
	return   Vector4(
		MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount),
		MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount),
		MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount),
		MathHelper::CatmullRom(value1.W, value2.W, value3.W, value4.W, amount));
}

void Vector4::CatmullRom(Vector4& value1, Vector4& value2, Vector4& value3, Vector4& value4, float amount, Vector4& result)
{
	result.X = MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount);
	result.Y = MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount);
	result.Z = MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount);
	result.W = MathHelper::CatmullRom(value1.W, value2.W, value3.W, value4.W, amount);
}

void Vector4::Ceiling()
{
	X = ceil(X);
	Y = ceil(Y);
	Z = ceil(Z);
	W = ceil(W);
}

void Vector4::Ceiling(Vector4& value)
{
	value.X = ceil(value.X);
	value.Y = ceil(value.Y);
	value.Z = ceil(value.Z);
	value.W = ceil(value.W);
}

void Vector4::Ceiling(Vector4& value, Vector4& result)
{
	result.X = ceil(value.X);
	result.Y = ceil(value.Y);
	result.Z = ceil(value.Z);
	result.W = ceil(value.W);
}

Vector4 Vector4::Clamp(Vector4& value1, Vector4& min, Vector4 max)
{
	return Vector4(
		MathHelper::Clamp(value1.X, min.X, max.X),
		MathHelper::Clamp(value1.Y, min.Y, max.Y),
		MathHelper::Clamp(value1.Z, min.Z, max.Z),
		MathHelper::Clamp(value1.W, min.W, max.W));
}

void Vector4::Clamp(Vector4& value1, Vector4& min, Vector4& max, Vector4& result)
{
	result.X = MathHelper::Clamp(value1.X, min.X, max.X);
	result.Y = MathHelper::Clamp(value1.Y, min.Y, max.Y);
	result.Z = MathHelper::Clamp(value1.Z, min.Z, max.Z);
	result.W = MathHelper::Clamp(value1.W, min.W, max.W);
}

float Vector4::Distance(Vector4& value1, Vector4& value2)
{
	return sqrt(DistanceSquared(value1, value2));
}

void Vector4::Distance(Vector4& value1, Vector4& value2, float& result)
{
	result = sqrt(DistanceSquared(value1, value2));
}

float Vector4::DistanceSquared(Vector4& value1, Vector4& value2)
{
	return (value1.W - value2.W) * (value1.W - value2.W) +
		(value1.X - value2.X) * (value1.X - value2.X) +
		(value1.Y - value2.Y) * (value1.Y - value2.Y) +
		(value1.Z - value2.Z) * (value1.Z - value2.Z);
}

void Vector4::DistanceSquared(Vector4& value1, Vector4& value2, float& result)
{
	result = (value1.W - value2.W) * (value1.W - value2.W) +
		(value1.X - value2.X) * (value1.X - value2.X) +
		(value1.Y - value2.Y) * (value1.Y - value2.Y) +
		(value1.Z - value2.Z) * (value1.Z - value2.Z);
}

float Vector4::Dot(Vector4& value1, Vector4& value2)
{
	return value1.X * value2.X + value1.Y * value2.Y + value1.Z * value2.Z + value1.W * value2.W;
}

void Vector4::Dot(Vector4& value1, Vector4& value2, float& result)
{
	result = value1.X * value2.X + value1.Y * value2.Y + value1.Z * value2.Z + value1.W * value2.W;
}

void Vector4::Vector4::Floor()
{
	X = floor(X);
	Y = floor(Y);
	Z = floor(Z);
	W = floor(W);
}

void Vector4::Floor(Vector4& value)
{
	value.X = floor(value.X);
	value.Y = floor(value.Y);
	value.Z = floor(value.Z);
	value.W = floor(value.W);
}

void Vector4::Floor(Vector4& value, Vector4& result)
{
	result.X = floor(value.X);
	result.Y = floor(value.Y);
	result.Z = floor(value.Z);
	result.W = floor(value.W);
}

Vector4 Vector4::Hermite(Vector4& value1, Vector4& tangent1, Vector4& value2, Vector4& tangent2, float amount)
{
	return Vector4(MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount),
		MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount),
		MathHelper::Hermite(value1.Z, tangent1.Z, value2.Z, tangent2.Z, amount),
		MathHelper::Hermite(value1.W, tangent1.W, value2.W, tangent2.W, amount));
}

void Vector4::Hermite(Vector4& value1, Vector4& tangent1, Vector4& value2, Vector4& tangent2, float amount, Vector4& result)
{
	result.W = MathHelper::Hermite(value1.W, tangent1.W, value2.W, tangent2.W, amount);
	result.X = MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount);
	result.Y = MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount);
	result.Z = MathHelper::Hermite(value1.Z, tangent1.Z, value2.Z, tangent2.Z, amount);
}

float Vector4::Vector4::Length()
{
	return sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
}

float Vector4::Vector4::LengthSquared()
{
	return (X * X) + (Y * Y) + (Z * Z) + (W * W);
}

Vector4 Vector4::Lerp(Vector4 value1, Vector4 value2, float amount)
{
	return Vector4(
		MathHelper::Lerp(value1.X, value2.X, amount),
		MathHelper::Lerp(value1.Y, value2.Y, amount),
		MathHelper::Lerp(value1.Z, value2.Z, amount),
		MathHelper::Lerp(value1.W, value2.W, amount));
}

void Vector4::Lerp(Vector4& value1, Vector4& value2, float amount, Vector4& result)
{
	result.X = MathHelper::Lerp(value1.X, value2.X, amount);
	result.Y = MathHelper::Lerp(value1.Y, value2.Y, amount);
	result.Z = MathHelper::Lerp(value1.Z, value2.Z, amount);
	result.W = MathHelper::Lerp(value1.W, value2.W, amount);
}

Vector4 Vector4::LerpPrecise(Vector4& value1, Vector4& value2, float amount)
{
	return Vector4(
		MathHelper::LerpPrecise(value1.X, value2.X, amount),
		MathHelper::LerpPrecise(value1.Y, value2.Y, amount),
		MathHelper::LerpPrecise(value1.Z, value2.Z, amount),
		MathHelper::LerpPrecise(value1.W, value2.W, amount));
}

void Vector4::LerpPrecise(Vector4& value1, Vector4& value2, float amount, Vector4& result)
{
	result.X = MathHelper::LerpPrecise(value1.X, value2.X, amount);
	result.Y = MathHelper::LerpPrecise(value1.Y, value2.Y, amount);
	result.Z = MathHelper::LerpPrecise(value1.Z, value2.Z, amount);
	result.W = MathHelper::LerpPrecise(value1.W, value2.W, amount);
}

Vector4 Vector4::Max(Vector4& value1, Vector4& value2)
{
	return Vector4(
		MathHelper::Max(value1.X, value2.X),
		MathHelper::Max(value1.Y, value2.Y),
		MathHelper::Max(value1.Z, value2.Z),
		MathHelper::Max(value1.W, value2.W));
}

void Vector4::Max(Vector4& value1, Vector4& value2, Vector4& result)
{
	result.X = MathHelper::Max(value1.X, value2.X);
	result.Y = MathHelper::Max(value1.Y, value2.Y);
	result.Z = MathHelper::Max(value1.Z, value2.Z);
	result.W = MathHelper::Max(value1.W, value2.W);
}

Vector4 Vector4::Min(Vector4& value1, Vector4& value2)
{
	return   Vector4(
		MathHelper::Min(value1.X, value2.X),
		MathHelper::Min(value1.Y, value2.Y),
		MathHelper::Min(value1.Z, value2.Z),
		MathHelper::Min(value1.W, value2.W));
}

void Vector4::Min(Vector4& value1, Vector4& value2, Vector4& result)
{
	result.X = MathHelper::Min(value1.X, value2.X);
	result.Y = MathHelper::Min(value1.Y, value2.Y);
	result.Z = MathHelper::Min(value1.Z, value2.Z);
	result.W = MathHelper::Min(value1.W, value2.W);
}

void Vector4::Negate(Vector4& value)
{
	value.X = -value.X;
	value.Y = -value.Y;
	value.Z = -value.Z;
	value.W = -value.W;
}

void Vector4::Negate()
{
	X = -X;
	Y = -Y;
	Z = -Z;
	W = -W;
}

void Vector4::Normalize()
{
	float factor = sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
	factor = 1.0f / factor;
	X *= factor;
	Y *= factor;
	Z *= factor;
	W *= factor;
}

void Vector4::Normalize(Vector4& value)
{
	float factor = sqrt((value.X * value.X) + (value.Y * value.Y) + (value.Z * value.Z) + (value.W * value.W));
	factor = 1.0f / factor;
	value.W *= factor;
	value.X *= factor;
	value.Y *= factor;
	value.Z *= factor;
}

void Vector4::Normalize(Vector4& value, Vector4& result)
{
	float factor = sqrt((value.X * value.X) + (value.Y * value.Y) + (value.Z * value.Z) + (value.W * value.W));
	factor = 1.0f / factor;
	result.W = value.W * factor;
	result.X = value.X * factor;
	result.Y = value.Y * factor;
	result.Z = value.Z * factor;
}

void Vector4::Round()
{
	X = round(X);
	Y = round(Y);
	Z = round(Z);
	W = round(W);
}

Vector4 Vector4::SmoothStep(Vector4& value1, Vector4& value2, float amount)
{
	return Vector4(
		MathHelper::SmoothStep(value1.X, value2.X, amount),
		MathHelper::SmoothStep(value1.Y, value2.Y, amount),
		MathHelper::SmoothStep(value1.Z, value2.Z, amount),
		MathHelper::SmoothStep(value1.W, value2.W, amount));
}

void Vector4::SmoothStep(Vector4& value1, Vector4& value2, float amount, Vector4& result)
{
	result.X = MathHelper::SmoothStep(value1.X, value2.X, amount);
	result.Y = MathHelper::SmoothStep(value1.Y, value2.Y, amount);
	result.Z = MathHelper::SmoothStep(value1.Z, value2.Z, amount);
	result.W = MathHelper::SmoothStep(value1.W, value2.W, amount);
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 2d-vector by the specified <see cref="Matrix"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector2"/>.</param>
/// <param name="matrix">The transformation <see cref="Matrix"/>.</param>
/// <returns>Transformed <see cref="Vector4"/>.</returns>
Vector4 Vector4::Transform(Vector2 value, Matrix matrix)
{
	Vector4 result;
	Transform(value, matrix, result);
	return result;
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 2d-vector by the specified <see cref="Quaternion"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector2"/>.</param>
/// <param name="rotation">The <see cref="Quaternion"/> which contains rotation transformation.</param>
/// <returns>Transformed <see cref="Vector4"/>.</returns>
Vector4 Vector4::Transform(Vector2& value, Quaternion& rotation)
{
	Vector4 result;
	Transform(value, rotation, result);
	return result;
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 3d-vector by the specified <see cref="Matrix"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector3"/>.</param>
/// <param name="matrix">The transformation <see cref="Matrix"/>.</param>
/// <returns>Transformed <see cref="Vector4"/>.</returns>
Vector4 Vector4::Transform(Vector3& value, Matrix& matrix)
{
	Vector4 result;
	Transform(value, matrix, result);
	return result;
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 3d-vector by the specified <see cref="Quaternion"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector3"/>.</param>
/// <param name="rotation">The <see cref="Quaternion"/> which contains rotation transformation.</param>
/// <returns>Transformed <see cref="Vector4"/>.</returns>
Vector4 Vector4::Transform(Vector3& value, Quaternion& rotation)
{
	Vector4 result;
	Transform(value, rotation, result);
	return result;
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 4d-vector by the specified <see cref="Matrix"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector4"/>.</param>
/// <param name="matrix">The transformation <see cref="Matrix"/>.</param>
/// <returns>Transformed <see cref="Vector4"/>.</returns>
Vector4 Vector4::Transform(Vector4& value, Matrix& matrix)
{
	Transform(value, matrix, value);
	return value;
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 4d-vector by the specified <see cref="Quaternion"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector4"/>.</param>
/// <param name="rotation">The <see cref="Quaternion"/> which contains rotation transformation.</param>
/// <returns>Transformed <see cref="Vector4"/>.</returns>
Vector4 Vector4::Transform(Vector4& value, Quaternion& rotation)
{
	Vector4 result;
	Transform(value, rotation, result);
	return result;
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 2d-vector by the specified <see cref="Matrix"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector2"/>.</param>
/// <param name="matrix">The transformation <see cref="Matrix"/>.</param>
/// <param name="result">Transformed <see cref="Vector4"/> as an output parameter.</param>
void Vector4::Transform(Vector2& value, Matrix& matrix, Vector4& result)
{
	result.X = (value.X * matrix.M11) + (value.Y * matrix.M21) + matrix.M41;
	result.Y = (value.X * matrix.M12) + (value.Y * matrix.M22) + matrix.M42;
	result.Z = (value.X * matrix.M13) + (value.Y * matrix.M23) + matrix.M43;
	result.W = (value.X * matrix.M14) + (value.Y * matrix.M24) + matrix.M44;
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 2d-vector by the specified <see cref="Quaternion"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector2"/>.</param>
/// <param name="rotation">The <see cref="Quaternion"/> which contains rotation transformation.</param>
/// <param name="result">Transformed <see cref="Vector4"/> as an output parameter.</param>
void Vector4::Transform(Vector2& value, Quaternion& rotation, Vector4& result)
{
	//throw new NotImplementedException();
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 3d-vector by the specified <see cref="Matrix"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector3"/>.</param>
/// <param name="matrix">The transformation <see cref="Matrix"/>.</param>
/// <param name="result">Transformed <see cref="Vector4"/> as an output parameter.</param>
void Vector4::Transform(Vector3& value, Matrix& matrix, Vector4& result)
{
	result.X = (value.X * matrix.M11) + (value.Y * matrix.M21) + (value.Z * matrix.M31) + matrix.M41;
	result.Y = (value.X * matrix.M12) + (value.Y * matrix.M22) + (value.Z * matrix.M32) + matrix.M42;
	result.Z = (value.X * matrix.M13) + (value.Y * matrix.M23) + (value.Z * matrix.M33) + matrix.M43;
	result.W = (value.X * matrix.M14) + (value.Y * matrix.M24) + (value.Z * matrix.M34) + matrix.M44;
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 3d-vector by the specified <see cref="Quaternion"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector3"/>.</param>
/// <param name="rotation">The <see cref="Quaternion"/> which contains rotation transformation.</param>
/// <param name="result">Transformed <see cref="Vector4"/> as an output parameter.</param>
void Vector4::Transform(Vector3& value, Quaternion& rotation, Vector4& result)
{
	//throw new NotImplementedException();
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 4d-vector by the specified <see cref="Matrix"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector4"/>.</param>
/// <param name="matrix">The transformation <see cref="Matrix"/>.</param>
/// <param name="result">Transformed <see cref="Vector4"/> as an output parameter.</param>
void Vector4::Transform(Vector4& value, Matrix& matrix, Vector4& result)
{
	auto x = (value.X * matrix.M11) + (value.Y * matrix.M21) + (value.Z * matrix.M31) + (value.W * matrix.M41);
	auto y = (value.X * matrix.M12) + (value.Y * matrix.M22) + (value.Z * matrix.M32) + (value.W * matrix.M42);
	auto z = (value.X * matrix.M13) + (value.Y * matrix.M23) + (value.Z * matrix.M33) + (value.W * matrix.M43);
	auto w = (value.X * matrix.M14) + (value.Y * matrix.M24) + (value.Z * matrix.M34) + (value.W * matrix.M44);
	result.X = x;
	result.Y = y;
	result.Z = z;
	result.W = w;
}

/// <summary>
/// Creates a new <see cref="Vector4"/> that contains a transformation of 4d-vector by the specified <see cref="Quaternion"/>.
/// </summary>
/// <param name="value">Source <see cref="Vector4"/>.</param>
/// <param name="rotation">The <see cref="Quaternion"/> which contains rotation transformation.</param>
/// <param name="result">Transformed <see cref="Vector4"/> as an output parameter.</param>
void Vector4::Transform(Vector4& value, Quaternion& rotation, Vector4& result)
{
	//throw new NotImplementedException();
}

/// <summary>
/// Apply transformation on vectors within array of <see cref="Vector4"/> by the specified <see cref="Matrix"/> and places the results in an another array.
/// </summary>
/// <param name="sourceArray">Source array.</param>
/// <param name="sourceIndex">The starting index of transformation in the source array.</param>
/// <param name="matrix">The transformation <see cref="Matrix"/>.</param>
/// <param name="destinationArray">Destination array.</param>
/// <param name="destinationIndex">The starting index in the destination array, where the first <see cref="Vector4"/> should be written.</param>
/// <param name="length">The number of vectors to be transformed.</param>
void Vector4::Transform(Vector4* sourceArray, int sourceIndex, Matrix& matrix, Vector4* destinationArray, int destinationIndex, int length)
{
	for (auto i = 0; i < length; i++)
	{
		auto value = sourceArray[sourceIndex + i];
		destinationArray[destinationIndex + i] = Transform(value, matrix);
	}
}

/// <summary>
/// Apply transformation on vectors within array of <see cref="Vector4"/> by the specified <see cref="Quaternion"/> and places the results in an another array.
/// </summary>
/// <param name="sourceArray">Source array.</param>
/// <param name="sourceIndex">The starting index of transformation in the source array.</param>
/// <param name="rotation">The <see cref="Quaternion"/> which contains rotation transformation.</param>
/// <param name="destinationArray">Destination array.</param>
/// <param name="destinationIndex">The starting index in the destination array, where the first <see cref="Vector4"/> should be written.</param>
/// <param name="length">The number of vectors to be transformed.</param>
void Vector4::Transform(Vector4* sourceArray, int sourceIndex, Quaternion& rotation, Vector4* destinationArray, int destinationIndex, int length)
{
	for (auto i = 0; i < length; i++)
	{
		auto value = sourceArray[sourceIndex + i];
		destinationArray[destinationIndex + i] = Transform(value, rotation);
	}
}

/// <summary>
/// Apply transformation on all vectors within array of <see cref="Vector4"/> by the specified <see cref="Matrix"/> and places the results in an another array.
/// </summary>
/// <param name="sourceArray">Source array.</param>
/// <param name="matrix">The transformation <see cref="Matrix"/>.</param>
/// <param name="destinationArray">Destination array.</param>
void Vector4::Transform(Vector4* sourceArray, Matrix& matrix, Vector4* destinationArray)
{
	int lenght = sizeof(sourceArray) / sizeof(sourceArray[0]);
	for (auto i = 0; i < lenght; i++)
	{
		auto value = sourceArray[i];
		destinationArray[i] = Transform(value, matrix);
	}
}

/// <summary>
/// Apply transformation on all vectors within array of <see cref="Vector4"/> by the specified <see cref="Quaternion"/> and places the results in an another array.
/// </summary>
/// <param name="sourceArray">Source array.</param>
/// <param name="rotation">The <see cref="Quaternion"/> which contains rotation transformation.</param>
/// <param name="destinationArray">Destination array.</param>
void Vector4::Transform(Vector4* sourceArray, Quaternion rotation, Vector4* destinationArray)
{
	int lenght = sizeof(sourceArray) / sizeof(sourceArray[0]);
	for (auto i = 0; i < lenght; i++)
	{
		auto value = sourceArray[i];
		destinationArray[i] = Transform(value, rotation);
	}
}