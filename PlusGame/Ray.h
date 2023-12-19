#pragma once
#include "BoundingBox.h"
class Ray
{
public:
	/// <summary>
	/// The direction of this <see cref="Ray"/>.
	/// </summary>
	Vector3 Direction;

	/// <summary>
	/// The origin of this <see cref="Ray"/>.
	/// </summary>
	Vector3 Position;

	Ray(Vector3 position, Vector3 direction) : Position(position), Direction(direction) { }
	Ray() : Position(Vector3(0)), Direction(Vector3(0)) { }

	float Intersects(BoundingBox& box);
	void Intersects(BoundingSphere& sphere, float& result);
	void Intersects(Plane& plane, float& result);

	void Intersects(BoundingBox& box, float& result);
	float Intersects(BoundingSphere& sphere);
	float Intersects(Plane plane);

};

