#pragma once
#include "Vector3.h"
class BoundingSphere
{
public:
	/// <summary>
	/// The sphere center.
	/// </summary>
	Vector3 Center;

	/// <summary>
	/// The sphere radius.
	/// </summary>
	float Radius;

	BoundingSphere(Vector3 center, float radius) : Center(center), Radius(radius) {}
	BoundingSphere() : Center(0), Radius(0) {}
	BoundingSphere CreateFromBoundingBox(BoundingBox& box);
	void CreateFromBoundingBox(BoundingBox& box, BoundingSphere& result);
	BoundingSphere CreateMerged(BoundingSphere& original, BoundingSphere& additional);
	void CreateMerged(BoundingSphere& original, BoundingSphere& additional, BoundingSphere& result);
	bool Intersects(BoundingBox& box);
	void Intersects(BoundingBox& box, bool& result);
	bool Intersects(BoundingSphere& sphere);
	void Intersects(BoundingSphere& sphere, bool& result);
	PlaneIntersectionType Intersects(Plane& plane);
	void Intersects(Plane& plane, PlaneIntersectionType& result);
};

