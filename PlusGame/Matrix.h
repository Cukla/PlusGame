#pragma once
#include <stdexcept>
#include "Vector3.h"
#include "Vector4.h" 
#include "Quaternion.h"
#include "Rectangle.h"
class Matrix
{
public:
	float M11, M12, M13, M14;
	float M21, M22, M23, M24;
	float M31, M32, M33, M34;
	float M41, M42, M43, M44;

	static const Matrix identity;

	float& operator[](int index) {
		switch (index) {
		case 0: return M11;
		case 1: return M12;
		case 2: return M13;
		case 3: return M14;
		case 4: return M21;
		case 5: return M22;
		case 6: return M23;
		case 7: return M24;
		case 8: return M31;
		case 9: return M32;
		case 10: return M33;
		case 11: return M34;
		case 12: return M41;
		case 13: return M42;
		case 14: return M43;
		case 15: return M44;
		default: throw std::out_of_range("Index  of range");
		}
	}

	float& operator()(int row, int column) {
		return (*this)[(row * 4) + column];
	}

	Matrix(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	);

	// Constructs a matrix.
	Matrix(
		const Vector4& row1,
		const Vector4& row2,
		const Vector4& row3,
		const Vector4& row4
	);

	Matrix() :
		M11(0), M12(0), M13(0), M14(0),
		M21(0), M22(0), M23(0), M24(0),
		M31(0), M32(0), M33(0), M34(0),
		M41(0), M42(0), M43(0), M44(0) {}

public:
	Vector3 Backward() const;
	void Backward(const Vector3& value);
	Vector3 Down() const;
	void Down(const Vector3& value);
	Vector3 Forward() const;
	void Forward(const Vector3& value);
	Vector3 Left() const;
	void Left(const Vector3& value);
	Vector3 Right() const;
	void Right(const Vector3& value);
	Vector3 Translation() const;
	void Translation(const Vector3& value);
	Vector3 Up() const;
	void Up(const Vector3& value);
	static Matrix Identity();

public:
	static Matrix CreateBillboard(Vector3& objectPosition, Vector3& cameraPosition, Vector3& cameraUpVector, Vector3* cameraForwardVector);
	static void CreateBillboard(Vector3& objectPosition, Vector3& cameraPosition, Vector3& cameraUpVector, Vector3* cameraForwardVector, Matrix& result);

	static Matrix CreateConstrainedBillboard(Vector3& objectPosition, Vector3& cameraPosition, Vector3& rotateAxis, Vector3* cameraForwardVector, Vector3* objectForwardVector);
	static void CreateConstrainedBillboard(Vector3& objectPosition, Vector3& cameraPosition, Vector3& rotateAxis, Vector3* cameraForwardVector, Vector3* objectForwardVector, Matrix& result);
	static Matrix CreateFromAxisAngle(Vector3& axis, float angle);
	static void CreateFromAxisAngle(Vector3& axis, float angle, Matrix& result);
	static Matrix CreateFromQuaternion(Quaternion& quaternion);
	static void CreateFromQuaternion(Quaternion& quaternion, Matrix& result);
	static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	static void CreateFromYawPitchRoll(float yaw, float pitch, float roll, Matrix& result);
	static void CreateLookAt(Vector3& cameraPosition, Vector3& cameraTarget, Vector3& cameraUpVector, Matrix& result);
	static Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
	static void CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane, Matrix& result);
	static Matrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);
	static Matrix CreateOrthographicOffCenter(Rectangle& viewingVolume, float zNearPlane, float zFarPlane);
	static void CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane, Matrix& result);
	static Matrix CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
	static void CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance, Matrix& result);
	static Matrix CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
	static void CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance, Matrix& result);
	static Matrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance);
	static Matrix CreatePerspectiveOffCenter(Rectangle& viewingVolume, float nearPlaneDistance, float farPlaneDistance);
	static void CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance, Matrix& result);
	static Matrix CreateRotationX(float radians);
	static void CreateRotationX(float radians, Matrix& result);
	static Matrix CreateRotationY(float radians);
	static void CreateRotationY(float radians, Matrix& result);
	static Matrix CreateRotationZ(float radians);
	static void CreateRotationZ(float radians, Matrix& result);
	static Matrix CreateScale(float scale);
	static void CreateScale(float scale, Matrix& result);
	static Matrix CreateScale(float xScale, float yScale, float zScale);
	static void CreateScale(float xScale, float yScale, float zScale, Matrix& result);
	static Matrix CreateScale(Vector3& scales);
	static Matrix CreateLookAt(Vector3& cameraPosition, Vector3& cameraTarget, Vector3& cameraUpVector);
	//TODO add the functions regarding Plane
	static void CreateScale(Vector3& scales, Matrix& result);
	static Matrix CreateTranslation(float xPosition, float yPosition, float zPosition);
	static void CreateTranslation(Vector3& position, Matrix& result);
	static Matrix CreateTranslation(Vector3& position);
	static void CreateTranslation(float xPosition, float yPosition, float zPosition, Matrix& result);
	static Matrix CreateWorld(Vector3& position, Vector3& forward, Vector3& up);
	static void CreateWorld(Vector3& position, Vector3& forward, Vector3& up, Matrix& result);
	bool Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation);
	float Determinant();
	static Matrix Add(Matrix& matrix1, Matrix& matrix2);
	static void Add(Matrix& matrix1, Matrix& matrix2, Matrix& result);
	static Matrix Divide(Matrix& matrix1, Matrix& matrix2);
	static void Divide(Matrix& matrix1, Matrix& matrix2, Matrix& result);
	static Matrix Divide(Matrix matrix1, float divider);
	static void Divide(Matrix& matrix1, float divider, Matrix& result);
	static Matrix Invert(Matrix& matrix);
	static void Invert(Matrix& matrix, Matrix& result);
	static Matrix Lerp(Matrix& matrix1, Matrix& matrix2, float amount);
	static void Lerp(Matrix& matrix1, Matrix& matrix2, float amount, Matrix& result);
	static Matrix Multiply(Matrix& matrix1, Matrix& matrix2);
	static void Multiply(Matrix& matrix1, Matrix& matrix2, Matrix& result);
	static Matrix Multiply(Matrix& matrix1, float scaleFactor);
	static void Multiply(Matrix& matrix1, float scaleFactor, Matrix& result);
	static float* ToFloatArray(Matrix& matrix);
	static Matrix Negate(Matrix& matrix);
	static void Negate(Matrix& matrix, Matrix& result);
	static Matrix Subtract(Matrix& matrix1, Matrix& matrix2);
	static void Subtract(Matrix& matrix1, Matrix& matrix2, Matrix& result);

	static Matrix Transpose(Matrix& matrix);
	static void Transpose(Matrix& matrix, Matrix& result);

	// Matrix addition
	friend Matrix operator+(const Matrix& matrix1, const Matrix& matrix2);
	// Matrix division by another matrix
	friend Matrix operator/(const Matrix& matrix1, const Matrix& matrix2);
	// Matrix division by a scalar
	friend Matrix operator/(const Matrix& matrix, float divider);
	// Matrix equality comparison
	friend bool operator==(const Matrix& matrix1, const Matrix& matrix2);
	// Matrix inequality comparison
	friend bool operator!=(const Matrix& matrix1, const Matrix& matrix2);
	// Matrix multiplication
	friend Matrix operator*(const Matrix& matrix1, const Matrix& matrix2);
	// Matrix multiplication by a scalar
	friend Matrix operator*(const Matrix& matrix, float scaleFactor);
	// Matrix subtraction
	friend Matrix operator-(const Matrix& matrix1, const Matrix& matrix2);
	// Matrix negation
	friend Matrix operator-(const Matrix& matrix);

private:

	static void FindDeterminants(Matrix& matrix, float& major, float& minor1, float& minor2, float& minor3, float& minor4, float& minor5, float& minor6,
		float& minor7, float& minor8, float& minor9, float& minor10, float& minor11, float& minor12);
};