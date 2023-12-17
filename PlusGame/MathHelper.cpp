#include "MathHelper.h" 

const float MathHelper::E = std::exp(1.0f);
const float MathHelper::Log10E = 0.4342945f;
const float MathHelper::Log2E = 1.442695f;
const float MathHelper::Pi = 3.14159274f;
const float MathHelper::PiOver2 = MathHelper::Pi / 2.0f;
const float MathHelper::PiOver4 = MathHelper::Pi / 4.0f;
const float MathHelper::TwoPi = MathHelper::Pi * 2.0f;
const float MathHelper::Tau = MathHelper::TwoPi;

float MathHelper::Barycentric(float value1, float value2, float value3, float amount1, float amount2) {
	return value1 + (value2 - value1) * amount1 + (value3 - value1) * amount2;
}

float MathHelper::CatmullRom(float value1, float value2, float value3, float value4, float amount) {
	double amountSquared = amount * amount;
	double amountCubed = amountSquared * amount;
	return static_cast<float>(0.5 * (2.0 * value2 +
		(value3 - value1) * amount +
		(2.0 * value1 - 5.0 * value2 + 4.0 * value3 - value4) * amountSquared +
		(3.0 * value2 - value1 - 3.0 * value3 + value4) * amountCubed));
}

float MathHelper::Clamp(float value, float min, float max) {
	value = (value > max) ? max : value;
	value = (value < min) ? min : value;
	return value;
}

int MathHelper::Clamp(int value, int min, int max) {
	value = (value > max) ? max : value;
	value = (value < min) ? min : value;
	return value;
}

float MathHelper::Distance(float value1, float value2) {
	return std::abs(value1 - value2);
}

float MathHelper::Hermite(float value1, float tangent1, float value2, float tangent2, float amount) {
	double v1 = value1, v2 = value2, t1 = tangent1, t2 = tangent2, s = amount, result;
	double sCubed = s * s * s;
	double sSquared = s * s;

	if (amount == 0.0f)
		result = value1;
	else if (amount == 1.0f)
		result = value2;
	else
		result = (2 * v1 - 2 * v2 + t2 + t1) * sCubed +
		(3 * v2 - 3 * v1 - 2 * t1 - t2) * sSquared +
		t1 * s +
		v1;
	return static_cast<float>(result);
}

float MathHelper::Lerp(float value1, float value2, float amount) {
	return value1 + (value2 - value1) * amount;
}

float MathHelper::LerpPrecise(float value1, float value2, float amount) {
	return ((1 - amount) * value1) + (value2 * amount);
}

float MathHelper::Max(float value1, float value2) {
	return (value1 > value2) ? value1 : value2;
}

int MathHelper::Max(int value1, int value2) {
	return (value1 > value2) ? value1 : value2;
}

float MathHelper::Min(float value1, float value2) {
	return (value1 < value2) ? value1 : value2;
}

int MathHelper::Min(int value1, int value2) {
	return (value1 < value2) ? value1 : value2;
}

float MathHelper::SmoothStep(float value1, float value2, float amount) {
	float result = Clamp(amount, 0.0f, 1.0f);
	result = Hermite(value1, 0.0f, value2, 0.0f, result);
	return result;
}

float MathHelper::ToDegrees(float radians) {
	return static_cast<float>(radians * 57.295779513082320876798154814105);
}

float MathHelper::ToRadians(float degrees) {
	return static_cast<float>(degrees * 0.017453292519943295769236907684886);
}

float MathHelper::WrapAngle(float angle) {
	if ((angle > -Pi) && (angle <= Pi))
		return angle;
	angle = std::fmod(angle, TwoPi);
	if (angle <= -Pi)
		return angle + TwoPi;
	if (angle > Pi)
		return angle - TwoPi;
	return angle;
}

bool MathHelper::IsPowerOfTwo(int value) {
	return (value > 0) && ((value & (value - 1)) == 0);
}

