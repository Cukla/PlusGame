#include "Vector2.h"

Vector2 operator-(const Vector2& value) {
	return Vector2(-value.X, -value.Y);
}

Vector2 operator+(const Vector2& value1, const Vector2& value2) {
	return Vector2(value1.X + value2.X, value1.Y + value2.Y);
}

Vector2 operator-(const Vector2& value1, const Vector2& value2) {
	return Vector2(value1.X - value2.X, value1.Y - value2.Y);
}

Vector2 operator*(const Vector2& value1, const Vector2& value2) {
	return Vector2(value1.X * value2.X, value1.Y * value2.Y);
}

Vector2 operator*(const Vector2& value, float scaleFactor) {
	return Vector2(value.X * scaleFactor, value.Y * scaleFactor);
}

Vector2 operator*(float scaleFactor, const Vector2& value) {
	return Vector2(value.X * scaleFactor, value.Y * scaleFactor);
}

Vector2 operator/(const Vector2& value1, const Vector2& value2) {
	return Vector2(value1.X / value2.X, value1.Y / value2.Y);
}

Vector2 operator/(const Vector2& value, float divider) {
	float factor = 1.0f / divider;
	return Vector2(value.X * factor, value.Y * factor);
}

bool operator==(const Vector2& value1, const Vector2& value2) {
	return value1.X == value2.X && value1.Y == value2.Y;
}

bool operator!=(const Vector2& value1, const Vector2& value2) {
	return value1.X != value2.X || value1.Y != value2.Y;
}

Vector2 Vector2::Add(Vector2 value1, Vector2 value2)
{
	value1.X += value2.X;
	value1.Y += value2.Y;
	return value1;
}

void Vector2::Add(Vector2& value1, Vector2& value2, Vector2& result)
{
	result.X = value1.X + value2.X;
	result.Y = value1.Y + value2.Y;
}

void Vector2::Ceiling()
{
	X = std::ceil(X);
	Y = std::ceil(Y);
}

Vector2 Vector2::Ceiling(Vector2 value)
{
	return Vector2(std::ceil(value.X), std::ceil(value.Y));
}

void Vector2::Ceiling(Vector2& value, Vector2& result)
{
	result.X = std::ceil(value.X);
	result.Y = std::ceil(value.Y);
}

Vector2 Vector2::Barycentric(Vector2 value1, Vector2 value2, Vector2 value3, float amount1, float amount2)
{
	return Vector2(
		value1.X + (amount1 * (value2.X - value1.X)) + (amount2 * (value3.X - value1.X)),
		value1.Y + (amount1 * (value2.Y - value1.Y)) + (amount2 * (value3.Y - value1.Y))
	);
}

void Vector2::Barycentric(Vector2& value1, Vector2& value2, Vector2& value3, float amount1, float amount2, Vector2& result)
{
	result.X = value1.X + (amount1 * (value2.X - value1.X)) + (amount2 * (value3.X - value1.X));
	result.Y = value1.Y + (amount1 * (value2.Y - value1.Y)) + (amount2 * (value3.Y - value1.Y));
}

Vector2 Vector2::CatmullRom(Vector2 value1, Vector2 value2, Vector2 value3, Vector2 value4, float amount)
{
	return Vector2(MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount), MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount));
}

void Vector2::CatmullRom(Vector2& value1, Vector2& value2, Vector2& value3, Vector2& value4, float amount, Vector2& result)
{
	result.X = MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount);
	result.Y = MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount);
}

Vector2 Vector2::Clamp(Vector2 value1, Vector2 min, Vector2 max)
{
	return Vector2(
		std::fmax(min.X, std::fmin(value1.X, max.X)),
		std::fmax(min.Y, std::fmin(value1.Y, max.Y))
	);
}

void Vector2::Clamp(Vector2& value1, Vector2& min, Vector2& max, Vector2& result)
{
	result.X = std::fmax(min.X, std::fmin(value1.X, max.X));
	result.Y = std::fmax(min.Y, std::fmin(value1.Y, max.Y));
}

float Vector2::Distance(Vector2 value1, Vector2 value2)
{
	float v1 = value1.X - value2.X, v2 = value1.Y - value2.Y;
	return std::sqrt((v1 * v1) + (v2 * v2));
}

void Vector2::Distance(Vector2& value1, Vector2& value2, float& result)
{
	float v1 = value1.X - value2.X, v2 = value1.Y - value2.Y;
	result = std::sqrt((v1 * v1) + (v2 * v2));
}

float Vector2::DistanceSquared(Vector2 value1, Vector2 value2)
{
	float v1 = value1.X - value2.X, v2 = value1.Y - value2.Y;
	return (v1 * v1) + (v2 * v2);
}

void Vector2::DistanceSquared(Vector2& value1, Vector2& value2, float& result)
{
	float v1 = value1.X - value2.X, v2 = value1.Y - value2.Y;
	result = (v1 * v1) + (v2 * v2);
}

Vector2 Vector2::Divide(Vector2 value1, Vector2 value2)
{
	value1.X /= value2.X;
	value1.Y /= value2.Y;
	return value1;
}

void Vector2::Divide(Vector2& value1, Vector2& value2, Vector2& result)
{
	result.X = value1.X / value2.X;
	result.Y = value1.Y / value2.Y;
}

Vector2 Vector2::Divide(Vector2 value1, float divider)
{
	float factor = 1.0f / divider;
	value1.X *= factor;
	value1.Y *= factor;
	return value1;
}

void Vector2::Divide(Vector2& value1, float divider, Vector2& result)
{
	float factor = 1.0f / divider;
	result.X = value1.X * factor;
	result.Y = value1.Y * factor;
}

float Vector2::Dot(Vector2 value1, Vector2 value2)
{
	return (value1.X * value2.X) + (value1.Y * value2.Y);
}

void Vector2::Dot(Vector2& value1, Vector2& value2, float& result)
{
	result = (value1.X * value2.X) + (value1.Y * value2.Y);
}

bool Vector2::Equals(Vector2 other)
{
	return (X == other.X) && (Y == other.Y);
}

void Vector2::Floor()
{
	X = std::floor(X);
	Y = std::floor(Y);
}

Vector2 Vector2::Floor(Vector2 value)
{
	return Vector2(std::floor(value.X), std::floor(value.Y));
}

void Vector2::Floor(Vector2& value, Vector2& result)
{
	result.X = std::floor(value.X);
	result.Y = std::floor(value.Y);
}

int Vector2::GetHashCode()
{
	return 1; //_cast<int>((X.GetHashCode() * 397) ^ Y.GetHashCode());
}

Vector2 Vector2::Hermite(Vector2 value1, Vector2 tangent1, Vector2 value2, Vector2 tangent2, float amount)
{
	return Vector2(
		MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount),
		MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount)
	);
}

void Vector2::Hermite(Vector2& value1, Vector2& tangent1, Vector2& value2, Vector2& tangent2, float amount, Vector2& result)
{
	result.X = MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount);
	result.Y = MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount);
}

float Vector2::Length()
{
	return sqrt((X * X) + (Y * Y));
}

float Vector2::LengthSquared()
{
	return (X * X) + (Y * Y);
}

Vector2 Vector2::Lerp(Vector2 value1, Vector2 value2, float amount)
{
	return Vector2(
		MathHelper::Lerp(value1.X, value2.X, amount),
		MathHelper::Lerp(value1.Y, value2.Y, amount)
	);
}

void Vector2::Lerp(Vector2& value1, Vector2& value2, float amount, Vector2& result)
{
	result.X = MathHelper::Lerp(value1.X, value2.X, amount);
	result.Y = MathHelper::Lerp(value1.Y, value2.Y, amount);
}

Vector2 Vector2::LerpPrecise(Vector2 value1, Vector2 value2, float amount)
{
	return Vector2(
		MathHelper::LerpPrecise(value1.X, value2.X, amount),
		MathHelper::LerpPrecise(value1.Y, value2.Y, amount)
	);
}

void Vector2::LerpPrecise(Vector2& value1, Vector2& value2, float amount, Vector2& result)
{
	result.X = MathHelper::LerpPrecise(value1.X, value2.X, amount);
	result.Y = MathHelper::LerpPrecise(value1.Y, value2.Y, amount);
}

Vector2 Vector2::Max(Vector2 value1, Vector2 value2)
{
	return Vector2(
		value1.X > value2.X ? value1.X : value2.X,
		value1.Y > value2.Y ? value1.Y : value2.Y
	);
}

void Vector2::Max(Vector2& value1, Vector2& value2, Vector2& result)
{
	result.X = value1.X > value2.X ? value1.X : value2.X;
	result.Y = value1.Y > value2.Y ? value1.Y : value2.Y;
}

Vector2 Vector2::Min(Vector2 value1, Vector2 value2)
{
	return Vector2(
		value1.X < value2.X ? value1.X : value2.X,
		value1.Y < value2.Y ? value1.Y : value2.Y
	);
}

void Vector2::Min(Vector2& value1, Vector2& value2, Vector2& result)
{
	result.X = value1.X < value2.X ? value1.X : value2.X;
	result.Y = value1.Y < value2.Y ? value1.Y : value2.Y;
}

Vector2 Vector2::Multiply(Vector2 value1, Vector2 value2)
{
	value1.X *= value2.X;
	value1.Y *= value2.Y;
	return value1;
}

void Vector2::Multiply(Vector2& value1, Vector2& value2, Vector2& result)
{
	result.X = value1.X * value2.X;
	result.Y = value1.Y * value2.Y;
}

Vector2 Vector2::Multiply(Vector2 value1, float scaleFactor)
{
	value1.X *= scaleFactor;
	value1.Y *= scaleFactor;
	return value1;
}

void Vector2::Multiply(Vector2& value1, float scaleFactor, Vector2& result)
{
	result.X = value1.X * scaleFactor;
	result.Y = value1.Y * scaleFactor;
}

Vector2 Vector2::Negate(Vector2 value)
{
	value.X = -value.X;
	value.Y = -value.Y;
	return value;
}

void Vector2::Negate(Vector2& value, Vector2& result)
{
	result.X = -value.X;
	result.Y = -value.Y;
}

void Vector2::Normalize()
{
	float val = 1.0f / sqrt((X * X) + (Y * Y));
	X *= val;
	Y *= val;
}

Vector2 Vector2::Normalize(Vector2 value)
{
	float val = 1.0f / sqrt((value.X * value.X) + (value.Y * value.Y));
	value.X *= val;
	value.Y *= val;
	return value;
}

void Vector2::Normalize(Vector2& value, Vector2& result)
{
	float val = 1.0f / sqrt((value.X * value.X) + (value.Y * value.Y));
	result.X = value.X * val;
	result.Y = value.Y * val;
}

Vector2 Vector2::Reflect(Vector2 vector, Vector2 normal)
{
	Vector2 result(0, 0);
	float val = 2.0f * ((vector.X * normal.X) + (vector.Y * normal.Y));
	result.X = vector.X - (normal.X * val);
	result.Y = vector.Y - (normal.Y * val);
	return result;
}

void Vector2::Reflect(Vector2& vector, Vector2& normal, Vector2& result)
{
	float val = 2.0f * ((vector.X * normal.X) + (vector.Y * normal.Y));
	result.X = vector.X - (normal.X * val);
	result.Y = vector.Y - (normal.Y * val);
}

void Vector2::Round()
{
	X = round(X);
	Y = round(Y);
}

Vector2 Vector2::Round(Vector2 value)
{
	value.X = round(value.X);
	value.Y = round(value.Y);
	return value;
}

void Vector2::Round(Vector2& value, Vector2& result)
{
	result.X = round(value.X);
	result.Y = round(value.Y);
}

Vector2 Vector2::SmoothStep(Vector2 value1, Vector2 value2, float amount)
{
	return Vector2(
		MathHelper::SmoothStep(value1.X, value2.X, amount),
		MathHelper::SmoothStep(value1.Y, value2.Y, amount)
	);
}

void Vector2::SmoothStep(Vector2& value1, Vector2& value2, float amount, Vector2& result)
{
	result.X = MathHelper::SmoothStep(value1.X, value2.X, amount);
	result.Y = MathHelper::SmoothStep(value1.Y, value2.Y, amount);
}

Vector2 Vector2::Subtract(Vector2 value1, Vector2 value2)
{
	value1.X -= value2.X;
	value1.Y -= value2.Y;
	return value1;
}

void Vector2::Subtract(Vector2& value1, Vector2& value2, Vector2& result)
{
	result.X = value1.X - value2.X;
	result.Y = value1.Y - value2.Y;
}

std::string Vector2::ToString()
{
	return "{X:" + std::to_string(X) + " Y:" + std::to_string(Y) + "}";
}

// Assuming Point is defined appropriately in your code
Point Vector2::ToPoint()
{
	return Point(static_cast<int>(X), static_cast<int>(Y));
}