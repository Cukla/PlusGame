#include "Ray.h"

// adapted from http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-7-intersecting-simple-shapes/ray-box-intersection/
/// <summary>
/// Check if this <see cref="Ray"/> intersects the specified <see cref="BoundingBox"/>.
/// </summary>
/// <param name="box">The <see cref="BoundingBox"/> to test for intersection.</param>
/// <returns>
/// The distance along the ray of the intersection or <code>NULL</code> if this
/// <see cref="Ray"/> does not intersect the <see cref="BoundingBox"/>.
/// </returns>			
float Ray::Intersects(BoundingBox& box) {
	const float Epsilon = 1e-6f;

	float tMin = -std::numeric_limits<float>::infinity();
	float tMax = std::numeric_limits<float>::infinity();

	if (std::abs(Direction.X) < Epsilon) {
		if (Position.X < box.Min.X || Position.X > box.Max.X)
			return std::numeric_limits<float>::quiet_NaN();
	}
	else {
		tMin = (box.Min.X - Position.X) / Direction.X;
		tMax = (box.Max.X - Position.X) / Direction.X;

		if (tMin > tMax) {
			std::swap(tMin, tMax);
		}
	}

	if (std::abs(Direction.Y) < Epsilon) {
		if (Position.Y < box.Min.Y || Position.Y > box.Max.Y)
			return std::numeric_limits<float>::quiet_NaN();
	}
	else {
		float tMinY = (box.Min.Y - Position.Y) / Direction.Y;
		float tMaxY = (box.Max.Y - Position.Y) / Direction.Y;

		if (tMinY > tMaxY) {
			std::swap(tMinY, tMaxY);
		}

		if (tMin > tMaxY || tMinY > tMax)
			return std::numeric_limits<float>::quiet_NaN();

		tMin = std::max(tMin, tMinY);
		tMax = std::min(tMax, tMaxY);
	}

	if (std::abs(Direction.Z) < Epsilon) {
		if (Position.Z < box.Min.Z || Position.Z > box.Max.Z)
			return std::numeric_limits<float>::quiet_NaN();
	}
	else {
		float tMinZ = (box.Min.Z - Position.Z) / Direction.Z;
		float tMaxZ = (box.Max.Z - Position.Z) / Direction.Z;

		if (tMinZ > tMaxZ) {
			std::swap(tMinZ, tMaxZ);
		}

		if (tMin > tMaxZ || tMinZ > tMax)
			return std::numeric_limits<float>::quiet_NaN();

		tMin = std::max(tMin, tMinZ);
		tMax = std::min(tMax, tMaxZ);
	}


	if (tMin < 0 && tMax > 0)
		return 0;

	if (tMin < 0)
		return std::numeric_limits<float>::quiet_NaN();

	return tMin;
}

/// <summary>
/// Check if this <see cref="Ray"/> intersects the specified <see cref="BoundingSphere"/>.
/// </summary>
/// <param name="sphere">The <see cref="BoundingBox"/> to test for intersection.</param>
/// <param name="result">
/// The distance along the ray of the intersection or <code>null</code> if this
/// <see cref="Ray"/> does not intersect the <see cref="BoundingSphere"/>.
/// </param>
void Ray::Intersects(BoundingSphere& sphere, float& result)
{
	// Find the vector between where the ray starts the the sphere's centre
	Vector3 difference = sphere.Center - this->Position;

	float differenceLengthSquared = difference.LengthSquared();
	float sphereRadiusSquared = sphere.Radius * sphere.Radius;

	float distanceAlongRay;

	// If the distance between the ray start and the sphere's centre is less than
	// the radius of the sphere, it means we've intersected. N.B. checking the LengthSquared is faster.
	if (differenceLengthSquared < sphereRadiusSquared)
	{
		result = 0.0f;
		return;
	}

	Vector3::Dot(this->Direction, difference, distanceAlongRay);
	// If the ray is pointing away from the sphere then we don't ever intersect
	if (distanceAlongRay < 0)
	{
		result = std::numeric_limits<float>::quiet_NaN();
		return;
	}

	// Next we kinda use Pythagoras to check if we are within the bounds of the sphere
	// if x = radius of sphere
	// if y = distance between ray position and sphere centre
	// if z = the distance we've travelled along the ray
	// if x^2 + z^2 - y^2 < 0, we do not intersect
	float dist = sphereRadiusSquared + distanceAlongRay * distanceAlongRay - differenceLengthSquared;

	result = (dist < 0) ? std::numeric_limits<float>::quiet_NaN() : distanceAlongRay - (float)sqrt(dist);
}

/// <summary>
/// Check if this <see cref="Ray"/> intersects the specified <see cref="Plane"/>.
/// </summary>
/// <param name="plane">The <see cref="Plane"/> to test for intersection.</param>
/// <param name="result">
/// The distance along the ray of the intersection or <code>null</code> if this
/// <see cref="Ray"/> does not intersect the <see cref="Plane"/>.
/// </param>
void Ray::Intersects(Plane& plane, float& result)
{
	auto den = Vector3::Dot(Direction, plane.Normal);
	if (abs(den) < 0.00001f)
	{
		result = std::numeric_limits<float>::quiet_NaN();
		return;
	}

	result = (-plane.D - Vector3::Dot(plane.Normal, Position)) / den;

	if (result < 0.0f)
	{
		if (result < -0.00001f)
		{
			result = std::numeric_limits<float>::quiet_NaN();
			return;
		}
		result = 0.0f;
	}
}

/// <summary>
/// Check if this <see cref="Ray"/> intersects the specified <see cref="BoundingBox"/>.
/// </summary>
/// <param name="box">The <see cref="BoundingBox"/> to test for intersection.</param>
/// <param name="result">
/// The distance along the ray of the intersection or <code>null</code> if this
/// <see cref="Ray"/> does not intersect the <see cref="BoundingBox"/>.
/// </param>
void Ray::Intersects(BoundingBox& box, float& result)
{
	result = Intersects(box);
}

/// <summary>
/// Check if this <see cref="Ray"/> intersects the specified <see cref="BoundingSphere"/>.
/// </summary>
/// <param name="sphere">The <see cref="BoundingBox"/> to test for intersection.</param>
/// <returns>
/// The distance along the ray of the intersection or <code>null</code> if this
/// <see cref="Ray"/> does not intersect the <see cref="BoundingSphere"/>.
/// </returns>
float Ray::Intersects(BoundingSphere& sphere)
{
	float result;
	Intersects(sphere, result);
	return result;
}

/// <summary>
/// Check if this <see cref="Ray"/> intersects the specified <see cref="Plane"/>.
/// </summary>
/// <param name="plane">The <see cref="Plane"/> to test for intersection.</param>
/// <returns>
/// The distance along the ray of the intersection or <code>null</code> if this
/// <see cref="Ray"/> does not intersect the <see cref="Plane"/>.
/// </returns>
float Ray::Intersects(Plane plane)
{
	float result;
	Intersects(plane, result);
	return result;
}