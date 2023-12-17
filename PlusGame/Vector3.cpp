#include "Vector3.h" 

// Operator overloads
Vector3& Vector3::operator=(const Vector3& other)
{
	if (this != &other)
	{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
	}
	return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(X + other.X, Y + other.Y, Z + other.Z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(X - other.X, Y - other.Y, Z - other.Z);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
	return *this;
}

Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(X * scalar, Y * scalar, Z * scalar);
}

Vector3& Vector3::operator*=(float scalar)
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;
	return *this;
}

Vector3 Vector3::operator/(float scalar) const
{
	if (scalar != 0.0f)
	{
		float reciprocal = 1.0f / scalar;
		return Vector3(X * reciprocal, Y * reciprocal, Z * reciprocal);
	}
	// Handle division by zero gracefully
	return Vector3();
}

Vector3& Vector3::operator/=(float scalar)
{
	if (scalar != 0.0f)
	{
		float reciprocal = 1.0f / scalar;
		X *= reciprocal;
		Y *= reciprocal;
		Z *= reciprocal;
	}
	// Handle division by zero gracefully
	return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
	return X == other.X && Y == other.Y && Z == other.Z;
}

bool Vector3::operator!=(const Vector3& other) const
{
	return !(*this == other);
}

Vector3 Vector3::Add(Vector3 value1, Vector3 value2)
{
	value1.X += value2.X;
	value1.Y += value2.Y;
	value1.Z += value2.Z;
	return value1;
}

void Vector3::Add(Vector3& value1, Vector3& value2, Vector3& result)
{
	result.X = value1.X + value2.X;
	result.Y = value1.Y + value2.Y;
	result.Z = value1.Z + value2.Z;
}

Vector3 Vector3::Barycentric(Vector3 value1, Vector3 value2, Vector3 value3, float amount1, float amount2)
{
	return Vector3(
		MathHelper::Barycentric(value1.X, value2.X, value3.X, amount1, amount2),
		MathHelper::Barycentric(value1.Y, value2.Y, value3.Y, amount1, amount2),
		MathHelper::Barycentric(value1.Z, value2.Z, value3.Z, amount1, amount2)
	);
}

void Vector3::Barycentric(Vector3& value1, Vector3& value2, Vector3& value3, float amount1, float amount2, Vector3& result)
{
	result.X = MathHelper::Barycentric(value1.X, value2.X, value3.X, amount1, amount2);
	result.Y = MathHelper::Barycentric(value1.Y, value2.Y, value3.Y, amount1, amount2);
	result.Z = MathHelper::Barycentric(value1.Z, value2.Z, value3.Z, amount1, amount2);
}

Vector3 Vector3::CatmullRom(Vector3 value1, Vector3 value2, Vector3 value3, Vector3 value4, float amount)
{
	return Vector3(
		MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount),
		MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount),
		MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount)
	);
}

void Vector3::CatmullRom(Vector3& value1, Vector3& value2, Vector3& value3, Vector3& value4, float amount, Vector3& result)
{
	result.X = MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount);
	result.Y = MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount);
	result.Z = MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount);
}

void Vector3::Ceiling()
{
	X = std::ceil(X);
	Y = std::ceil(Y);
	Z = std::ceil(Z);
}

Vector3 Vector3::Ceiling(Vector3 value)
{
	value.X = std::ceil(value.X);
	value.Y = std::ceil(value.Y);
	value.Z = std::ceil(value.Z);
	return value;
}

void Vector3::Ceiling(Vector3& value, Vector3& result)
{
	result.X = std::ceil(value.X);
	result.Y = std::ceil(value.Y);
	result.Z = std::ceil(value.Z);
}

Vector3 Vector3::Clamp(Vector3 value1, Vector3 min, Vector3 max)
{
	return Vector3(
		MathHelper::Clamp(value1.X, min.X, max.X),
		MathHelper::Clamp(value1.Y, min.Y, max.Y),
		MathHelper::Clamp(value1.Z, min.Z, max.Z)
	);
}

void Vector3::Clamp(Vector3& value1, Vector3& min, Vector3& max, Vector3& result)
{
	result.X = MathHelper::Clamp(value1.X, min.X, max.X);
	result.Y = MathHelper::Clamp(value1.Y, min.Y, max.Y);
	result.Z = MathHelper::Clamp(value1.Z, min.Z, max.Z);
}

Vector3 Vector3::Cross(Vector3 vector1, Vector3 vector2)
{
	Vector3 result;
	Cross(vector1, vector2, result);
	return result;
}

void Vector3::Cross(Vector3& vector1, Vector3& vector2, Vector3& result)
{
	float x = vector1.Y * vector2.Z - vector2.Y * vector1.Z;
	float y = -(vector1.X * vector2.Z - vector2.X * vector1.Z);
	float z = vector1.X * vector2.Y - vector2.X * vector1.Y;
	result.X = x;
	result.Y = y;
	result.Z = z;
}

float Vector3::Distance(Vector3 value1, Vector3 value2)
{
	float result;
	Distance(value1, value2, result);
	return result;
}

void Vector3::Distance(Vector3& value1, Vector3& value2, float& result)
{
	DistanceSquared(value1, value2, result);
	result = std::sqrt(result);
}

float Vector3::DistanceSquared(Vector3 value1, Vector3 value2)
{
	return (value1.X - value2.X) * (value1.X - value2.X) +
		(value1.Y - value2.Y) * (value1.Y - value2.Y) +
		(value1.Z - value2.Z) * (value1.Z - value2.Z);
}

void Vector3::DistanceSquared(Vector3& value1, Vector3& value2, float& result)
{
	result = (value1.X - value2.X) * (value1.X - value2.X) +
		(value1.Y - value2.Y) * (value1.Y - value2.Y) +
		(value1.Z - value2.Z) * (value1.Z - value2.Z);
}

Vector3 Vector3::Divide(Vector3 value1, Vector3 value2)
{
	value1.X /= value2.X;
	value1.Y /= value2.Y;
	value1.Z /= value2.Z;
	return value1;
}

Vector3 Vector3::Divide(Vector3 value1, float divider)
{
	float factor = 1 / divider;
	value1.X *= factor;
	value1.Y *= factor;
	value1.Z *= factor;
	return value1;
}

void Vector3::Divide(Vector3& value1, float divider, Vector3& result)
{
	float factor = 1 / divider;
	result.X = value1.X * factor;
	result.Y = value1.Y * factor;
	result.Z = value1.Z * factor;
}

void Vector3::Divide(Vector3& value1, Vector3& value2, Vector3& result)
{
	result.X = value1.X / value2.X;
	result.Y = value1.Y / value2.Y;
	result.Z = value1.Z / value2.Z;
}

float Vector3::Dot(Vector3 value1, Vector3 value2)
{
	return value1.X * value2.X + value1.Y * value2.Y + value1.Z * value2.Z;
}

void Vector3::Dot(Vector3& value1, Vector3& value2, float& result)
{
	result = value1.X * value2.X + value1.Y * value2.Y + value1.Z * value2.Z;
}


void Vector3::Floor()
{
	X = std::floor(X);
	Y = std::floor(Y);
	Z = std::floor(Z);
}

Vector3 Vector3::Floor(Vector3 value)
{
	value.X = std::floor(value.X);
	value.Y = std::floor(value.Y);
	value.Z = std::floor(value.Z);
	return value;
}

void Vector3::Floor(Vector3& value, Vector3& result)
{
	result.X = std::floor(value.X);
	result.Y = std::floor(value.Y);
	result.Z = std::floor(value.Z);
}


Vector3 Vector3::Hermite(Vector3 value1, Vector3 tangent1, Vector3 value2, Vector3 tangent2, float amount)
{
	return Vector3(
		MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount),
		MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount),
		MathHelper::Hermite(value1.Z, tangent1.Z, value2.Z, tangent2.Z, amount)
	);
}

void Vector3::Hermite(Vector3& value1, Vector3& tangent1, Vector3& value2, Vector3& tangent2, float amount, Vector3& result)
{
	result.X = MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount);
	result.Y = MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount);
	result.Z = MathHelper::Hermite(value1.Z, tangent1.Z, value2.Z, tangent2.Z, amount);
}

float Vector3::Length(Vector3& vector)
{
	return std::sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z));
}

float Vector3::LengthSquared(Vector3& vector)
{
	return (vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z);
}

Vector3 Vector3::Lerp(Vector3 value1, Vector3 value2, float amount)
{
	return Vector3(
		MathHelper::Lerp(value1.X, value2.X, amount),
		MathHelper::Lerp(value1.Y, value2.Y, amount),
		MathHelper::Lerp(value1.Z, value2.Z, amount)
	);
}

void Vector3::Lerp(Vector3& value1, Vector3& value2, float amount, Vector3& result)
{
	result.X = MathHelper::Lerp(value1.X, value2.X, amount);
	result.Y = MathHelper::Lerp(value1.Y, value2.Y, amount);
	result.Z = MathHelper::Lerp(value1.Z, value2.Z, amount);
}

Vector3 Vector3::LerpPrecise(Vector3 value1, Vector3 value2, float amount)
{
	return Vector3(
		MathHelper::LerpPrecise(value1.X, value2.X, amount),
		MathHelper::LerpPrecise(value1.Y, value2.Y, amount),
		MathHelper::LerpPrecise(value1.Z, value2.Z, amount)
	);
}

void Vector3::LerpPrecise(Vector3& value1, Vector3& value2, float amount, Vector3& result)
{
	result.X = MathHelper::LerpPrecise(value1.X, value2.X, amount);
	result.Y = MathHelper::LerpPrecise(value1.Y, value2.Y, amount);
	result.Z = MathHelper::LerpPrecise(value1.Z, value2.Z, amount);
}

Vector3 Vector3::Max(Vector3 value1, Vector3 value2)
{
	return Vector3(
		MathHelper::Max(value1.X, value2.X),
		MathHelper::Max(value1.Y, value2.Y),
		MathHelper::Max(value1.Z, value2.Z)
	);
}

void Vector3::Max(Vector3& value1, Vector3& value2, Vector3& result)
{
	result.X = MathHelper::Max(value1.X, value2.X);
	result.Y = MathHelper::Max(value1.Y, value2.Y);
	result.Z = MathHelper::Max(value1.Z, value2.Z);
}

Vector3 Vector3::Min(Vector3 value1, Vector3 value2)
{
	return Vector3(
		MathHelper::Min(value1.X, value2.X),
		MathHelper::Min(value1.Y, value2.Y),
		MathHelper::Min(value1.Z, value2.Z)
	);
}

void Vector3::Min(Vector3& value1, Vector3& value2, Vector3& result)
{
	result.X = MathHelper::Min(value1.X, value2.X);
	result.Y = MathHelper::Min(value1.Y, value2.Y);
	result.Z = MathHelper::Min(value1.Z, value2.Z);
}

Vector3 Vector3::Multiply(Vector3 value1, Vector3 value2)
{
	value1.X *= value2.X;
	value1.Y *= value2.Y;
	value1.Z *= value2.Z;
	return value1;
}

Vector3 Vector3::Multiply(Vector3 value1, float scaleFactor)
{
	value1.X *= scaleFactor;
	value1.Y *= scaleFactor;
	value1.Z *= scaleFactor;
	return value1;
}

void Vector3::Multiply(Vector3& value1, float scaleFactor, Vector3& result)
{
	result.X = value1.X * scaleFactor;
	result.Y = value1.Y * scaleFactor;
	result.Z = value1.Z * scaleFactor;
}

void Vector3::Multiply(Vector3& value1, Vector3& value2, Vector3& result)
{
	result.X = value1.X * value2.X;
	result.Y = value1.Y * value2.Y;
	result.Z = value1.Z * value2.Z;
}

Vector3 Vector3::Negate(Vector3 value)
{
	value = Vector3(-value.X, -value.Y, -value.Z);
	return value;
}

void Vector3::Negate(Vector3& value, Vector3& result)
{
	result.X = -value.X;
	result.Y = -value.Y;
	result.Z = -value.Z;
}

void Vector3::Normalize()
{
	float factor = std::sqrt((X * X) + (Y * Y) + (Z * Z));
	factor = 1.0f / factor;
	X *= factor;
	Y *= factor;
	Z *= factor;
}

Vector3 Vector3::Normalize(Vector3 value)
{
	float factor = std::sqrt((value.X * value.X) + (value.Y * value.Y) + (value.Z * value.Z));
	factor = 1.0f / factor;
	return Vector3(value.X * factor, value.Y * factor, value.Z * factor);
}

void Vector3::Normalize(Vector3& value, Vector3& result)
{
	float factor = std::sqrt((value.X * value.X) + (value.Y * value.Y) + (value.Z * value.Z));
	factor = 1.0f / factor;
	result.X = value.X * factor;
	result.Y = value.Y * factor;
	result.Z = value.Z * factor;
}

Vector3 Vector3::Reflect(Vector3 vector, Vector3 normal)
{
	Vector3 reflectedVector;
	float dotProduct = ((vector.X * normal.X) + (vector.Y * normal.Y)) + (vector.Z * normal.Z);
	reflectedVector.X = vector.X - (2.0f * normal.X) * dotProduct;
	reflectedVector.Y = vector.Y - (2.0f * normal.Y) * dotProduct;
	reflectedVector.Z = vector.Z - (2.0f * normal.Z) * dotProduct;
	return reflectedVector;
}

void Vector3::Reflect(Vector3& vector, Vector3& normal, Vector3& result)
{
	float dotProduct = ((vector.X * normal.X) + (vector.Y * normal.Y)) + (vector.Z * normal.Z);
	result.X = vector.X - (2.0f * normal.X) * dotProduct;
	result.Y = vector.Y - (2.0f * normal.Y) * dotProduct;
	result.Z = vector.Z - (2.0f * normal.Z) * dotProduct;
}

void Vector3::Round()
{
	X = std::round(X);
	Y = std::round(Y);
	Z = std::round(Z);
}

Vector3 Vector3::Round(Vector3 value)
{
	value.X = std::round(value.X);
	value.Y = std::round(value.Y);
	value.Z = std::round(value.Z);
	return value;
}

Vector3 Vector3::Round(Vector3 value)
{
	return Vector3(
		std::round(value.X),
		std::round(value.Y),
		std::round(value.Z)
	);
}

void Vector3::Round(Vector3& value, Vector3& result)
{
	result.X = std::round(value.X);
	result.Y = std::round(value.Y);
	result.Z = std::round(value.Z);
}

Vector3 Vector3::SmoothStep(Vector3 value1, Vector3 value2, float amount)
{
	amount = (amount < 0.0f) ? 0.0f : ((amount > 1.0f) ? 1.0f : amount);
	amount = amount * amount * (3.0f - 2.0f * amount);

	return Vector3(
		MathHelper::Lerp(value1.X, value2.X, amount),
		MathHelper::Lerp(value1.Y, value2.Y, amount),
		MathHelper::Lerp(value1.Z, value2.Z, amount)
	);
}

void Vector3::SmoothStep(Vector3& value1, Vector3& value2, float amount, Vector3& result)
{
	amount = (amount < 0.0f) ? 0.0f : ((amount > 1.0f) ? 1.0f : amount);
	amount = amount * amount * (3.0f - 2.0f * amount);

	result.X = MathHelper::Lerp(value1.X, value2.X, amount);
	result.Y = MathHelper::Lerp(value1.Y, value2.Y, amount);
	result.Z = MathHelper::Lerp(value1.Z, value2.Z, amount);
}

Vector3 Vector3::Subtract(Vector3 value1, Vector3 value2)
{
	return Vector3(
		value1.X - value2.X,
		value1.Y - value2.Y,
		value1.Z - value2.Z
	);
}

void Vector3::Subtract(Vector3& value1, Vector3& value2, Vector3& result)
{
	result.X = value1.X - value2.X;
	result.Y = value1.Y - value2.Y;
	result.Z = value1.Z - value2.Z;
}
