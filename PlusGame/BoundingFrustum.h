#pragma once

#include "Matrix.h"
#include "Vector3.h"
#include "Plane.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"
#include "Ray.h"

enum ContainmentType
{
	Disjoint,
	Contains,
	Intersects
};

enum PlaneIntersectionType
{
	Front,
	Intersecting,
	Back
};

class BoundingFrustum
{
public:
	static const int PlaneCount = 6;
	static const int CornerCount = 8;

	BoundingFrustum(Matrix& value);

	Matrix GetMatrix();
	void SetMatrix(Matrix& value);

	Plane GetNear();
	Plane GetFar();
	Plane GetLeft();
	Plane GetRight();
	Plane GetTop();
	Plane GetBottom();

	ContainmentType Contains(BoundingBox& box);

	void Contains(BoundingBox& box, ContainmentType& result);

	ContainmentType Contains(BoundingFrustum& frustum);

	ContainmentType Contains(BoundingSphere& sphere);

	void Contains(BoundingSphere& sphere, ContainmentType& result);

	ContainmentType Contains(Vector3 point);

	void Contains(Vector3& point, ContainmentType& result);

	bool Intersects(BoundingBox& box);
	bool Intersects(BoundingFrustum& frustum);
	bool Intersects(BoundingSphere& sphere);
	PlaneIntersectionType Intersects(Plane& plane);
	void Intersects(Plane& plane, PlaneIntersectionType& result);

	float Intersects(Ray& ray);
	void Intersects(Ray& ray, float& result);

	Vector3* GetCorners();

	bool operator==(BoundingFrustum& other);
	bool operator!=(BoundingFrustum& other);

private:
	Matrix _matrix;
	Vector3 _corners[CornerCount];
	Plane _planes[PlaneCount];

	void CreateCorners();
	void CreatePlanes();
	static void IntersectionPoint(Plane& a, Plane& b, Plane& c, Vector3& result);
	void NormalizePlane(Plane& p);
};


