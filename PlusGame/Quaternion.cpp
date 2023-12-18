#include "Quaternion.h"

const Quaternion Quaternion::Identity(0, 0, 0, 1);
Quaternion& Quaternion::operator=(const Quaternion& other)
{
	if (this != &other)
	{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		W = other.W;
	}
	return *this;
}

Quaternion Quaternion::Add(const Quaternion& quaternion1, const Quaternion& quaternion2)
{
	return Quaternion(quaternion1.X + quaternion2.X, quaternion1.Y + quaternion2.Y, quaternion1.Z + quaternion2.Z, quaternion1.W + quaternion2.W);
}

void Quaternion::Add(const Quaternion& quaternion1, const Quaternion& quaternion2, Quaternion& result)
{
	result.X = quaternion1.X + quaternion2.X;
	result.Y = quaternion1.Y + quaternion2.Y;
	result.Z = quaternion1.Z + quaternion2.Z;
	result.W = quaternion1.W + quaternion2.W;
}

Quaternion Quaternion::Concatenate(const Quaternion& value1, const Quaternion& value2)
{
	Quaternion quaternion;

	float x1 = value1.X;
	float y1 = value1.Y;
	float z1 = value1.Z;
	float w1 = value1.W;

	float x2 = value2.X;
	float y2 = value2.Y;
	float z2 = value2.Z;
	float w2 = value2.W;

	quaternion.X = ((x2 * w1) + (x1 * w2)) + ((y2 * z1) - (z2 * y1));
	quaternion.Y = ((y2 * w1) + (y1 * w2)) + ((z2 * x1) - (x2 * z1));
	quaternion.Z = ((z2 * w1) + (z1 * w2)) + ((x2 * y1) - (y2 * x1));
	quaternion.W = (w2 * w1) - (((x2 * x1) + (y2 * y1)) + (z2 * z1));

	return quaternion;
}

void Quaternion::Concatenate(const Quaternion& value1, const Quaternion& value2, Quaternion& result)
{
	float x1 = value1.X;
	float y1 = value1.Y;
	float z1 = value1.Z;
	float w1 = value1.W;

	float x2 = value2.X;
	float y2 = value2.Y;
	float z2 = value2.Z;
	float w2 = value2.W;

	result.X = ((x2 * w1) + (x1 * w2)) + ((y2 * z1) - (z2 * y1));
	result.Y = ((y2 * w1) + (y1 * w2)) + ((z2 * x1) - (x2 * z1));
	result.Z = ((z2 * w1) + (z1 * w2)) + ((x2 * y1) - (y2 * x1));
	result.W = (w2 * w1) - (((x2 * x1) + (y2 * y1)) + (z2 * z1));
}

void Quaternion::Conjugate()
{
	X = -X;
	Y = -Y;
	Z = -Z;
}

void Quaternion::Conjugate(Quaternion& value)
{
	value.X = -value.X, value.Y = -value.Y, value.Z = -value.Z;
}

void Quaternion::Conjugate(const Quaternion& value, Quaternion& result)
{
	result.X = -value.X;
	result.Y = -value.Y;
	result.Z = -value.Z;
	result.W = value.W;
}

Quaternion Quaternion::CreateFromAxisAngle(const Vector3& axis, float angle)
{
	float half = angle * 0.5f;
	float sinHalf = sin(half);
	float cosHalf = cos(half);

	return Quaternion(axis.X * sinHalf, axis.Y * sinHalf, axis.Z * sinHalf, cosHalf);
}

void Quaternion::CreateFromAxisAngle(const Vector3& axis, float angle, Quaternion& result)
{
	float half = angle * 0.5f;
	float sinHalf = sin(half);
	float cosHalf = cos(half);

	result.X = axis.X * sinHalf;
	result.Y = axis.Y * sinHalf;
	result.Z = axis.Z * sinHalf;
	result.W = cosHalf;
}

Quaternion Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	float halfRoll = roll * 0.5f;
	float halfPitch = pitch * 0.5f;
	float halfYaw = yaw * 0.5f;

	float sinRoll = sin(halfRoll);
	float cosRoll = cos(halfRoll);
	float sinPitch = sin(halfPitch);
	float cosPitch = cos(halfPitch);
	float sinYaw = sin(halfYaw);
	float cosYaw = cos(halfYaw);

	return Quaternion((cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll),
		(sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll),
		(cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll),
		(cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll));
}

void Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll, Quaternion& result)
{
	float halfRoll = roll * 0.5f;
	float halfPitch = pitch * 0.5f;
	float halfYaw = yaw * 0.5f;

	float sinRoll = sin(halfRoll);
	float cosRoll = cos(halfRoll);
	float sinPitch = sin(halfPitch);
	float cosPitch = cos(halfPitch);
	float sinYaw = sin(halfYaw);
	float cosYaw = cos(halfYaw);

	result.X = (cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll);
	result.Y = (sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll);
	result.Z = (cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll);
	result.W = (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll);
}

Quaternion Quaternion::Divide(Quaternion& quaternion1, Quaternion& quaternion2)
{
	Quaternion quaternion;
	float x = quaternion1.X;
	float y = quaternion1.Y;
	float z = quaternion1.Z;
	float w = quaternion1.W;
	float num14 = (((quaternion2.X * quaternion2.X) + (quaternion2.Y * quaternion2.Y)) + (quaternion2.Z * quaternion2.Z)) + (quaternion2.W * quaternion2.W);
	float num5 = 1.0f / num14;
	float num4 = -quaternion2.X * num5;
	float num3 = -quaternion2.Y * num5;
	float num2 = -quaternion2.Z * num5;
	float num = quaternion2.W * num5;
	float num13 = (y * num2) - (z * num3);
	float num12 = (z * num4) - (x * num2);
	float num11 = (x * num3) - (y * num4);
	float num10 = ((x * num4) + (y * num3)) + (z * num2);
	quaternion.X = ((x * num) + (num4 * w)) + num13;
	quaternion.Y = ((y * num) + (num3 * w)) + num12;
	quaternion.Z = ((z * num) + (num2 * w)) + num11;
	quaternion.W = (w * num) - num10;
	return quaternion;
}

void Quaternion::Divide(Quaternion& quaternion1, Quaternion& quaternion2, Quaternion& result)
{
	float x = quaternion1.X;
	float y = quaternion1.Y;
	float z = quaternion1.Z;
	float w = quaternion1.W;
	float num14 = (((quaternion2.X * quaternion2.X) + (quaternion2.Y * quaternion2.Y)) + (quaternion2.Z * quaternion2.Z)) + (quaternion2.W * quaternion2.W);
	float num5 = 1.0f / num14;
	float num4 = -quaternion2.X * num5;
	float num3 = -quaternion2.Y * num5;
	float num2 = -quaternion2.Z * num5;
	float num = quaternion2.W * num5;
	float num13 = (y * num2) - (z * num3);
	float num12 = (z * num4) - (x * num2);
	float num11 = (x * num3) - (y * num4);
	float num10 = ((x * num4) + (y * num3)) + (z * num2);
	result.X = ((x * num) + (num4 * w)) + num13;
	result.Y = ((y * num) + (num3 * w)) + num12;
	result.Z = ((z * num) + (num2 * w)) + num11;
	result.W = (w * num) - num10;
}

float Quaternion::Dot(Quaternion& quaternion1, Quaternion& quaternion2)
{
	return ((((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W));
}

void Quaternion::Dot(Quaternion& quaternion1, Quaternion& quaternion2, float& result)
{
	result = (((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W);
}

float Quaternion::Length()
{
	return sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
}

float Quaternion::LengthSquared()
{
	return (X * X) + (Y * Y) + (Z * Z) + (W * W);
}

Quaternion  Quaternion::Lerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount)
{
	float num = amount;
	float num2 = 1.0f - num;
	Quaternion quaternion = Quaternion();
	float num5 = (((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W);
	if (num5 >= 0.0f)
	{
		quaternion.X = (num2 * quaternion1.X) + (num * quaternion2.X);
		quaternion.Y = (num2 * quaternion1.Y) + (num * quaternion2.Y);
		quaternion.Z = (num2 * quaternion1.Z) + (num * quaternion2.Z);
		quaternion.W = (num2 * quaternion1.W) + (num * quaternion2.W);
	}
	else
	{
		quaternion.X = (num2 * quaternion1.X) - (num * quaternion2.X);
		quaternion.Y = (num2 * quaternion1.Y) - (num * quaternion2.Y);
		quaternion.Z = (num2 * quaternion1.Z) - (num * quaternion2.Z);
		quaternion.W = (num2 * quaternion1.W) - (num * quaternion2.W);
	}
	float num4 = (((quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y)) + (quaternion.Z * quaternion.Z)) + (quaternion.W * quaternion.W);
	float num3 = 1.0f / sqrt(num4);
	quaternion.X *= num3;
	quaternion.Y *= num3;
	quaternion.Z *= num3;
	quaternion.W *= num3;
	return quaternion;
}

void  Quaternion::Lerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount, Quaternion& result)
{
	float num = amount;
	float num2 = 1.0f - num;
	float num5 = (((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W);
	if (num5 >= 0.0f)
	{
		result.X = (num2 * quaternion1.X) + (num * quaternion2.X);
		result.Y = (num2 * quaternion1.Y) + (num * quaternion2.Y);
		result.Z = (num2 * quaternion1.Z) + (num * quaternion2.Z);
		result.W = (num2 * quaternion1.W) + (num * quaternion2.W);
	}
	else
	{
		result.X = (num2 * quaternion1.X) - (num * quaternion2.X);
		result.Y = (num2 * quaternion1.Y) - (num * quaternion2.Y);
		result.Z = (num2 * quaternion1.Z) - (num * quaternion2.Z);
		result.W = (num2 * quaternion1.W) - (num * quaternion2.W);
	}
	float num4 = (((result.X * result.X) + (result.Y * result.Y)) + (result.Z * result.Z)) + (result.W * result.W);
	float num3 = 1.0f / sqrt(num4);
	result.X *= num3;
	result.Y *= num3;
	result.Z *= num3;
	result.W *= num3;
}

Quaternion Quaternion::Slerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount)
{
	float num2;
	float num3;
	Quaternion quaternion;
	float num = amount;
	float num4 = (((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W);
	bool flag = false;
	if (num4 < 0.0f)
	{
		flag = true;
		num4 = -num4;
	}
	if (num4 > 0.999999f)
	{
		num3 = 1.0f - num;
		num2 = flag ? -num : num;
	}
	else
	{
		float num5 = acos(num4);
		float num6 = (float)(1.0 / sin((double)num5));
		num3 = sin((1.0f - num) * num5) * num6;
		num2 = flag ? (-sin(num * num5) * num6) : (sin(num * num5) * num6);
	}
	quaternion.X = (num3 * quaternion1.X) + (num2 * quaternion2.X);
	quaternion.Y = (num3 * quaternion1.Y) + (num2 * quaternion2.Y);
	quaternion.Z = (num3 * quaternion1.Z) + (num2 * quaternion2.Z);
	quaternion.W = (num3 * quaternion1.W) + (num2 * quaternion2.W);
	return quaternion;
}

void Quaternion::Slerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount, Quaternion& result)
{
	float num2;
	float num3;
	float num = amount;
	float num4 = (((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W);
	bool flag = false;
	if (num4 < 0.0f)
	{
		flag = true;
		num4 = -num4;
	}
	if (num4 > 0.999999f)
	{
		num3 = 1.0f - num;
		num2 = flag ? -num : num;
	}
	else
	{
		float num5 = acos(num4);
		float num6 = (float)(1.0 / sin((double)num5));
		num3 = sin((1.0f - num) * num5) * num6;
		num2 = flag ? (-sin(num * num5) * num6) : (sin(num * num5) * num6);
	}
	result.X = (num3 * quaternion1.X) + (num2 * quaternion2.X);
	result.Y = (num3 * quaternion1.Y) + (num2 * quaternion2.Y);
	result.Z = (num3 * quaternion1.Z) + (num2 * quaternion2.Z);
	result.W = (num3 * quaternion1.W) + (num2 * quaternion2.W);
}

Quaternion Quaternion::Subtract(Quaternion& quaternion1, Quaternion& quaternion2)
{
	Quaternion quaternion;
	quaternion.X = quaternion1.X - quaternion2.X;
	quaternion.Y = quaternion1.Y - quaternion2.Y;
	quaternion.Z = quaternion1.Z - quaternion2.Z;
	quaternion.W = quaternion1.W - quaternion2.W;
	return quaternion;
}

void Quaternion::Subtract(Quaternion& quaternion1, Quaternion& quaternion2, Quaternion& result)
{
	result.X = quaternion1.X - quaternion2.X;
	result.Y = quaternion1.Y - quaternion2.Y;
	result.Z = quaternion1.Z - quaternion2.Z;
	result.W = quaternion1.W - quaternion2.W;
}

Quaternion Quaternion::Multiply(Quaternion& quaternion1, Quaternion& quaternion2)
{
	Quaternion quaternion;
	float x = quaternion1.X;
	float y = quaternion1.Y;
	float z = quaternion1.Z;
	float w = quaternion1.W;
	float num4 = quaternion2.X;
	float num3 = quaternion2.Y;
	float num2 = quaternion2.Z;
	float num = quaternion2.W;
	float num12 = (y * num2) - (z * num3);
	float num11 = (z * num4) - (x * num2);
	float num10 = (x * num3) - (y * num4);
	float num9 = ((x * num4) + (y * num3)) + (z * num2);
	quaternion.X = ((x * num) + (num4 * w)) + num12;
	quaternion.Y = ((y * num) + (num3 * w)) + num11;
	quaternion.Z = ((z * num) + (num2 * w)) + num10;
	quaternion.W = (w * num) - num9;
	return quaternion;
}

Quaternion Quaternion::Multiply(Quaternion& quaternion1, float scaleFactor)
{
	Quaternion quaternion;
	quaternion.X = quaternion1.X * scaleFactor;
	quaternion.Y = quaternion1.Y * scaleFactor;
	quaternion.Z = quaternion1.Z * scaleFactor;
	quaternion.W = quaternion1.W * scaleFactor;
	return quaternion;
}

void Quaternion::Multiply(Quaternion& quaternion1, float scaleFactor, Quaternion& result)
{
	result.X = quaternion1.X * scaleFactor;
	result.Y = quaternion1.Y * scaleFactor;
	result.Z = quaternion1.Z * scaleFactor;
	result.W = quaternion1.W * scaleFactor;
}

void Quaternion::Multiply(Quaternion& quaternion1, Quaternion& quaternion2, Quaternion& result)
{
	float x = quaternion1.X;
	float y = quaternion1.Y;
	float z = quaternion1.Z;
	float w = quaternion1.W;
	float num4 = quaternion2.X;
	float num3 = quaternion2.Y;
	float num2 = quaternion2.Z;
	float num = quaternion2.W;
	float num12 = (y * num2) - (z * num3);
	float num11 = (z * num4) - (x * num2);
	float num10 = (x * num3) - (y * num4);
	float num9 = ((x * num4) + (y * num3)) + (z * num2);
	result.X = ((x * num) + (num4 * w)) + num12;
	result.Y = ((y * num) + (num3 * w)) + num11;
	result.Z = ((z * num) + (num2 * w)) + num10;
	result.W = (w * num) - num9;
}

void Quaternion::Negate(Quaternion& quaternion)
{
	quaternion.X = -quaternion.X;
	quaternion.Y = -quaternion.Y;
	quaternion.Z = -quaternion.Z;
	quaternion.W = -quaternion.W;
}

void Quaternion::Negate() {
	X = -X;
	Y = -Y;
	Z = -Z;
	W = -W;
}

void Quaternion::Normalize()
{
	float num = 1.0f / sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
	X *= num;
	Y *= num;
	Z *= num;
	W *= num;
}

Quaternion Quaternion::CreateFromRotationMatrix(Matrix& matrix)
{
	Quaternion quaternion;
	float sqrtv;
	float half;
	float scale = matrix.M11 + matrix.M22 + matrix.M33;

	if (scale > 0.0f)
	{
		sqrtv = sqrt(scale + 1.0f);
		quaternion.W = sqrtv * 0.5f;
		sqrtv = 0.5f / sqrtv;

		quaternion.X = (matrix.M23 - matrix.M32) * sqrtv;
		quaternion.Y = (matrix.M31 - matrix.M13) * sqrtv;
		quaternion.Z = (matrix.M12 - matrix.M21) * sqrtv;

		return quaternion;
	}
	if ((matrix.M11 >= matrix.M22) && (matrix.M11 >= matrix.M33))
	{
		sqrtv = sqrt(1.0f + matrix.M11 - matrix.M22 - matrix.M33);
		half = 0.5f / sqrtv;

		quaternion.X = 0.5f * sqrtv;
		quaternion.Y = (matrix.M12 + matrix.M21) * half;
		quaternion.Z = (matrix.M13 + matrix.M31) * half;
		quaternion.W = (matrix.M23 - matrix.M32) * half;

		return quaternion;
	}
	if (matrix.M22 > matrix.M33)
	{
		sqrtv = sqrt(1.0f + matrix.M22 - matrix.M11 - matrix.M33);
		half = 0.5f / sqrtv;

		quaternion.X = (matrix.M21 + matrix.M12) * half;
		quaternion.Y = 0.5f * sqrtv;
		quaternion.Z = (matrix.M32 + matrix.M23) * half;
		quaternion.W = (matrix.M31 - matrix.M13) * half;

		return quaternion;
	}
	sqrtv = sqrt(1.0f + matrix.M33 - matrix.M11 - matrix.M22);
	half = 0.5f / sqrtv;

	quaternion.X = (matrix.M31 + matrix.M13) * half;
	quaternion.Y = (matrix.M32 + matrix.M23) * half;
	quaternion.Z = 0.5f * sqrtv;
	quaternion.W = (matrix.M12 - matrix.M21) * half;

	return quaternion;
}

void Quaternion::CreateFromRotationMatrix(Matrix& matrix, Quaternion& result)
{
	float sqrtv;
	float half;
	float scale = matrix.M11 + matrix.M22 + matrix.M33;

	if (scale > 0.0f)
	{
		sqrtv = sqrt(scale + 1.0f);
		result.W = sqrtv * 0.5f;
		sqrtv = 0.5f / sqrtv;

		result.X = (matrix.M23 - matrix.M32) * sqrtv;
		result.Y = (matrix.M31 - matrix.M13) * sqrtv;
		result.Z = (matrix.M12 - matrix.M21) * sqrtv;
	}
	else
		if ((matrix.M11 >= matrix.M22) && (matrix.M11 >= matrix.M33))
		{
			sqrtv = sqrt(1.0f + matrix.M11 - matrix.M22 - matrix.M33);
			half = 0.5f / sqrtv;

			result.X = 0.5f * sqrtv;
			result.Y = (matrix.M12 + matrix.M21) * half;
			result.Z = (matrix.M13 + matrix.M31) * half;
			result.W = (matrix.M23 - matrix.M32) * half;
		}
		else if (matrix.M22 > matrix.M33)
		{
			sqrtv = sqrt(1.0f + matrix.M22 - matrix.M11 - matrix.M33);
			half = 0.5f / sqrtv;

			result.X = (matrix.M21 + matrix.M12) * half;
			result.Y = 0.5f * sqrtv;
			result.Z = (matrix.M32 + matrix.M23) * half;
			result.W = (matrix.M31 - matrix.M13) * half;
		}
		else
		{
			sqrtv = sqrt(1.0f + matrix.M33 - matrix.M11 - matrix.M22);
			half = 0.5f / sqrtv;

			result.X = (matrix.M31 + matrix.M13) * half;
			result.Y = (matrix.M32 + matrix.M23) * half;
			result.Z = 0.5f * sqrtv;
			result.W = (matrix.M12 - matrix.M21) * half;
		}
}
Quaternion Quaternion::operator+(const Quaternion& quaternion) const
{
	Quaternion result;
	result.X = X + quaternion.X;
	result.Y = Y + quaternion.Y;
	result.Z = Z + quaternion.Z;
	result.W = W + quaternion.W;
	return result;
}

Quaternion Quaternion::operator/(const Quaternion& quaternion) const
{
	Quaternion result;
	float x = X;
	float y = Y;
	float z = Z;
	float w = W;
	float num14 = (((quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y)) + (quaternion.Z * quaternion.Z)) + (quaternion.W * quaternion.W);
	float num5 = 1.0f / num14;
	float num4 = -quaternion.X * num5;
	float num3 = -quaternion.Y * num5;
	float num2 = -quaternion.Z * num5;
	float num1 = quaternion.W * num5;
	float num13 = (y * num2) - (z * num3);
	float num12 = (z * num4) - (x * num2);
	float num11 = (x * num3) - (y * num4);
	float num10 = ((x * num4) + (y * num3)) + (z * num2);
	result.X = ((x * num1) + (num4 * w)) + num13;
	result.Y = ((y * num1) + (num3 * w)) + num12;
	result.Z = ((z * num1) + (num2 * w)) + num11;
	result.W = (w * num1) - num10;
	return result;
}

bool Quaternion::operator==(const Quaternion& quaternion) const
{
	return X == quaternion.X && Y == quaternion.Y && Z == quaternion.Z && W == quaternion.W;
}

bool Quaternion::operator!=(const Quaternion& quaternion) const
{
	return !(*this == quaternion);
}

Quaternion Quaternion::operator*(const Quaternion& quaternion) const
{
	Quaternion result;
	float x = X;
	float y = Y;
	float z = Z;
	float w = W;
	float num4 = quaternion.X;
	float num3 = quaternion.Y;
	float num2 = quaternion.Z;
	float num1 = quaternion.W;
	float num12 = (y * num2) - (z * num3);
	float num11 = (z * num4) - (x * num2);
	float num10 = (x * num3) - (y * num4);
	float num9 = ((x * num4) + (y * num3)) + (z * num2);
	result.X = ((x * num1) + (num4 * w)) + num12;
	result.Y = ((y * num1) + (num3 * w)) + num11;
	result.Z = ((z * num1) + (num2 * w)) + num10;
	result.W = (w * num1) - num9;
	return result;
}

Quaternion Quaternion::operator*(float scaleFactor) const
{
	Quaternion result;
	result.X = X * scaleFactor;
	result.Y = Y * scaleFactor;
	result.Z = Z * scaleFactor;
	result.W = W * scaleFactor;
	return result;
}

Quaternion Quaternion::operator-(const Quaternion& quaternion) const
{
	Quaternion result;
	result.X = X - quaternion.X;
	result.Y = Y - quaternion.Y;
	result.Z = Z - quaternion.Z;
	result.W = W - quaternion.W;
	return result;
}

Quaternion Quaternion::operator-() const
{
	Quaternion result;
	result.X = -X;
	result.Y = -Y;
	result.Z = -Z;
	result.W = -W;
	return result;
}