#include "Matrix.h"	

const Matrix Matrix::identity(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);
Matrix::Matrix(
	float m11, float m12, float m13, float m14,
	float m21, float m22, float m23, float m24,
	float m31, float m32, float m33, float m34,
	float m41, float m42, float m43, float m44
) :
	M11(m11), M12(m12), M13(m13), M14(m14),
	M21(m21), M22(m22), M23(m23), M24(m24),
	M31(m31), M32(m32), M33(m33), M34(m34),
	M41(m41), M42(m42), M43(m43), M44(m44)
{

}

// Constructs a matrix.
Matrix::Matrix(
	const Vector4& row1,
	const Vector4& row2,
	const Vector4& row3,
	const Vector4& row4
) :
	M11(row1.X), M12(row1.Y), M13(row1.Z), M14(row1.W),
	M21(row2.X), M22(row2.Y), M23(row2.Z), M24(row2.W),
	M31(row3.X), M32(row3.Y), M33(row3.Z), M34(row3.W),
	M41(row4.X), M42(row4.Y), M43(row4.Z), M44(row4.W)
{
}

// The backward vector formed from the third row M31, M32, M33 elements.
Vector3 Matrix::Backward() const {
	return Vector3(M31, M32, M33);
}

void Matrix::Backward(const Vector3& value) {
	M31 = value.X;
	M32 = value.Y;
	M33 = value.Z;
}

// The down vector formed from the second row -M21, -M22, -M23 elements.
Vector3 Matrix::Down() const {
	return Vector3(-M21, -M22, -M23);
}

void Matrix::Down(const Vector3& value) {
	M21 = -value.X;
	M22 = -value.Y;
	M23 = -value.Z;
}

// The forward vector formed from the third row -M31, -M32, -M33 elements.
Vector3 Matrix::Forward() const {
	return Vector3(-M31, -M32, -M33);
}

void Matrix::Forward(const Vector3& value) {
	M31 = -value.X;
	M32 = -value.Y;
	M33 = -value.Z;
}

// The left vector formed from the first row -M11, -M12, -M13 elements.
Vector3 Matrix::Left() const {
	return Vector3(-M11, -M12, -M13);
}

void Matrix::Left(const Vector3& value) {
	M11 = -value.X;
	M12 = -value.Y;
	M13 = -value.Z;
}

// The right vector formed from the first row M11, M12, M13 elements.
Vector3 Matrix::Right() const {
	return Vector3(M11, M12, M13);
}

void Matrix::Right(const Vector3& value) {
	M11 = value.X;
	M12 = value.Y;
	M13 = value.Z;
}

// Position stored in this matrix.
Vector3 Matrix::Translation() const {
	return Vector3(M41, M42, M43);
}

void Matrix::Translation(const Vector3& value) {
	M41 = value.X;
	M42 = value.Y;
	M43 = value.Z;
}

// The upper vector formed from the second row M21, M22, M23 elements.
Vector3 Matrix::Up() const {
	return Vector3(M21, M22, M23);
}

void Matrix::Up(const Vector3& value) {
	M21 = value.X;
	M22 = value.Y;
	M23 = value.Z;
}

Matrix Matrix::Identity() {
	return identity;
}

/// <summary>
/// Creates a new <see cref="Matrix"/> for spherical billboarding that rotates around specified object position.
/// </summary>
/// <param name="objectPosition">Position of billboard object. It will rotate around that vector.</param>
/// <param name="cameraPosition">The camera position.</param>
/// <param name="cameraUpVector">The camera up vector.</param>
/// <param name="cameraForwardVector">Optional camera forward vector.</param>
/// <returns>The <see cref="Matrix"/> for spherical billboarding.</returns>
Matrix Matrix::CreateBillboard(Vector3& objectPosition, Vector3& cameraPosition,
	Vector3& cameraUpVector, Vector3* cameraForwardVector)
{
	Matrix result;

	// Delegate to the other overload of the function to do the work
	CreateBillboard(objectPosition, cameraPosition, cameraUpVector, cameraForwardVector, result);

	return result;
}

/// <summary>
/// Creates a new <see cref="Matrix"/> for spherical billboarding that rotates around specified object position.
/// </summary>
/// <param name="objectPosition">Position of billboard object. It will rotate around that vector.</param>
/// <param name="cameraPosition">The camera position.</param>
/// <param name="cameraUpVector">The camera up vector.</param>
/// <param name="cameraForwardVector">Optional camera forward vector.</param>
/// <param name="result">The <see cref="Matrix"/> for spherical billboarding as an output parameter.</param>
void Matrix::CreateBillboard(Vector3& objectPosition, Vector3& cameraPosition, Vector3& cameraUpVector, Vector3* cameraForwardVector, Matrix& result)
{
	Vector3 vector;
	Vector3 vector2;
	Vector3 vector3;
	vector.X = objectPosition.X - cameraPosition.X;
	vector.Y = objectPosition.Y - cameraPosition.Y;
	vector.Z = objectPosition.Z - cameraPosition.Z;
	float num = vector.LengthSquared();
	if (num < 0.0001f)
	{
		vector = (cameraForwardVector != nullptr) ? Vector3::Negate(*cameraForwardVector) : Vector3::Forward;
	}
	else
	{
		Vector3::Multiply(vector, 1.0f / sqrt(num), vector);
	}
	Vector3::Cross(cameraUpVector, vector, vector3);
	vector3.Normalize();
	Vector3::Cross(vector, vector3, vector2);
	result.M11 = vector3.X;
	result.M12 = vector3.Y;
	result.M13 = vector3.Z;
	result.M14 = 0;
	result.M21 = vector2.X;
	result.M22 = vector2.Y;
	result.M23 = vector2.Z;
	result.M24 = 0;
	result.M31 = vector.X;
	result.M32 = vector.Y;
	result.M33 = vector.Z;
	result.M34 = 0;
	result.M41 = objectPosition.X;
	result.M42 = objectPosition.Y;
	result.M43 = objectPosition.Z;
	result.M44 = 1;
}

/// <summary>
	   /// Creates a new <see cref="Matrix"/> for cylindrical billboarding that rotates around specified axis.
	   /// </summary>
	   /// <param name="objectPosition">Object position the billboard will rotate around.</param>
	   /// <param name="cameraPosition">Camera position.</param>
	   /// <param name="rotateAxis">Axis of billboard for rotation.</param>
	   /// <param name="cameraForwardVector">Optional camera forward vector.</param>
	   /// <param name="objectForwardVector">Optional object forward vector.</param>
	   /// <returns>The <see cref="Matrix"/> for cylindrical billboarding.</returns>
Matrix Matrix::CreateConstrainedBillboard(Vector3& objectPosition, Vector3& cameraPosition,
	Vector3& rotateAxis, Vector3* cameraForwardVector, Vector3* objectForwardVector)
{
	Matrix result;
	CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis,
		cameraForwardVector, objectForwardVector, result);
	return result;
}

/// <summary>
	 /// Creates a new <see cref="Matrix"/> for cylindrical billboarding that rotates around specified axis.
	 /// </summary>
	 /// <param name="objectPosition">Object position the billboard will rotate around.</param>
	 /// <param name="cameraPosition">Camera position.</param>
	 /// <param name="rotateAxis">Axis of billboard for rotation.</param>
	 /// <param name="cameraForwardVector">Optional camera forward vector.</param>
	 /// <param name="objectForwardVector">Optional object forward vector.</param>
	 /// <param name="result">The <see cref="Matrix"/> for cylindrical billboarding as an output parameter.</param>
void  Matrix::CreateConstrainedBillboard(Vector3& objectPosition, Vector3& cameraPosition,
	Vector3& rotateAxis, Vector3* cameraForwardVector, Vector3* objectForwardVector, Matrix& result)
{
	float num;
	Vector3 vector;
	Vector3 vector2;
	Vector3 vector3;
	vector2.X = objectPosition.X - cameraPosition.X;
	vector2.Y = objectPosition.Y - cameraPosition.Y;
	vector2.Z = objectPosition.Z - cameraPosition.Z;
	float num2 = vector2.LengthSquared();
	if (num2 < 0.0001f)
	{
		vector2 = (cameraForwardVector != nullptr) ? Vector3::Negate(*cameraForwardVector) : Vector3::Forward;
	}
	else
	{
		Vector3::Multiply(vector2, 1.0f / sqrt(num2), vector2);
	}
	Vector3 vector4 = rotateAxis;
	Vector3::Dot(rotateAxis, vector2, num);
	if (abs(num) > 0.9982547f)
	{
		if (objectForwardVector != nullptr)
		{
			vector = *objectForwardVector;
			Vector3::Dot(rotateAxis, vector, num);
			if (abs(num) > 0.9982547f)
			{
				num = ((rotateAxis.X * Vector3::Forward.X) + (rotateAxis.Y * Vector3::Forward.Y)) + (rotateAxis.Z * Vector3::Forward.Z);
				vector = (abs(num) > 0.9982547f) ? Vector3::Right : Vector3::Forward;
			}
		}
		else
		{
			num = ((rotateAxis.X * Vector3::Forward.X) + (rotateAxis.Y * Vector3::Forward.Y)) + (rotateAxis.Z * Vector3::Forward.Z);
			vector = (abs(num) > 0.9982547f) ? Vector3::Right : Vector3::Forward;
		}
		Vector3::Cross(rotateAxis, vector, vector3);
		vector3.Normalize();
		Vector3::Cross(vector3, rotateAxis, vector);
		vector.Normalize();
	}
	else
	{
		Vector3::Cross(rotateAxis, vector2, vector3);
		vector3.Normalize();
		Vector3::Cross(vector3, vector4, vector);
		vector.Normalize();
	}
	result.M11 = vector3.X;
	result.M12 = vector3.Y;
	result.M13 = vector3.Z;
	result.M14 = 0;
	result.M21 = vector4.X;
	result.M22 = vector4.Y;
	result.M23 = vector4.Z;
	result.M24 = 0;
	result.M31 = vector.X;
	result.M32 = vector.Y;
	result.M33 = vector.Z;
	result.M34 = 0;
	result.M41 = objectPosition.X;
	result.M42 = objectPosition.Y;
	result.M43 = objectPosition.Z;
	result.M44 = 1;
}

/// <summary>
	 /// Creates a new <see cref="Matrix"/> which contains the rotation moment around specified axis.
	 /// </summary>
	 /// <param name="axis">The axis of rotation.</param>
	 /// <param name="angle">The angle of rotation in radians.</param>
	 /// <returns>The rotation <see cref="Matrix"/>.</returns>
Matrix Matrix::CreateFromAxisAngle(Vector3& axis, float angle)
{
	Matrix result;
	CreateFromAxisAngle(axis, angle, result);
	return result;
}

/// <summary>
/// Creates a new <see cref="Matrix"/> which contains the rotation moment around specified axis.
/// </summary>
/// <param name="axis">The axis of rotation.</param>
/// <param name="angle">The angle of rotation in radians.</param>
/// <param name="result">The rotation <see cref="Matrix"/> as an output parameter.</param>
void Matrix::CreateFromAxisAngle(Vector3& axis, float angle, Matrix& result)
{
	float x = axis.X;
	float y = axis.Y;
	float z = axis.Z;
	float num2 = sin(angle);
	float num = cos(angle);
	float num11 = x * x;
	float num10 = y * y;
	float num9 = z * z;
	float num8 = x * y;
	float num7 = x * z;
	float num6 = y * z;
	result.M11 = num11 + (num * (1.0f - num11));
	result.M12 = (num8 - (num * num8)) + (num2 * z);
	result.M13 = (num7 - (num * num7)) - (num2 * y);
	result.M14 = 0;
	result.M21 = (num8 - (num * num8)) - (num2 * z);
	result.M22 = num10 + (num * (1.0f - num10));
	result.M23 = (num6 - (num * num6)) + (num2 * x);
	result.M24 = 0;
	result.M31 = (num7 - (num * num7)) + (num2 * y);
	result.M32 = (num6 - (num * num6)) - (num2 * x);
	result.M33 = num9 + (num * (1.0f - num9));
	result.M34 = 0;
	result.M41 = 0;
	result.M42 = 0;
	result.M43 = 0;
	result.M44 = 1;
}

/// <summary>
	 /// Creates a new rotation <see cref="Matrix"/> from a <see cref="Quaternion"/>.
	 /// </summary>
	 /// <param name="quaternion"><see cref="Quaternion"/> of rotation moment.</param>
	 /// <returns>The rotation <see cref="Matrix"/>.</returns>
Matrix Matrix::CreateFromQuaternion(Quaternion& quaternion)
{
	Matrix result;
	CreateFromQuaternion(quaternion, result);
	return result;
}

/// <summary>
/// Creates a new rotation <see cref="Matrix"/> from a <see cref="Quaternion"/>.
/// </summary>
/// <param name="quaternion"><see cref="Quaternion"/> of rotation moment.</param>
/// <param name="result">The rotation <see cref="Matrix"/> as an output parameter.</param>
void Matrix::CreateFromQuaternion(Quaternion& quaternion, Matrix& result)
{
	float num9 = quaternion.X * quaternion.X;
	float num8 = quaternion.Y * quaternion.Y;
	float num7 = quaternion.Z * quaternion.Z;
	float num6 = quaternion.X * quaternion.Y;
	float num5 = quaternion.Z * quaternion.W;
	float num4 = quaternion.Z * quaternion.X;
	float num3 = quaternion.Y * quaternion.W;
	float num2 = quaternion.Y * quaternion.Z;
	float num = quaternion.X * quaternion.W;
	result.M11 = 1.0f - (2.0f * (num8 + num7));
	result.M12 = 2.0f * (num6 + num5);
	result.M13 = 2.0f * (num4 - num3);
	result.M14 = 0.0f;
	result.M21 = 2.0f * (num6 - num5);
	result.M22 = 1.0f - (2.0f * (num7 + num9));
	result.M23 = 2.0f * (num2 + num);
	result.M24 = 0.0f;
	result.M31 = 2.0f * (num4 + num3);
	result.M32 = 2.0f * (num2 - num);
	result.M33 = 1.0f - (2.0f * (num8 + num9));
	result.M34 = 0.0f;
	result.M41 = 0.0f;
	result.M42 = 0.0f;
	result.M43 = 0.0f;
	result.M44 = 1.0f;
}

/// <summary>
/// /// Creates a new rotation <see cref="Matrix"/> from the specified yaw, pitch and roll values.
/// </summary>
/// <param name="yaw">The yaw rotation value in radians.</param>
/// <param name="pitch">The pitch rotation value in radians.</param>
/// <param name="roll">The roll rotation value in radians.</param>
/// <returns>The rotation <see cref="Matrix"/>.</returns>
/// <remarks>For more information about yaw, pitch and roll visit http://en.wikipedia.org/wiki/Euler_angles.
/// </remarks>
Matrix Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	Matrix matrix;
	CreateFromYawPitchRoll(yaw, pitch, roll, matrix);
	return matrix;
}

/// <summary>
/// Creates a new rotation <see cref="Matrix"/> from the specified yaw, pitch and roll values.
/// </summary>
/// <param name="yaw">The yaw rotation value in radians.</param>
/// <param name="pitch">The pitch rotation value in radians.</param>
/// <param name="roll">The roll rotation value in radians.</param>
/// <param name="result">The rotation <see cref="Matrix"/> as an output parameter.</param>
/// <remarks>For more information about yaw, pitch and roll visit http://en.wikipedia.org/wiki/Euler_angles.
/// </remarks>
void Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll, Matrix& result)
{
	Quaternion quaternion;
	Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll, quaternion);
	CreateFromQuaternion(quaternion, result);
}

/// <summary>
	   /// Creates a new viewing <see cref="Matrix"/>.
	   /// </summary>
	   /// <param name="cameraPosition">Position of the camera.</param>
	   /// <param name="cameraTarget">Lookup vector of the camera.</param>
	   /// <param name="cameraUpVector">The direction of the upper edge of the camera.</param>
	   /// <returns>The viewing <see cref="Matrix"/>.</returns>
Matrix Matrix::CreateLookAt(Vector3& cameraPosition, Vector3& cameraTarget, Vector3& cameraUpVector)
{
	Matrix matrix;
	CreateLookAt(cameraPosition, cameraTarget, cameraUpVector, matrix);
	return matrix;
}

/// <summary>
/// Creates a new viewing <see cref="Matrix"/>.
/// </summary>
/// <param name="cameraPosition">Position of the camera.</param>
/// <param name="cameraTarget">Lookup vector of the camera.</param>
/// <param name="cameraUpVector">The direction of the upper edge of the camera.</param>
/// <param name="result">The viewing <see cref="Matrix"/> as an output parameter.</param>
void Matrix::CreateLookAt(Vector3& cameraPosition, Vector3& cameraTarget, Vector3& cameraUpVector, Matrix& result)
{
	auto vector = Vector3::Normalize(cameraPosition - cameraTarget);
	auto vector2 = Vector3::Normalize(Vector3::Cross(cameraUpVector, vector));
	auto vector3 = Vector3::Cross(vector, vector2);
	result.M11 = vector2.X;
	result.M12 = vector3.X;
	result.M13 = vector.X;
	result.M14 = 0.0f;
	result.M21 = vector2.Y;
	result.M22 = vector3.Y;
	result.M23 = vector.Y;
	result.M24 = 0.0f;
	result.M31 = vector2.Z;
	result.M32 = vector3.Z;
	result.M33 = vector.Z;
	result.M34 = 0.0f;
	result.M41 = -Vector3::Dot(vector2, cameraPosition);
	result.M42 = -Vector3::Dot(vector3, cameraPosition);
	result.M43 = -Vector3::Dot(vector, cameraPosition);
	result.M44 = 1.0f;
}

/// <summary>
/// Creates a new projection <see cref="Matrix"/> for orthographic view.
/// </summary>
/// <param name="width">Width of the viewing volume.</param>
/// <param name="height">Height of the viewing volume.</param>
/// <param name="zNearPlane">Depth of the near plane.</param>
/// <param name="zFarPlane">Depth of the far plane.</param>
/// <returns>The new projection <see cref="Matrix"/> for orthographic view.</returns>
Matrix Matrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane)
{
	Matrix matrix;
	CreateOrthographic(width, height, zNearPlane, zFarPlane, matrix);
	return matrix;
}

/// <summary>
/// Creates a new projection <see cref="Matrix"/> for orthographic view.
/// </summary>
/// <param name="width">Width of the viewing volume.</param>
/// <param name="height">Height of the viewing volume.</param>
/// <param name="zNearPlane">Depth of the near plane.</param>
/// <param name="zFarPlane">Depth of the far plane.</param>
/// <param name="result">The new projection <see cref="Matrix"/> for orthographic view as an output parameter.</param>
void Matrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane, Matrix& result)
{
	result.M11 = 2.0f / width;
	result.M12 = result.M13 = result.M14 = 0.0f;
	result.M22 = 2.0f / height;
	result.M21 = result.M23 = result.M24 = 0.0f;
	result.M33 = 1.0f / (zNearPlane - zFarPlane);
	result.M31 = result.M32 = result.M34 = 0.0f;
	result.M41 = result.M42 = 0.0f;
	result.M43 = zNearPlane / (zNearPlane - zFarPlane);
	result.M44 = 1.0f;
}

/// <summary>
/// Creates a new projection <see cref="Matrix"/> for customized orthographic view.
/// </summary>
/// <param name="left">Lower x-value at the near plane.</param>
/// <param name="right">Upper x-value at the near plane.</param>
/// <param name="bottom">Lower y-coordinate at the near plane.</param>
/// <param name="top">Upper y-value at the near plane.</param>
/// <param name="zNearPlane">Depth of the near plane.</param>
/// <param name="zFarPlane">Depth of the far plane.</param>
/// <returns>The new projection <see cref="Matrix"/> for customized orthographic view.</returns>
Matrix Matrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
{
	Matrix matrix;
	CreateOrthographicOffCenter(left, right, bottom, top, zNearPlane, zFarPlane, matrix);
	return matrix;
}

Matrix Matrix::CreateOrthographicOffCenter(Rectangle& viewingVolume, float zNearPlane, float zFarPlane)
{
	Matrix matrix;
	CreateOrthographicOffCenter(viewingVolume.GetLeft(), viewingVolume.GetRight(), viewingVolume.GetBottom(), viewingVolume.GetTop(), zNearPlane, zFarPlane, matrix);
	return matrix;
}

/// <summary>
/// Creates a new projection <see cref="Matrix"/> for customized orthographic view.
/// </summary>
/// <param name="viewingVolume">The viewing volume.</param>
/// <param name="zNearPlane">Depth of the near plane.</param>
/// <param name="zFarPlane">Depth of the far plane.</param>
/// <returns>The new projection <see cref="Matrix"/> for customized orthographic view.</returns>


/// <summary>
/// Creates a new projection <see cref="Matrix"/> for customized orthographic view.
/// </summary>
/// <param name="left">Lower x-value at the near plane.</param>
/// <param name="right">Upper x-value at the near plane.</param>
/// <param name="bottom">Lower y-coordinate at the near plane.</param>
/// <param name="top">Upper y-value at the near plane.</param>
/// <param name="zNearPlane">Depth of the near plane.</param>
/// <param name="zFarPlane">Depth of the far plane.</param>
/// <param name="result">The new projection <see cref="Matrix"/> for customized orthographic view as an output parameter.</param>
void Matrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane, Matrix& result)
{
	result.M11 = (float)(2.0 / ((double)right - (double)left));
	result.M12 = 0.0f;
	result.M13 = 0.0f;
	result.M14 = 0.0f;
	result.M21 = 0.0f;
	result.M22 = (float)(2.0 / ((double)top - (double)bottom));
	result.M23 = 0.0f;
	result.M24 = 0.0f;
	result.M31 = 0.0f;
	result.M32 = 0.0f;
	result.M33 = (float)(1.0 / ((double)zNearPlane - (double)zFarPlane));
	result.M34 = 0.0f;
	result.M41 = (float)(((double)left + (double)right) / ((double)left - (double)right));
	result.M42 = (float)(((double)top + (double)bottom) / ((double)bottom - (double)top));
	result.M43 = (float)((double)zNearPlane / ((double)zNearPlane - (double)zFarPlane));
	result.M44 = 1.0f;
}

/// <summary>
/// Creates a new projection <see cref="Matrix"/> for perspective view.
/// </summary>
/// <param name="width">Width of the viewing volume.</param>
/// <param name="height">Height of the viewing volume.</param>
/// <param name="nearPlaneDistance">Distance to the near plane.</param>
/// <param name="farPlaneDistance">Distance to the far plane.</param>
/// <returns>The new projection <see cref="Matrix"/> for perspective view.</returns>
Matrix Matrix::CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance)
{
	Matrix matrix;
	CreatePerspective(width, height, nearPlaneDistance, farPlaneDistance, matrix);
	return matrix;
}

/// <summary>
/// Creates a new projection <see cref="Matrix"/> for perspective view.
/// </summary>
/// <param name="width">Width of the viewing volume.</param>
/// <param name="height">Height of the viewing volume.</param>
/// <param name="nearPlaneDistance">Distance to the near plane.</param>
/// <param name="farPlaneDistance">Distance to the far plane, or <see cref="float.PositiveInfinity"/>.</param>
/// <param name="result">The new projection <see cref="Matrix"/> for perspective view as an output parameter.</param>
void Matrix::CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance, Matrix& result)
{
	auto negFarRange = std::isinf(farPlaneDistance) ? -1.0f : farPlaneDistance / (nearPlaneDistance - farPlaneDistance);

	result.M11 = (2.0f * nearPlaneDistance) / width;
	result.M12 = result.M13 = result.M14 = 0.0f;
	result.M22 = (2.0f * nearPlaneDistance) / height;
	result.M21 = result.M23 = result.M24 = 0.0f;
	result.M33 = negFarRange;
	result.M31 = result.M32 = 0.0f;
	result.M34 = -1.0f;
	result.M41 = result.M42 = result.M44 = 0.0f;
	result.M43 = nearPlaneDistance * negFarRange;
}

/// <summary>
/// Creates a new projection <see cref="Matrix"/> for perspective view with field of view.
/// </summary>
/// <param name="fieldOfView">Field of view in the y direction in radians.</param>
/// <param name="aspectRatio">Width divided by height of the viewing volume.</param>
/// <param name="nearPlaneDistance">Distance to the near plane.</param>
/// <param name="farPlaneDistance">Distance to the far plane, or <see cref="float.PositiveInfinity"/>.</param>
/// <returns>The new projection <see cref="Matrix"/> for perspective view with FOV.</returns>
Matrix Matrix::CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
{
	Matrix result;
	CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlaneDistance, farPlaneDistance, result);
	return result;
}

/// <summary>
/// Creates a new projection <see cref="Matrix"/> for perspective view with field of view.
/// </summary>
/// <param name="fieldOfView">Field of view in the y direction in radians.</param>
/// <param name="aspectRatio">Width divided by height of the viewing volume.</param>
/// <param name="nearPlaneDistance">Distance of the near plane.</param>
/// <param name="farPlaneDistance">Distance of the far plane, or <see cref="float.PositiveInfinity"/>.</param>
/// <param name="result">The new projection <see cref="Matrix"/> for perspective view with FOV as an output parameter.</param>
void Matrix::CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance, Matrix& result)
{
	auto yScale = 1.0f / tan((double)fieldOfView * 0.5f);
	auto xScale = yScale / aspectRatio;
	auto negFarRange = std::isinf(farPlaneDistance) ? -1.0f : farPlaneDistance / (nearPlaneDistance - farPlaneDistance);

	result.M11 = xScale;
	result.M12 = result.M13 = result.M14 = 0.0f;
	result.M22 = yScale;
	result.M21 = result.M23 = result.M24 = 0.0f;
	result.M31 = result.M32 = 0.0f;
	result.M33 = negFarRange;
	result.M34 = -1.0f;
	result.M41 = result.M42 = result.M44 = 0.0f;
	result.M43 = nearPlaneDistance * negFarRange;
}

/// <summary>
/// Creates a new projection <see cref="Matrix"/> for customized perspective view.
/// </summary>
/// <param name="left">Lower x-value at the near plane.</param>
/// <param name="right">Upper x-value at the near plane.</param>
/// <param name="bottom">Lower y-coordinate at the near plane.</param>
/// <param name="top">Upper y-value at the near plane.</param>
/// <param name="nearPlaneDistance">Distance to the near plane.</param>
/// <param name="farPlaneDistance">Distance to the far plane.</param>
/// <returns>The new <see cref="Matrix"/> for customized perspective view.</returns>
Matrix Matrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance)
{
	Matrix result;
	CreatePerspectiveOffCenter(left, right, bottom, top, nearPlaneDistance, farPlaneDistance, result);
	return result;
}

/// <summary>
/// Creates a new projection <see cref="Matrix"/> for customized perspective view.
/// </summary>
/// <param name="viewingVolume">The viewing volume.</param>
/// <param name="nearPlaneDistance">Distance to the near plane.</param>
/// <param name="farPlaneDistance">Distance to the far plane.</param>
/// <returns>The new <see cref="Matrix"/> for customized perspective view.</returns>
Matrix Matrix::CreatePerspectiveOffCenter(Rectangle& viewingVolume, float nearPlaneDistance, float farPlaneDistance)
{
	Matrix result;
	CreatePerspectiveOffCenter(viewingVolume.GetLeft(), viewingVolume.GetRight(), viewingVolume.GetBottom(), viewingVolume.GetTop(), nearPlaneDistance, farPlaneDistance, result);
	return result;
}

/// <summary>
/// Creates a new projection <see cref="Matrix"/> for customized perspective view.
/// </summary>
/// <param name="left">Lower x-value at the near plane.</param>
/// <param name="right">Upper x-value at the near plane.</param>
/// <param name="bottom">Lower y-coordinate at the near plane.</param>
/// <param name="top">Upper y-value at the near plane.</param>
/// <param name="nearPlaneDistance">Distance to the near plane.</param>
/// <param name="farPlaneDistance">Distance to the far plane.</param>
/// <param name="result">The new <see cref="Matrix"/> for customized perspective view as an output parameter.</param>
void Matrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance, Matrix& result)
{
	result.M11 = (2.0f * nearPlaneDistance) / (right - left);
	result.M12 = result.M13 = result.M14 = 0;
	result.M22 = (2.0f * nearPlaneDistance) / (top - bottom);
	result.M21 = result.M23 = result.M24 = 0;
	result.M31 = (left + right) / (right - left);
	result.M32 = (top + bottom) / (top - bottom);
	result.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
	result.M34 = -1;
	result.M43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
	result.M41 = result.M42 = result.M44 = 0;
}

/// <summary>
/// Creates a new rotation <see cref="Matrix"/> around X axis.
/// </summary>
/// <param name="radians">Angle in radians.</param>
/// <returns>The rotation <see cref="Matrix"/> around X axis.</returns>
Matrix Matrix::CreateRotationX(float radians)
{
	Matrix result;
	CreateRotationX(radians, result);
	return result;
}

/// <summary>
/// Creates a new rotation <see cref="Matrix"/> around X axis.
/// </summary>
/// <param name="radians">Angle in radians.</param>
/// <param name="result">The rotation <see cref="Matrix"/> around X axis as an output parameter.</param>
void Matrix::CreateRotationX(float radians, Matrix& result)
{
	result = Matrix::Identity();

	auto val1 = cos(radians);
	auto val2 = sin(radians);

	result.M22 = val1;
	result.M23 = val2;
	result.M32 = -val2;
	result.M33 = val1;
}

/// <summary>
/// Creates a new rotation <see cref="Matrix"/> around Y axis.
/// </summary>
/// <param name="radians">Angle in radians.</param>
/// <returns>The rotation <see cref="Matrix"/> around Y axis.</returns>
Matrix Matrix::CreateRotationY(float radians)
{
	Matrix result;
	CreateRotationY(radians, result);
	return result;
}

/// <summary>
/// Creates a new rotation <see cref="Matrix"/> around Y axis.
/// </summary>
/// <param name="radians">Angle in radians.</param>
/// <param name="result">The rotation <see cref="Matrix"/> around Y axis as an output parameter.</param>
void Matrix::CreateRotationY(float radians, Matrix& result)
{
	result = Matrix::Identity();

	auto val1 = cos(radians);
	auto val2 = sin(radians);

	result.M11 = val1;
	result.M13 = -val2;
	result.M31 = val2;
	result.M33 = val1;
}

/// <summary>
/// Creates a new rotation <see cref="Matrix"/> around Z axis.
/// </summary>
/// <param name="radians">Angle in radians.</param>
/// <returns>The rotation <see cref="Matrix"/> around Z axis.</returns>
Matrix Matrix::CreateRotationZ(float radians)
{
	Matrix result;
	CreateRotationZ(radians, result);
	return result;
}

/// <summary>
/// Creates a new rotation <see cref="Matrix"/> around Z axis.
/// </summary>
/// <param name="radians">Angle in radians.</param>
/// <param name="result">The rotation <see cref="Matrix"/> around Z axis as an output parameter.</param>
void Matrix::CreateRotationZ(float radians, Matrix& result)
{
	result = Matrix::Identity();

	auto val1 = cos(radians);
	auto val2 = sin(radians);

	result.M11 = val1;
	result.M12 = val2;
	result.M21 = -val2;
	result.M22 = val1;
}

/// <summary>
/// Creates a new scaling <see cref="Matrix"/>.
/// </summary>
/// <param name="scale">Scale value for all three axises.</param>
/// <returns>The scaling <see cref="Matrix"/>.</returns>
Matrix Matrix::CreateScale(float scale)
{
	Matrix result;
	CreateScale(scale, scale, scale, result);
	return result;
}

/// <summary>
/// Creates a new scaling <see cref="Matrix"/>.
/// </summary>
/// <param name="scale">Scale value for all three axises.</param>
/// <param name="result">The scaling <see cref="Matrix"/> as an output parameter.</param>
void Matrix::CreateScale(float scale, Matrix& result)
{
	CreateScale(scale, scale, scale, result);
}

/// <summary>
/// Creates a new scaling <see cref="Matrix"/>.
/// </summary>
/// <param name="xScale">Scale value for X axis.</param>
/// <param name="yScale">Scale value for Y axis.</param>
/// <param name="zScale">Scale value for Z axis.</param>
/// <returns>The scaling <see cref="Matrix"/>.</returns>
Matrix Matrix::CreateScale(float xScale, float yScale, float zScale)
{
	Matrix result;
	CreateScale(xScale, yScale, zScale, result);
	return result;
}

/// <summary>
/// Creates a new scaling <see cref="Matrix"/>.
/// </summary>
/// <param name="xScale">Scale value for X axis.</param>
/// <param name="yScale">Scale value for Y axis.</param>
/// <param name="zScale">Scale value for Z axis.</param>
/// <param name="result">The scaling <see cref="Matrix"/> as an output parameter.</param>
void Matrix::CreateScale(float xScale, float yScale, float zScale, Matrix& result)
{
	result.M11 = xScale;
	result.M12 = 0;
	result.M13 = 0;
	result.M14 = 0;
	result.M21 = 0;
	result.M22 = yScale;
	result.M23 = 0;
	result.M24 = 0;
	result.M31 = 0;
	result.M32 = 0;
	result.M33 = zScale;
	result.M34 = 0;
	result.M41 = 0;
	result.M42 = 0;
	result.M43 = 0;
	result.M44 = 1;
}

/// <summary>
/// Creates a new scaling <see cref="Matrix"/>.
/// </summary>
/// <param name="scales"><see cref="Vector3"/> representing x,y and z scale values.</param>
/// <returns>The scaling <see cref="Matrix"/>.</returns>
Matrix Matrix::CreateScale(Vector3& scales)
{
	Matrix result;
	CreateScale(scales, result);
	return result;
}

/// <summary>
/// Creates a new scaling <see cref="Matrix"/>.
/// </summary>
/// <param name="scales"><see cref="Vector3"/> representing x,y and z scale values.</param>
/// <param name="result">The scaling <see cref="Matrix"/> as an output parameter.</param>
void Matrix::CreateScale(Vector3& scales, Matrix& result)
{
	result.M11 = scales.X;
	result.M12 = 0;
	result.M13 = 0;
	result.M14 = 0;
	result.M21 = 0;
	result.M22 = scales.Y;
	result.M23 = 0;
	result.M24 = 0;
	result.M31 = 0;
	result.M32 = 0;
	result.M33 = scales.Z;
	result.M34 = 0;
	result.M41 = 0;
	result.M42 = 0;
	result.M43 = 0;
	result.M44 = 1;
}

/// <summary>
/// Creates a new translation <see cref="Matrix"/>.
/// </summary>
/// <param name="xPosition">X coordinate of translation.</param>
/// <param name="yPosition">Y coordinate of translation.</param>
/// <param name="zPosition">Z coordinate of translation.</param>
/// <returns>The translation <see cref="Matrix"/>.</returns>
Matrix Matrix::CreateTranslation(float xPosition, float yPosition, float zPosition)
{
	Matrix result;
	CreateTranslation(xPosition, yPosition, zPosition, result);
	return result;
}

/// <summary>
/// Creates a new translation <see cref="Matrix"/>.
/// </summary>
/// <param name="position">X,Y and Z coordinates of translation.</param>
/// <param name="result">The translation <see cref="Matrix"/> as an output parameter.</param>
void Matrix::CreateTranslation(Vector3& position, Matrix& result)
{
	result.M11 = 1;
	result.M12 = 0;
	result.M13 = 0;
	result.M14 = 0;
	result.M21 = 0;
	result.M22 = 1;
	result.M23 = 0;
	result.M24 = 0;
	result.M31 = 0;
	result.M32 = 0;
	result.M33 = 1;
	result.M34 = 0;
	result.M41 = position.X;
	result.M42 = position.Y;
	result.M43 = position.Z;
	result.M44 = 1;
}

/// <summary>
/// Creates a new translation <see cref="Matrix"/>.
/// </summary>
/// <param name="position">X,Y and Z coordinates of translation.</param>
/// <returns>The translation <see cref="Matrix"/>.</returns>
Matrix Matrix::CreateTranslation(Vector3& position)
{
	Matrix result;
	CreateTranslation(position, result);
	return result;
}

/// <summary>
/// Creates a new translation <see cref="Matrix"/>.
/// </summary>
/// <param name="xPosition">X coordinate of translation.</param>
/// <param name="yPosition">Y coordinate of translation.</param>
/// <param name="zPosition">Z coordinate of translation.</param>
/// <param name="result">The translation <see cref="Matrix"/> as an output parameter.</param>
void Matrix::CreateTranslation(float xPosition, float yPosition, float zPosition, Matrix& result)
{
	result.M11 = 1;
	result.M12 = 0;
	result.M13 = 0;
	result.M14 = 0;
	result.M21 = 0;
	result.M22 = 1;
	result.M23 = 0;
	result.M24 = 0;
	result.M31 = 0;
	result.M32 = 0;
	result.M33 = 1;
	result.M34 = 0;
	result.M41 = xPosition;
	result.M42 = yPosition;
	result.M43 = zPosition;
	result.M44 = 1;
}

/// <summary>
	/// Creates a new world <see cref="Matrix"/>.
	/// </summary>
	/// <param name="position">The position vector.</param>
	/// <param name="forward">The forward direction vector.</param>
	/// <param name="up">The upward direction vector. Usually <see cref="Vector3.Up"/>.</param>
	/// <returns>The world <see cref="Matrix"/>.</returns>
Matrix Matrix::CreateWorld(Vector3& position, Vector3& forward, Vector3& up)
{
	Matrix ret;
	CreateWorld(position, forward, up, ret);
	return ret;
}

/// <summary>
/// Creates a new world <see cref="Matrix"/>.
/// </summary>
/// <param name="position">The position vector.</param>
/// <param name="forward">The forward direction vector.</param>
/// <param name="up">The upward direction vector. Usually <see cref="Vector3.Up"/>.</param>
/// <param name="result">The world <see cref="Matrix"/> as an output parameter.</param>
void Matrix::CreateWorld(Vector3& position, Vector3& forward, Vector3& up, Matrix& result)
{
	Vector3 x, y, z;
	Vector3::Normalize(forward, z);
	Vector3::Cross(forward, up, x);
	Vector3::Cross(x, forward, y);
	x.Normalize();
	y.Normalize();

	result = Matrix();
	result.Right(x);
	result.Up(y);
	result.Forward(z);
	result.Translation(position);
	result.M44 = 1.0f;
}

/// <summary>
 /// Decomposes this matrix to translation, rotation and scale elements. Returns <c>true</c> if matrix can be decomposed; <c>false</c> otherwise.
 /// </summary>
 /// <param name="scale">Scale vector as an output parameter.</param>
 /// <param name="rotation">Rotation quaternion as an output parameter.</param>
 /// <param name="translation">Translation vector as an output parameter.</param>
 /// <returns><c>true</c> if matrix can be decomposed; <c>false</c> otherwise.</returns>
bool Matrix::Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation)
{
	translation.X = this->M41;
	translation.Y = this->M42;
	translation.Z = this->M43;

	float xs = (std::signbit(M11 * M12 * M13 * M14) < 0) ? -1 : 1;
	float ys = (std::signbit(M21 * M22 * M23 * M24) < 0) ? -1 : 1;
	float zs = (std::signbit(M31 * M32 * M33 * M34) < 0) ? -1 : 1;

	scale.X = xs * sqrt(this->M11 * this->M11 + this->M12 * this->M12 + this->M13 * this->M13);
	scale.Y = ys * sqrt(this->M21 * this->M21 + this->M22 * this->M22 + this->M23 * this->M23);
	scale.Z = zs * sqrt(this->M31 * this->M31 + this->M32 * this->M32 + this->M33 * this->M33);

	if (scale.X == 0.0 || scale.Y == 0.0 || scale.Z == 0.0)
	{
		rotation = Quaternion::Identity;
		return false;
	}

	Matrix m1 = Matrix(this->M11 / scale.X, M12 / scale.X, M13 / scale.X, 0,
		this->M21 / scale.Y, M22 / scale.Y, M23 / scale.Y, 0,
		this->M31 / scale.Z, M32 / scale.Z, M33 / scale.Z, 0,
		0, 0, 0, 1);

	rotation = Quaternion::CreateFromRotationMatrix(m1);
	return true;
}
/// <summary>
/// Returns a determinant of this <see cref="Matrix"/>.
/// </summary>
/// <returns>Determinant of this <see cref="Matrix"/></returns>
/// <remarks>See more about determinant here - http://en.wikipedia.org/wiki/Determinant.
/// </remarks>
float Matrix::Determinant()
{
	float num22 = this->M11;
	float num21 = this->M12;
	float num20 = this->M13;
	float num19 = this->M14;
	float num12 = this->M21;
	float num11 = this->M22;
	float num10 = this->M23;
	float num9 = this->M24;
	float num8 = this->M31;
	float num7 = this->M32;
	float num6 = this->M33;
	float num5 = this->M34;
	float num4 = this->M41;
	float num3 = this->M42;
	float num2 = this->M43;
	float num = this->M44;
	float num18 = (num6 * num) - (num5 * num2);
	float num17 = (num7 * num) - (num5 * num3);
	float num16 = (num7 * num2) - (num6 * num3);
	float num15 = (num8 * num) - (num5 * num4);
	float num14 = (num8 * num2) - (num6 * num4);
	float num13 = (num8 * num3) - (num7 * num4);
	return ((((num22 * (((num11 * num18) - (num10 * num17)) + (num9 * num16))) - (num21 * (((num12 * num18) - (num10 * num15)) + (num9 * num14)))) + (num20 * (((num12 * num17) - (num11 * num15)) + (num9 * num13)))) - (num19 * (((num12 * num16) - (num11 * num14)) + (num10 * num13))));
}

/// <summary>
	  /// Creates a new <see cref="Matrix"/> which contains sum of two matrixes.
	  /// </summary>
	  /// <param name="matrix1">The first matrix to add.</param>
	  /// <param name="matrix2">The second matrix to add.</param>
	  /// <returns>The result of the matrix addition.</returns>
Matrix Matrix::Add(Matrix& matrix1, Matrix& matrix2)
{
	matrix1.M11 += matrix2.M11;
	matrix1.M12 += matrix2.M12;
	matrix1.M13 += matrix2.M13;
	matrix1.M14 += matrix2.M14;
	matrix1.M21 += matrix2.M21;
	matrix1.M22 += matrix2.M22;
	matrix1.M23 += matrix2.M23;
	matrix1.M24 += matrix2.M24;
	matrix1.M31 += matrix2.M31;
	matrix1.M32 += matrix2.M32;
	matrix1.M33 += matrix2.M33;
	matrix1.M34 += matrix2.M34;
	matrix1.M41 += matrix2.M41;
	matrix1.M42 += matrix2.M42;
	matrix1.M43 += matrix2.M43;
	matrix1.M44 += matrix2.M44;
	return matrix1;
}

/// <summary>
/// Creates a new <see cref="Matrix"/> which contains sum of two matrixes.
/// </summary>
/// <param name="matrix1">The first matrix to add.</param>
/// <param name="matrix2">The second matrix to add.</param>
/// <param name="result">The result of the matrix addition as an output parameter.</param>
void Matrix::Add(Matrix& matrix1, Matrix& matrix2, Matrix& result)
{
	result.M11 = matrix1.M11 + matrix2.M11;
	result.M12 = matrix1.M12 + matrix2.M12;
	result.M13 = matrix1.M13 + matrix2.M13;
	result.M14 = matrix1.M14 + matrix2.M14;
	result.M21 = matrix1.M21 + matrix2.M21;
	result.M22 = matrix1.M22 + matrix2.M22;
	result.M23 = matrix1.M23 + matrix2.M23;
	result.M24 = matrix1.M24 + matrix2.M24;
	result.M31 = matrix1.M31 + matrix2.M31;
	result.M32 = matrix1.M32 + matrix2.M32;
	result.M33 = matrix1.M33 + matrix2.M33;
	result.M34 = matrix1.M34 + matrix2.M34;
	result.M41 = matrix1.M41 + matrix2.M41;
	result.M42 = matrix1.M42 + matrix2.M42;
	result.M43 = matrix1.M43 + matrix2.M43;
	result.M44 = matrix1.M44 + matrix2.M44;

}
/// <summary>
/// Divides the elements of a <see cref="Matrix"/> by the elements of another matrix.
/// </summary>
/// <param name="matrix1">Source <see cref="Matrix"/>.</param>
/// <param name="matrix2">Divisor <see cref="Matrix"/>.</param>
/// <returns>The result of dividing the matrix.</returns>
Matrix Matrix::Divide(Matrix& matrix1, Matrix& matrix2)
{
	matrix1.M11 = matrix1.M11 / matrix2.M11;
	matrix1.M12 = matrix1.M12 / matrix2.M12;
	matrix1.M13 = matrix1.M13 / matrix2.M13;
	matrix1.M14 = matrix1.M14 / matrix2.M14;
	matrix1.M21 = matrix1.M21 / matrix2.M21;
	matrix1.M22 = matrix1.M22 / matrix2.M22;
	matrix1.M23 = matrix1.M23 / matrix2.M23;
	matrix1.M24 = matrix1.M24 / matrix2.M24;
	matrix1.M31 = matrix1.M31 / matrix2.M31;
	matrix1.M32 = matrix1.M32 / matrix2.M32;
	matrix1.M33 = matrix1.M33 / matrix2.M33;
	matrix1.M34 = matrix1.M34 / matrix2.M34;
	matrix1.M41 = matrix1.M41 / matrix2.M41;
	matrix1.M42 = matrix1.M42 / matrix2.M42;
	matrix1.M43 = matrix1.M43 / matrix2.M43;
	matrix1.M44 = matrix1.M44 / matrix2.M44;
	return matrix1;
}

/// <summary>
/// Divides the elements of a <see cref="Matrix"/> by the elements of another matrix.
/// </summary>
/// <param name="matrix1">Source <see cref="Matrix"/>.</param>
/// <param name="matrix2">Divisor <see cref="Matrix"/>.</param>
/// <param name="result">The result of dividing the matrix as an output parameter.</param>
void Matrix::Divide(Matrix& matrix1, Matrix& matrix2, Matrix& result)
{
	result.M11 = matrix1.M11 / matrix2.M11;
	result.M12 = matrix1.M12 / matrix2.M12;
	result.M13 = matrix1.M13 / matrix2.M13;
	result.M14 = matrix1.M14 / matrix2.M14;
	result.M21 = matrix1.M21 / matrix2.M21;
	result.M22 = matrix1.M22 / matrix2.M22;
	result.M23 = matrix1.M23 / matrix2.M23;
	result.M24 = matrix1.M24 / matrix2.M24;
	result.M31 = matrix1.M31 / matrix2.M31;
	result.M32 = matrix1.M32 / matrix2.M32;
	result.M33 = matrix1.M33 / matrix2.M33;
	result.M34 = matrix1.M34 / matrix2.M34;
	result.M41 = matrix1.M41 / matrix2.M41;
	result.M42 = matrix1.M42 / matrix2.M42;
	result.M43 = matrix1.M43 / matrix2.M43;
	result.M44 = matrix1.M44 / matrix2.M44;
}

/// <summary>
/// Divides the elements of a <see cref="Matrix"/> by a scalar.
/// </summary>
/// <param name="matrix1">Source <see cref="Matrix"/>.</param>
/// <param name="divider">Divisor scalar.</param>
/// <returns>The result of dividing a matrix by a scalar.</returns>
Matrix Matrix::Divide(Matrix matrix1, float divider)
{
	float num = 1.0f / divider;
	matrix1.M11 = matrix1.M11 * num;
	matrix1.M12 = matrix1.M12 * num;
	matrix1.M13 = matrix1.M13 * num;
	matrix1.M14 = matrix1.M14 * num;
	matrix1.M21 = matrix1.M21 * num;
	matrix1.M22 = matrix1.M22 * num;
	matrix1.M23 = matrix1.M23 * num;
	matrix1.M24 = matrix1.M24 * num;
	matrix1.M31 = matrix1.M31 * num;
	matrix1.M32 = matrix1.M32 * num;
	matrix1.M33 = matrix1.M33 * num;
	matrix1.M34 = matrix1.M34 * num;
	matrix1.M41 = matrix1.M41 * num;
	matrix1.M42 = matrix1.M42 * num;
	matrix1.M43 = matrix1.M43 * num;
	matrix1.M44 = matrix1.M44 * num;
	return matrix1;
}

/// <summary>
/// Divides the elements of a <see cref="Matrix"/> by a scalar.
/// </summary>
/// <param name="matrix1">Source <see cref="Matrix"/>.</param>
/// <param name="divider">Divisor scalar.</param>
/// <param name="result">The result of dividing a matrix by a scalar as an output parameter.</param>
void Matrix::Divide(Matrix& matrix1, float divider, Matrix& result)
{
	float num = 1.0f / divider;
	result.M11 = matrix1.M11 * num;
	result.M12 = matrix1.M12 * num;
	result.M13 = matrix1.M13 * num;
	result.M14 = matrix1.M14 * num;
	result.M21 = matrix1.M21 * num;
	result.M22 = matrix1.M22 * num;
	result.M23 = matrix1.M23 * num;
	result.M24 = matrix1.M24 * num;
	result.M31 = matrix1.M31 * num;
	result.M32 = matrix1.M32 * num;
	result.M33 = matrix1.M33 * num;
	result.M34 = matrix1.M34 * num;
	result.M41 = matrix1.M41 * num;
	result.M42 = matrix1.M42 * num;
	result.M43 = matrix1.M43 * num;
	result.M44 = matrix1.M44 * num;
}

/// <summary>
	   /// Creates a new <see cref="Matrix"/> which contains inversion of the specified matrix. 
	   /// </summary>
	   /// <param name="matrix">Source <see cref="Matrix"/>.</param>
	   /// <returns>The inverted matrix.</returns>
Matrix Matrix::Invert(Matrix& matrix)
{
	Matrix result;
	Invert(matrix, result);
	return result;
}

/// <summary>
/// Creates a new <see cref="Matrix"/> which contains inversion of the specified matrix. 
/// </summary>
/// <param name="matrix">Source <see cref="Matrix"/>.</param>
/// <param name="result">The inverted matrix as output parameter.</param>
void Matrix::Invert(Matrix& matrix, Matrix& result)
{
	float num1 = matrix.M11;
	float num2 = matrix.M12;
	float num3 = matrix.M13;
	float num4 = matrix.M14;
	float num5 = matrix.M21;
	float num6 = matrix.M22;
	float num7 = matrix.M23;
	float num8 = matrix.M24;
	float num9 = matrix.M31;
	float num10 = matrix.M32;
	float num11 = matrix.M33;
	float num12 = matrix.M34;
	float num13 = matrix.M41;
	float num14 = matrix.M42;
	float num15 = matrix.M43;
	float num16 = matrix.M44;
	float num17 = (float)((double)num11 * (double)num16 - (double)num12 * (double)num15);
	float num18 = (float)((double)num10 * (double)num16 - (double)num12 * (double)num14);
	float num19 = (float)((double)num10 * (double)num15 - (double)num11 * (double)num14);
	float num20 = (float)((double)num9 * (double)num16 - (double)num12 * (double)num13);
	float num21 = (float)((double)num9 * (double)num15 - (double)num11 * (double)num13);
	float num22 = (float)((double)num9 * (double)num14 - (double)num10 * (double)num13);
	float num23 = (float)((double)num6 * (double)num17 - (double)num7 * (double)num18 + (double)num8 * (double)num19);
	float num24 = (float)-((double)num5 * (double)num17 - (double)num7 * (double)num20 + (double)num8 * (double)num21);
	float num25 = (float)((double)num5 * (double)num18 - (double)num6 * (double)num20 + (double)num8 * (double)num22);
	float num26 = (float)-((double)num5 * (double)num19 - (double)num6 * (double)num21 + (double)num7 * (double)num22);
	float num27 = (float)(1.0 / ((double)num1 * (double)num23 + (double)num2 * (double)num24 + (double)num3 * (double)num25 + (double)num4 * (double)num26));

	result.M11 = num23 * num27;
	result.M21 = num24 * num27;
	result.M31 = num25 * num27;
	result.M41 = num26 * num27;
	result.M12 = (float)-((double)num2 * (double)num17 - (double)num3 * (double)num18 + (double)num4 * (double)num19) * num27;
	result.M22 = (float)((double)num1 * (double)num17 - (double)num3 * (double)num20 + (double)num4 * (double)num21) * num27;
	result.M32 = (float)-((double)num1 * (double)num18 - (double)num2 * (double)num20 + (double)num4 * (double)num22) * num27;
	result.M42 = (float)((double)num1 * (double)num19 - (double)num2 * (double)num21 + (double)num3 * (double)num22) * num27;
	float num28 = (float)((double)num7 * (double)num16 - (double)num8 * (double)num15);
	float num29 = (float)((double)num6 * (double)num16 - (double)num8 * (double)num14);
	float num30 = (float)((double)num6 * (double)num15 - (double)num7 * (double)num14);
	float num31 = (float)((double)num5 * (double)num16 - (double)num8 * (double)num13);
	float num32 = (float)((double)num5 * (double)num15 - (double)num7 * (double)num13);
	float num33 = (float)((double)num5 * (double)num14 - (double)num6 * (double)num13);
	result.M13 = (float)((double)num2 * (double)num28 - (double)num3 * (double)num29 + (double)num4 * (double)num30) * num27;
	result.M23 = (float)-((double)num1 * (double)num28 - (double)num3 * (double)num31 + (double)num4 * (double)num32) * num27;
	result.M33 = (float)((double)num1 * (double)num29 - (double)num2 * (double)num31 + (double)num4 * (double)num33) * num27;
	result.M43 = (float)-((double)num1 * (double)num30 - (double)num2 * (double)num32 + (double)num3 * (double)num33) * num27;
	float num34 = (float)((double)num7 * (double)num12 - (double)num8 * (double)num11);
	float num35 = (float)((double)num6 * (double)num12 - (double)num8 * (double)num10);
	float num36 = (float)((double)num6 * (double)num11 - (double)num7 * (double)num10);
	float num37 = (float)((double)num5 * (double)num12 - (double)num8 * (double)num9);
	float num38 = (float)((double)num5 * (double)num11 - (double)num7 * (double)num9);
	float num39 = (float)((double)num5 * (double)num10 - (double)num6 * (double)num9);
	result.M14 = (float)-((double)num2 * (double)num34 - (double)num3 * (double)num35 + (double)num4 * (double)num36) * num27;
	result.M24 = (float)((double)num1 * (double)num34 - (double)num3 * (double)num37 + (double)num4 * (double)num38) * num27;
	result.M34 = (float)-((double)num1 * (double)num35 - (double)num2 * (double)num37 + (double)num4 * (double)num39) * num27;
	result.M44 = (float)((double)num1 * (double)num36 - (double)num2 * (double)num38 + (double)num3 * (double)num39) * num27;

}

/// <summary>
	   /// Creates a new <see cref="Matrix"/> that contains linear interpolation of the values in specified matrixes.
	   /// </summary>
	   /// <param name="matrix1">The first <see cref="Matrix"/>.</param>
	   /// <param name="matrix2">The second <see cref="Vector2"/>.</param>
	   /// <param name="amount">Weighting value(between 0.0 and 1.0).</param>
	   /// <returns>>The result of linear interpolation of the specified matrixes.</returns>
Matrix Matrix::Lerp(Matrix& matrix1, Matrix& matrix2, float amount)
{
	matrix1.M11 = matrix1.M11 + ((matrix2.M11 - matrix1.M11) * amount);
	matrix1.M12 = matrix1.M12 + ((matrix2.M12 - matrix1.M12) * amount);
	matrix1.M13 = matrix1.M13 + ((matrix2.M13 - matrix1.M13) * amount);
	matrix1.M14 = matrix1.M14 + ((matrix2.M14 - matrix1.M14) * amount);
	matrix1.M21 = matrix1.M21 + ((matrix2.M21 - matrix1.M21) * amount);
	matrix1.M22 = matrix1.M22 + ((matrix2.M22 - matrix1.M22) * amount);
	matrix1.M23 = matrix1.M23 + ((matrix2.M23 - matrix1.M23) * amount);
	matrix1.M24 = matrix1.M24 + ((matrix2.M24 - matrix1.M24) * amount);
	matrix1.M31 = matrix1.M31 + ((matrix2.M31 - matrix1.M31) * amount);
	matrix1.M32 = matrix1.M32 + ((matrix2.M32 - matrix1.M32) * amount);
	matrix1.M33 = matrix1.M33 + ((matrix2.M33 - matrix1.M33) * amount);
	matrix1.M34 = matrix1.M34 + ((matrix2.M34 - matrix1.M34) * amount);
	matrix1.M41 = matrix1.M41 + ((matrix2.M41 - matrix1.M41) * amount);
	matrix1.M42 = matrix1.M42 + ((matrix2.M42 - matrix1.M42) * amount);
	matrix1.M43 = matrix1.M43 + ((matrix2.M43 - matrix1.M43) * amount);
	matrix1.M44 = matrix1.M44 + ((matrix2.M44 - matrix1.M44) * amount);
	return matrix1;
}

/// <summary>
/// Creates a new <see cref="Matrix"/> that contains linear interpolation of the values in specified matrixes.
/// </summary>
/// <param name="matrix1">The first <see cref="Matrix"/>.</param>
/// <param name="matrix2">The second <see cref="Vector2"/>.</param>
/// <param name="amount">Weighting value(between 0.0 and 1.0).</param>
/// <param name="result">The result of linear interpolation of the specified matrixes as an output parameter.</param>
void Matrix::Lerp(Matrix& matrix1, Matrix& matrix2, float amount, Matrix& result)
{
	result.M11 = matrix1.M11 + ((matrix2.M11 - matrix1.M11) * amount);
	result.M12 = matrix1.M12 + ((matrix2.M12 - matrix1.M12) * amount);
	result.M13 = matrix1.M13 + ((matrix2.M13 - matrix1.M13) * amount);
	result.M14 = matrix1.M14 + ((matrix2.M14 - matrix1.M14) * amount);
	result.M21 = matrix1.M21 + ((matrix2.M21 - matrix1.M21) * amount);
	result.M22 = matrix1.M22 + ((matrix2.M22 - matrix1.M22) * amount);
	result.M23 = matrix1.M23 + ((matrix2.M23 - matrix1.M23) * amount);
	result.M24 = matrix1.M24 + ((matrix2.M24 - matrix1.M24) * amount);
	result.M31 = matrix1.M31 + ((matrix2.M31 - matrix1.M31) * amount);
	result.M32 = matrix1.M32 + ((matrix2.M32 - matrix1.M32) * amount);
	result.M33 = matrix1.M33 + ((matrix2.M33 - matrix1.M33) * amount);
	result.M34 = matrix1.M34 + ((matrix2.M34 - matrix1.M34) * amount);
	result.M41 = matrix1.M41 + ((matrix2.M41 - matrix1.M41) * amount);
	result.M42 = matrix1.M42 + ((matrix2.M42 - matrix1.M42) * amount);
	result.M43 = matrix1.M43 + ((matrix2.M43 - matrix1.M43) * amount);
	result.M44 = matrix1.M44 + ((matrix2.M44 - matrix1.M44) * amount);
}

/// <summary>
/// Creates a new <see cref="Matrix"/> that contains a multiplication of two matrix.
/// </summary>
/// <param name="matrix1">Source <see cref="Matrix"/>.</param>
/// <param name="matrix2">Source <see cref="Matrix"/>.</param>
/// <returns>Result of the matrix multiplication.</returns>
Matrix  Matrix::Multiply(Matrix& matrix1, Matrix& matrix2)
{
	auto m11 = (((matrix1.M11 * matrix2.M11) + (matrix1.M12 * matrix2.M21)) + (matrix1.M13 * matrix2.M31)) + (matrix1.M14 * matrix2.M41);
	auto m12 = (((matrix1.M11 * matrix2.M12) + (matrix1.M12 * matrix2.M22)) + (matrix1.M13 * matrix2.M32)) + (matrix1.M14 * matrix2.M42);
	auto m13 = (((matrix1.M11 * matrix2.M13) + (matrix1.M12 * matrix2.M23)) + (matrix1.M13 * matrix2.M33)) + (matrix1.M14 * matrix2.M43);
	auto m14 = (((matrix1.M11 * matrix2.M14) + (matrix1.M12 * matrix2.M24)) + (matrix1.M13 * matrix2.M34)) + (matrix1.M14 * matrix2.M44);
	auto m21 = (((matrix1.M21 * matrix2.M11) + (matrix1.M22 * matrix2.M21)) + (matrix1.M23 * matrix2.M31)) + (matrix1.M24 * matrix2.M41);
	auto m22 = (((matrix1.M21 * matrix2.M12) + (matrix1.M22 * matrix2.M22)) + (matrix1.M23 * matrix2.M32)) + (matrix1.M24 * matrix2.M42);
	auto m23 = (((matrix1.M21 * matrix2.M13) + (matrix1.M22 * matrix2.M23)) + (matrix1.M23 * matrix2.M33)) + (matrix1.M24 * matrix2.M43);
	auto m24 = (((matrix1.M21 * matrix2.M14) + (matrix1.M22 * matrix2.M24)) + (matrix1.M23 * matrix2.M34)) + (matrix1.M24 * matrix2.M44);
	auto m31 = (((matrix1.M31 * matrix2.M11) + (matrix1.M32 * matrix2.M21)) + (matrix1.M33 * matrix2.M31)) + (matrix1.M34 * matrix2.M41);
	auto m32 = (((matrix1.M31 * matrix2.M12) + (matrix1.M32 * matrix2.M22)) + (matrix1.M33 * matrix2.M32)) + (matrix1.M34 * matrix2.M42);
	auto m33 = (((matrix1.M31 * matrix2.M13) + (matrix1.M32 * matrix2.M23)) + (matrix1.M33 * matrix2.M33)) + (matrix1.M34 * matrix2.M43);
	auto m34 = (((matrix1.M31 * matrix2.M14) + (matrix1.M32 * matrix2.M24)) + (matrix1.M33 * matrix2.M34)) + (matrix1.M34 * matrix2.M44);
	auto m41 = (((matrix1.M41 * matrix2.M11) + (matrix1.M42 * matrix2.M21)) + (matrix1.M43 * matrix2.M31)) + (matrix1.M44 * matrix2.M41);
	auto m42 = (((matrix1.M41 * matrix2.M12) + (matrix1.M42 * matrix2.M22)) + (matrix1.M43 * matrix2.M32)) + (matrix1.M44 * matrix2.M42);
	auto m43 = (((matrix1.M41 * matrix2.M13) + (matrix1.M42 * matrix2.M23)) + (matrix1.M43 * matrix2.M33)) + (matrix1.M44 * matrix2.M43);
	auto m44 = (((matrix1.M41 * matrix2.M14) + (matrix1.M42 * matrix2.M24)) + (matrix1.M43 * matrix2.M34)) + (matrix1.M44 * matrix2.M44);
	matrix1.M11 = m11;
	matrix1.M12 = m12;
	matrix1.M13 = m13;
	matrix1.M14 = m14;
	matrix1.M21 = m21;
	matrix1.M22 = m22;
	matrix1.M23 = m23;
	matrix1.M24 = m24;
	matrix1.M31 = m31;
	matrix1.M32 = m32;
	matrix1.M33 = m33;
	matrix1.M34 = m34;
	matrix1.M41 = m41;
	matrix1.M42 = m42;
	matrix1.M43 = m43;
	matrix1.M44 = m44;
	return matrix1;
}

/// <summary>
/// Creates a new <see cref="Matrix"/> that contains a multiplication of two matrix.
/// </summary>
/// <param name="matrix1">Source <see cref="Matrix"/>.</param>
/// <param name="matrix2">Source <see cref="Matrix"/>.</param>
/// <param name="result">Result of the matrix multiplication as an output parameter.</param>
void  Matrix::Multiply(Matrix& matrix1, Matrix& matrix2, Matrix& result)
{
	auto m11 = (((matrix1.M11 * matrix2.M11) + (matrix1.M12 * matrix2.M21)) + (matrix1.M13 * matrix2.M31)) + (matrix1.M14 * matrix2.M41);
	auto m12 = (((matrix1.M11 * matrix2.M12) + (matrix1.M12 * matrix2.M22)) + (matrix1.M13 * matrix2.M32)) + (matrix1.M14 * matrix2.M42);
	auto m13 = (((matrix1.M11 * matrix2.M13) + (matrix1.M12 * matrix2.M23)) + (matrix1.M13 * matrix2.M33)) + (matrix1.M14 * matrix2.M43);
	auto m14 = (((matrix1.M11 * matrix2.M14) + (matrix1.M12 * matrix2.M24)) + (matrix1.M13 * matrix2.M34)) + (matrix1.M14 * matrix2.M44);
	auto m21 = (((matrix1.M21 * matrix2.M11) + (matrix1.M22 * matrix2.M21)) + (matrix1.M23 * matrix2.M31)) + (matrix1.M24 * matrix2.M41);
	auto m22 = (((matrix1.M21 * matrix2.M12) + (matrix1.M22 * matrix2.M22)) + (matrix1.M23 * matrix2.M32)) + (matrix1.M24 * matrix2.M42);
	auto m23 = (((matrix1.M21 * matrix2.M13) + (matrix1.M22 * matrix2.M23)) + (matrix1.M23 * matrix2.M33)) + (matrix1.M24 * matrix2.M43);
	auto m24 = (((matrix1.M21 * matrix2.M14) + (matrix1.M22 * matrix2.M24)) + (matrix1.M23 * matrix2.M34)) + (matrix1.M24 * matrix2.M44);
	auto m31 = (((matrix1.M31 * matrix2.M11) + (matrix1.M32 * matrix2.M21)) + (matrix1.M33 * matrix2.M31)) + (matrix1.M34 * matrix2.M41);
	auto m32 = (((matrix1.M31 * matrix2.M12) + (matrix1.M32 * matrix2.M22)) + (matrix1.M33 * matrix2.M32)) + (matrix1.M34 * matrix2.M42);
	auto m33 = (((matrix1.M31 * matrix2.M13) + (matrix1.M32 * matrix2.M23)) + (matrix1.M33 * matrix2.M33)) + (matrix1.M34 * matrix2.M43);
	auto m34 = (((matrix1.M31 * matrix2.M14) + (matrix1.M32 * matrix2.M24)) + (matrix1.M33 * matrix2.M34)) + (matrix1.M34 * matrix2.M44);
	auto m41 = (((matrix1.M41 * matrix2.M11) + (matrix1.M42 * matrix2.M21)) + (matrix1.M43 * matrix2.M31)) + (matrix1.M44 * matrix2.M41);
	auto m42 = (((matrix1.M41 * matrix2.M12) + (matrix1.M42 * matrix2.M22)) + (matrix1.M43 * matrix2.M32)) + (matrix1.M44 * matrix2.M42);
	auto m43 = (((matrix1.M41 * matrix2.M13) + (matrix1.M42 * matrix2.M23)) + (matrix1.M43 * matrix2.M33)) + (matrix1.M44 * matrix2.M43);
	auto m44 = (((matrix1.M41 * matrix2.M14) + (matrix1.M42 * matrix2.M24)) + (matrix1.M43 * matrix2.M34)) + (matrix1.M44 * matrix2.M44);
	result.M11 = m11;
	result.M12 = m12;
	result.M13 = m13;
	result.M14 = m14;
	result.M21 = m21;
	result.M22 = m22;
	result.M23 = m23;
	result.M24 = m24;
	result.M31 = m31;
	result.M32 = m32;
	result.M33 = m33;
	result.M34 = m34;
	result.M41 = m41;
	result.M42 = m42;
	result.M43 = m43;
	result.M44 = m44;
}

/// <summary>
/// Creates a new <see cref="Matrix"/> that contains a multiplication of <see cref="Matrix"/> and a scalar.
/// </summary>
/// <param name="matrix1">Source <see cref="Matrix"/>.</param>
/// <param name="scaleFactor">Scalar value.</param>
/// <returns>Result of the matrix multiplication with a scalar.</returns>
Matrix  Matrix::Multiply(Matrix& matrix1, float scaleFactor)
{
	matrix1.M11 *= scaleFactor;
	matrix1.M12 *= scaleFactor;
	matrix1.M13 *= scaleFactor;
	matrix1.M14 *= scaleFactor;
	matrix1.M21 *= scaleFactor;
	matrix1.M22 *= scaleFactor;
	matrix1.M23 *= scaleFactor;
	matrix1.M24 *= scaleFactor;
	matrix1.M31 *= scaleFactor;
	matrix1.M32 *= scaleFactor;
	matrix1.M33 *= scaleFactor;
	matrix1.M34 *= scaleFactor;
	matrix1.M41 *= scaleFactor;
	matrix1.M42 *= scaleFactor;
	matrix1.M43 *= scaleFactor;
	matrix1.M44 *= scaleFactor;
	return matrix1;
}

/// <summary>
/// Creates a new <see cref="Matrix"/> that contains a multiplication of <see cref="Matrix"/> and a scalar.
/// </summary>
/// <param name="matrix1">Source <see cref="Matrix"/>.</param>
/// <param name="scaleFactor">Scalar value.</param>
/// <param name="result">Result of the matrix multiplication with a scalar as an output parameter.</param>
void Matrix::Multiply(Matrix& matrix1, float scaleFactor, Matrix& result)
{
	result.M11 = matrix1.M11 * scaleFactor;
	result.M12 = matrix1.M12 * scaleFactor;
	result.M13 = matrix1.M13 * scaleFactor;
	result.M14 = matrix1.M14 * scaleFactor;
	result.M21 = matrix1.M21 * scaleFactor;
	result.M22 = matrix1.M22 * scaleFactor;
	result.M23 = matrix1.M23 * scaleFactor;
	result.M24 = matrix1.M24 * scaleFactor;
	result.M31 = matrix1.M31 * scaleFactor;
	result.M32 = matrix1.M32 * scaleFactor;
	result.M33 = matrix1.M33 * scaleFactor;
	result.M34 = matrix1.M34 * scaleFactor;
	result.M41 = matrix1.M41 * scaleFactor;
	result.M42 = matrix1.M42 * scaleFactor;
	result.M43 = matrix1.M43 * scaleFactor;
	result.M44 = matrix1.M44 * scaleFactor;

}
/// <summary>
 /// Copy the values of specified <see cref="Matrix"/> to the float array.
 /// </summary>
 /// <param name="matrix">The source <see cref="Matrix"/>.</param>
 /// <returns>The array which matrix values will be stored.</returns>
 /// <remarks>
 /// Required for OpenGL 2.0 projection matrix stuff.
 /// </remarks>
float* Matrix::ToFloatArray(Matrix& matrix)
{
	float matarray[16] = {
							matrix.M11, matrix.M12, matrix.M13, matrix.M14,
							matrix.M21, matrix.M22, matrix.M23, matrix.M24,
							matrix.M31, matrix.M32, matrix.M33, matrix.M34,
							matrix.M41, matrix.M42, matrix.M43, matrix.M44
	};
	return matarray;
}

/// <summary>
/// Returns a matrix with the all values negated.
/// </summary>
/// <param name="matrix">Source <see cref="Matrix"/>.</param>
/// <returns>Result of the matrix negation.</returns>
Matrix Matrix::Negate(Matrix& matrix)
{
	matrix.M11 = -matrix.M11;
	matrix.M12 = -matrix.M12;
	matrix.M13 = -matrix.M13;
	matrix.M14 = -matrix.M14;
	matrix.M21 = -matrix.M21;
	matrix.M22 = -matrix.M22;
	matrix.M23 = -matrix.M23;
	matrix.M24 = -matrix.M24;
	matrix.M31 = -matrix.M31;
	matrix.M32 = -matrix.M32;
	matrix.M33 = -matrix.M33;
	matrix.M34 = -matrix.M34;
	matrix.M41 = -matrix.M41;
	matrix.M42 = -matrix.M42;
	matrix.M43 = -matrix.M43;
	matrix.M44 = -matrix.M44;
	return matrix;
}

/// <summary>
/// Returns a matrix with the all values negated.
/// </summary>
/// <param name="matrix">Source <see cref="Matrix"/>.</param>
/// <param name="result">Result of the matrix negation as an output parameter.</param>
void Matrix::Negate(Matrix& matrix, Matrix& result)
{
	result.M11 = -matrix.M11;
	result.M12 = -matrix.M12;
	result.M13 = -matrix.M13;
	result.M14 = -matrix.M14;
	result.M21 = -matrix.M21;
	result.M22 = -matrix.M22;
	result.M23 = -matrix.M23;
	result.M24 = -matrix.M24;
	result.M31 = -matrix.M31;
	result.M32 = -matrix.M32;
	result.M33 = -matrix.M33;
	result.M34 = -matrix.M34;
	result.M41 = -matrix.M41;
	result.M42 = -matrix.M42;
	result.M43 = -matrix.M43;
	result.M44 = -matrix.M44;
}

/// <summary>
		/// Creates a new <see cref="Matrix"/> that contains subtraction of one matrix from another.
		/// </summary>
		/// <param name="matrix1">The first <see cref="Matrix"/>.</param>
		/// <param name="matrix2">The second <see cref="Matrix"/>.</param>
		/// <returns>The result of the matrix subtraction.</returns>
Matrix Matrix::Subtract(Matrix& matrix1, Matrix& matrix2)
{
	matrix1.M11 = matrix1.M11 - matrix2.M11;
	matrix1.M12 = matrix1.M12 - matrix2.M12;
	matrix1.M13 = matrix1.M13 - matrix2.M13;
	matrix1.M14 = matrix1.M14 - matrix2.M14;
	matrix1.M21 = matrix1.M21 - matrix2.M21;
	matrix1.M22 = matrix1.M22 - matrix2.M22;
	matrix1.M23 = matrix1.M23 - matrix2.M23;
	matrix1.M24 = matrix1.M24 - matrix2.M24;
	matrix1.M31 = matrix1.M31 - matrix2.M31;
	matrix1.M32 = matrix1.M32 - matrix2.M32;
	matrix1.M33 = matrix1.M33 - matrix2.M33;
	matrix1.M34 = matrix1.M34 - matrix2.M34;
	matrix1.M41 = matrix1.M41 - matrix2.M41;
	matrix1.M42 = matrix1.M42 - matrix2.M42;
	matrix1.M43 = matrix1.M43 - matrix2.M43;
	matrix1.M44 = matrix1.M44 - matrix2.M44;
	return matrix1;
}

/// <summary>
/// Creates a new <see cref="Matrix"/> that contains subtraction of one matrix from another.
/// </summary>
/// <param name="matrix1">The first <see cref="Matrix"/>.</param>
/// <param name="matrix2">The second <see cref="Matrix"/>.</param>
/// <param name="result">The result of the matrix subtraction as an output parameter.</param>
void Matrix::Subtract(Matrix& matrix1, Matrix& matrix2, Matrix& result)
{
	result.M11 = matrix1.M11 - matrix2.M11;
	result.M12 = matrix1.M12 - matrix2.M12;
	result.M13 = matrix1.M13 - matrix2.M13;
	result.M14 = matrix1.M14 - matrix2.M14;
	result.M21 = matrix1.M21 - matrix2.M21;
	result.M22 = matrix1.M22 - matrix2.M22;
	result.M23 = matrix1.M23 - matrix2.M23;
	result.M24 = matrix1.M24 - matrix2.M24;
	result.M31 = matrix1.M31 - matrix2.M31;
	result.M32 = matrix1.M32 - matrix2.M32;
	result.M33 = matrix1.M33 - matrix2.M33;
	result.M34 = matrix1.M34 - matrix2.M34;
	result.M41 = matrix1.M41 - matrix2.M41;
	result.M42 = matrix1.M42 - matrix2.M42;
	result.M43 = matrix1.M43 - matrix2.M43;
	result.M44 = matrix1.M44 - matrix2.M44;
}

// Matrix addition
Matrix operator+(const Matrix& matrix1, const Matrix& matrix2) {
	return Matrix(
		matrix1.M11 + matrix2.M11, matrix1.M12 + matrix2.M12, matrix1.M13 + matrix2.M13, matrix1.M14 + matrix2.M14,
		matrix1.M21 + matrix2.M21, matrix1.M22 + matrix2.M22, matrix1.M23 + matrix2.M23, matrix1.M24 + matrix2.M24,
		matrix1.M31 + matrix2.M31, matrix1.M32 + matrix2.M32, matrix1.M33 + matrix2.M33, matrix1.M34 + matrix2.M34,
		matrix1.M41 + matrix2.M41, matrix1.M42 + matrix2.M42, matrix1.M43 + matrix2.M43, matrix1.M44 + matrix2.M44
	);
}

// Matrix division by another matrix
Matrix operator/(const Matrix& matrix1, const Matrix& matrix2) {
	return Matrix(
		matrix1.M11 / matrix2.M11, matrix1.M12 / matrix2.M12, matrix1.M13 / matrix2.M13, matrix1.M14 / matrix2.M14,
		matrix1.M21 / matrix2.M21, matrix1.M22 / matrix2.M22, matrix1.M23 / matrix2.M23, matrix1.M24 / matrix2.M24,
		matrix1.M31 / matrix2.M31, matrix1.M32 / matrix2.M32, matrix1.M33 / matrix2.M33, matrix1.M34 / matrix2.M34,
		matrix1.M41 / matrix2.M41, matrix1.M42 / matrix2.M42, matrix1.M43 / matrix2.M43, matrix1.M44 / matrix2.M44
	);
}

// Matrix division by a scalar
Matrix operator/(const Matrix& matrix, float divider) {
	float num = 1.0f / divider;
	return Matrix(
		matrix.M11 * num, matrix.M12 * num, matrix.M13 * num, matrix.M14 * num,
		matrix.M21 * num, matrix.M22 * num, matrix.M23 * num, matrix.M24 * num,
		matrix.M31 * num, matrix.M32 * num, matrix.M33 * num, matrix.M34 * num,
		matrix.M41 * num, matrix.M42 * num, matrix.M43 * num, matrix.M44 * num
	);
}

// Matrix equality comparison
bool operator==(const Matrix& matrix1, const Matrix& matrix2) {
	return (
		matrix1.M11 == matrix2.M11 && matrix1.M12 == matrix2.M12 && matrix1.M13 == matrix2.M13 && matrix1.M14 == matrix2.M14 &&
		matrix1.M21 == matrix2.M21 && matrix1.M22 == matrix2.M22 && matrix1.M23 == matrix2.M23 && matrix1.M24 == matrix2.M24 &&
		matrix1.M31 == matrix2.M31 && matrix1.M32 == matrix2.M32 && matrix1.M33 == matrix2.M33 && matrix1.M34 == matrix2.M34 &&
		matrix1.M41 == matrix2.M41 && matrix1.M42 == matrix2.M42 && matrix1.M43 == matrix2.M43 && matrix1.M44 == matrix2.M44
		);
}

// Matrix inequality comparison
bool operator!=(const Matrix& matrix1, const Matrix& matrix2) {
	return !operator==(matrix1, matrix2);
}

// Matrix multiplication
Matrix operator*(const Matrix& matrix1, const Matrix& matrix2) {
	return Matrix(
		(((matrix1.M11 * matrix2.M11) + (matrix1.M12 * matrix2.M21)) + (matrix1.M13 * matrix2.M31)) + (matrix1.M14 * matrix2.M41),
		(((matrix1.M11 * matrix2.M12) + (matrix1.M12 * matrix2.M22)) + (matrix1.M13 * matrix2.M32)) + (matrix1.M14 * matrix2.M42),
		(((matrix1.M11 * matrix2.M13) + (matrix1.M12 * matrix2.M23)) + (matrix1.M13 * matrix2.M33)) + (matrix1.M14 * matrix2.M43),
		(((matrix1.M11 * matrix2.M14) + (matrix1.M12 * matrix2.M24)) + (matrix1.M13 * matrix2.M34)) + (matrix1.M14 * matrix2.M44),
		(((matrix1.M21 * matrix2.M11) + (matrix1.M22 * matrix2.M21)) + (matrix1.M23 * matrix2.M31)) + (matrix1.M24 * matrix2.M41),
		(((matrix1.M21 * matrix2.M12) + (matrix1.M22 * matrix2.M22)) + (matrix1.M23 * matrix2.M32)) + (matrix1.M24 * matrix2.M42),
		(((matrix1.M21 * matrix2.M13) + (matrix1.M22 * matrix2.M23)) + (matrix1.M23 * matrix2.M33)) + (matrix1.M24 * matrix2.M43),
		(((matrix1.M21 * matrix2.M14) + (matrix1.M22 * matrix2.M24)) + (matrix1.M23 * matrix2.M34)) + (matrix1.M24 * matrix2.M44),
		(((matrix1.M31 * matrix2.M11) + (matrix1.M32 * matrix2.M21)) + (matrix1.M33 * matrix2.M31)) + (matrix1.M34 * matrix2.M41),
		(((matrix1.M31 * matrix2.M12) + (matrix1.M32 * matrix2.M22)) + (matrix1.M33 * matrix2.M32)) + (matrix1.M34 * matrix2.M42),
		(((matrix1.M31 * matrix2.M13) + (matrix1.M32 * matrix2.M23)) + (matrix1.M33 * matrix2.M33)) + (matrix1.M34 * matrix2.M43),
		(((matrix1.M31 * matrix2.M14) + (matrix1.M32 * matrix2.M24)) + (matrix1.M33 * matrix2.M34)) + (matrix1.M34 * matrix2.M44),
		(((matrix1.M41 * matrix2.M11) + (matrix1.M42 * matrix2.M21)) + (matrix1.M43 * matrix2.M31)) + (matrix1.M44 * matrix2.M41),
		(((matrix1.M41 * matrix2.M12) + (matrix1.M42 * matrix2.M22)) + (matrix1.M43 * matrix2.M32)) + (matrix1.M44 * matrix2.M42),
		(((matrix1.M41 * matrix2.M13) + (matrix1.M42 * matrix2.M23)) + (matrix1.M43 * matrix2.M33)) + (matrix1.M44 * matrix2.M43),
		(((matrix1.M41 * matrix2.M14) + (matrix1.M42 * matrix2.M24)) + (matrix1.M43 * matrix2.M34)) + (matrix1.M44 * matrix2.M44)
	);
}

// Matrix multiplication by a scalar
Matrix operator*(const Matrix& matrix, float scaleFactor) {
	return Matrix(
		matrix.M11 * scaleFactor, matrix.M12 * scaleFactor, matrix.M13 * scaleFactor, matrix.M14 * scaleFactor,
		matrix.M21 * scaleFactor, matrix.M22 * scaleFactor, matrix.M23 * scaleFactor, matrix.M24 * scaleFactor,
		matrix.M31 * scaleFactor, matrix.M32 * scaleFactor, matrix.M33 * scaleFactor, matrix.M34 * scaleFactor,
		matrix.M41 * scaleFactor, matrix.M42 * scaleFactor, matrix.M43 * scaleFactor, matrix.M44 * scaleFactor
	);
}

// Matrix subtraction
Matrix operator-(const Matrix& matrix1, const Matrix& matrix2) {
	return Matrix(
		matrix1.M11 - matrix2.M11, matrix1.M12 - matrix2.M12, matrix1.M13 - matrix2.M13, matrix1.M14 - matrix2.M14,
		matrix1.M21 - matrix2.M21, matrix1.M22 - matrix2.M22, matrix1.M23 - matrix2.M23, matrix1.M24 - matrix2.M24,
		matrix1.M31 - matrix2.M31, matrix1.M32 - matrix2.M32, matrix1.M33 - matrix2.M33, matrix1.M34 - matrix2.M34,
		matrix1.M41 - matrix2.M41, matrix1.M42 - matrix2.M42, matrix1.M43 - matrix2.M43, matrix1.M44 - matrix2.M44
	);
}

// Matrix negation
Matrix operator-(const Matrix& matrix) {
	return Matrix(
		-matrix.M11, -matrix.M12, -matrix.M13, -matrix.M14,
		-matrix.M21, -matrix.M22, -matrix.M23, -matrix.M24,
		-matrix.M31, -matrix.M32, -matrix.M33, -matrix.M34,
		-matrix.M41, -matrix.M42, -matrix.M43, -matrix.M44
	);
}
void Matrix::FindDeterminants(Matrix& matrix, float& major, float& minor1, float& minor2, float& minor3, float& minor4, float& minor5, float& minor6, float& minor7, float& minor8, float& minor9, float& minor10, float& minor11, float& minor12)
{
	double det1 = (double)matrix.M11 * (double)matrix.M22 - (double)matrix.M12 * (double)matrix.M21;
	double det2 = (double)matrix.M11 * (double)matrix.M23 - (double)matrix.M13 * (double)matrix.M21;
	double det3 = (double)matrix.M11 * (double)matrix.M24 - (double)matrix.M14 * (double)matrix.M21;
	double det4 = (double)matrix.M12 * (double)matrix.M23 - (double)matrix.M13 * (double)matrix.M22;
	double det5 = (double)matrix.M12 * (double)matrix.M24 - (double)matrix.M14 * (double)matrix.M22;
	double det6 = (double)matrix.M13 * (double)matrix.M24 - (double)matrix.M14 * (double)matrix.M23;
	double det7 = (double)matrix.M31 * (double)matrix.M42 - (double)matrix.M32 * (double)matrix.M41;
	double det8 = (double)matrix.M31 * (double)matrix.M43 - (double)matrix.M33 * (double)matrix.M41;
	double det9 = (double)matrix.M31 * (double)matrix.M44 - (double)matrix.M34 * (double)matrix.M41;
	double det10 = (double)matrix.M32 * (double)matrix.M43 - (double)matrix.M33 * (double)matrix.M42;
	double det11 = (double)matrix.M32 * (double)matrix.M44 - (double)matrix.M34 * (double)matrix.M42;
	double det12 = (double)matrix.M33 * (double)matrix.M44 - (double)matrix.M34 * (double)matrix.M43;

	major = (float)(det1 * det12 - det2 * det11 + det3 * det10 + det4 * det9 - det5 * det8 + det6 * det7);
	minor1 = (float)det1;
	minor2 = (float)det2;
	minor3 = (float)det3;
	minor4 = (float)det4;
	minor5 = (float)det5;
	minor6 = (float)det6;
	minor7 = (float)det7;
	minor8 = (float)det8;
	minor9 = (float)det9;
	minor10 = (float)det10;
	minor11 = (float)det11;
	minor12 = (float)det12;
}
