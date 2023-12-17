#pragma once 
#include <cmath>

class MathHelper {
public:
	static const float E;
	static const float Log10E;
	static const float Log2E;
	static const float Pi;
	static const float PiOver2;
	static const float PiOver4;
	static const float TwoPi;
	static const float Tau;

	static float Barycentric(float value1, float value2, float value3, float amount1, float amount2);
	static float CatmullRom(float value1, float value2, float value3, float value4, float amount);
	static float Clamp(float value, float min, float max);
	static int Clamp(int value, int min, int max);
	static float Distance(float value1, float value2);
	static float Hermite(float value1, float tangent1, float value2, float tangent2, float amount);
	static float Lerp(float value1, float value2, float amount);
	static float LerpPrecise(float value1, float value2, float amount);
	static float Max(float value1, float value2);
	static int Max(int value1, int value2);
	static float Min(float value1, float value2);
	static int Min(int value1, int value2);
	static float SmoothStep(float value1, float value2, float amount);
	static float ToDegrees(float radians);
	static float ToRadians(float degrees);
	static float WrapAngle(float angle);
	static bool IsPowerOfTwo(int value);
};



