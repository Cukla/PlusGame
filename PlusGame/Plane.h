#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "BoundingBox.h"
#include "BoundingFrustum.h"
#include "BoundingSphere.h" 

class Plane
{
public:
	float D;
	Vector3 Normal;

	Plane() { Plane(0); };
	Plane(Vector4 value);
	Plane(Vector3 normal, float d);
	Plane(Vector3 a, Vector3 b, Vector3 c);
	Plane(float a, float b, float c, float d);
	Plane(Vector3 pointOnPlane, Vector3 normal);

	float Dot(Vector4 value);
	void Dot(Vector4& value, float& result);
	float DotCoordinate(Vector3 value);
	void DotCoordinate(Vector3& value, float& result);
	float DotNormal(Vector3 value);
	void DotNormal(Vector3& value, float& result);

	static Plane Transform(Plane plane, Matrix matrix);
	static void Transform(Plane& plane, Matrix& matrix, Plane& result);
	static Plane Transform(Plane plane, Quaternion rotation);
	static void Transform(Plane& plane, Quaternion& rotation, Plane& result);

	void Normalize();
	static Plane Normalize(Plane value);
	static void Normalize(Plane& value, Plane& result);

	bool operator!=(Plane& other);
	bool operator==(Plane& other);

	bool Equals(Plane& other);
	int GetHashCode();

	PlaneIntersectionType Intersects(BoundingBox box);
	void Intersects(BoundingBox& box, PlaneIntersectionType& result);
	PlaneIntersectionType Intersects(BoundingFrustum frustum);
	PlaneIntersectionType Intersects(BoundingSphere sphere);
	void Intersects(BoundingSphere& sphere, PlaneIntersectionType& result);

	PlaneIntersectionType Intersects(Vector3& point);

	void Deconstruct(Vector3& normal, float& d);

	static float ClassifyPoint(Vector3& point, Plane& plane);
	static float PerpendicularDistance(Vector3& point, Plane& plane);
};
