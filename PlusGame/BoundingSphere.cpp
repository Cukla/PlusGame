#include "BoundingSphere.h"
#include "BoundingBox.h"

/// <summary>
 /// Creates the smallest <see cref="BoundingSphere"/> that can contain a specified <see cref="BoundingBox"/>.
 /// </summary>
 /// <param name="box">The box to create the sphere from.</param>
 /// <returns>The new <see cref="BoundingSphere"/>.</returns>
BoundingSphere BoundingSphere::CreateFromBoundingBox(BoundingBox& box)
{
	BoundingSphere result;
	CreateFromBoundingBox(box, result);
	return result;
}

/// <summary>
/// Creates the smallest <see cref="BoundingSphere"/> that can contain a specified <see cref="BoundingBox"/>.
/// </summary>
/// <param name="box">The box to create the sphere from.</param>
/// <param name="result">The new <see cref="BoundingSphere"/> as an output parameter.</param>
void BoundingSphere::CreateFromBoundingBox(BoundingBox& box, BoundingSphere& result)
{
	// Find the center of the box.
	Vector3 center = Vector3((box.Min.X + box.Max.X) / 2.0f,
		(box.Min.Y + box.Max.Y) / 2.0f,
		(box.Min.Z + box.Max.Z) / 2.0f);

	// Find the distance between the center and one of the corners of the box.
	float radius = Vector3::Distance(center, box.Max);

	result = BoundingSphere(center, radius);
}

/// <summary>
/// Creates the smallest <see cref="BoundingSphere"/> that can contain two spheres.
/// </summary>
/// <param name="original">First sphere.</param>
/// <param name="additional">Second sphere.</param>
/// <returns>The new <see cref="BoundingSphere"/>.</returns>
BoundingSphere BoundingSphere::CreateMerged(BoundingSphere& original, BoundingSphere& additional)
{
	BoundingSphere result;
	CreateMerged(original, additional, result);
	return result;
}

/// <summary>
/// Creates the smallest <see cref="BoundingSphere"/> that can contain two spheres.
/// </summary>
/// <param name="original">First sphere.</param>
/// <param name="additional">Second sphere.</param>
/// <param name="result">The new <see cref="BoundingSphere"/> as an output parameter.</param>
void BoundingSphere::CreateMerged(BoundingSphere& original, BoundingSphere& additional, BoundingSphere& result)
{
	Vector3 ocenterToaCenter = Vector3::Subtract(additional.Center, original.Center);
	float distance = Vector3::Length(ocenterToaCenter);
	if (distance <= original.Radius + additional.Radius)//intersect
	{
		if (distance <= original.Radius - additional.Radius)//original contain additional
		{
			result = original;
			return;
		}
		if (distance <= additional.Radius - original.Radius)//additional contain original
		{
			result = additional;
			return;
		}
	}
	//else find center of new sphere and radius
	float leftRadius = MathHelper::Max(original.Radius - distance, additional.Radius);
	float Rightradius = MathHelper::Max(original.Radius + distance, additional.Radius);
	ocenterToaCenter = ocenterToaCenter + (ocenterToaCenter * ((leftRadius - Rightradius) / (Vector3::Length(ocenterToaCenter) * 2)));//oCenterToResultCenter

	result = BoundingSphere();
	result.Center = original.Center + ocenterToaCenter;
	result.Radius = (leftRadius + Rightradius) / 2;
}

/// <summary>
/// Gets whether or not a specified <see cref="BoundingBox"/> intersects with this sphere.
/// </summary>
/// <param name="box">The box for testing.</param>
/// <returns><c>true</c> if <see cref="BoundingBox"/> intersects with this sphere; <c>false</c> otherwise.</returns>
bool BoundingSphere::Intersects(BoundingBox& box)
{
	return box.Intersects(this);
}

/// <summary>
/// Gets whether or not a specified <see cref="BoundingBox"/> intersects with this sphere.
/// </summary>
/// <param name="box">The box for testing.</param>
/// <param name="result"><c>true</c> if <see cref="BoundingBox"/> intersects with this sphere; <c>false</c> otherwise. As an output parameter.</param>
void BoundingSphere::Intersects(BoundingBox& box, bool& result)
{
	box.Intersects(this, result);
}

bool BoundingSphere::Intersects(BoundingSphere& sphere)
{
	bool result;
	Intersects(sphere, result);
	return result;
}

/// <summary>
/// Gets whether or not the other <see cref="BoundingSphere"/> intersects with this sphere.
/// </summary>
/// <param name="sphere">The other sphere for testing.</param>
/// <param name="result"><c>true</c> if other <see cref="BoundingSphere"/> intersects with this sphere; <c>false</c> otherwise. As an output parameter.</param>
void BoundingSphere::Intersects(BoundingSphere& sphere, bool& result)
{
	float sqDistance;
	Vector3::DistanceSquared(sphere.Center, Center, sqDistance);

	if (sqDistance > (sphere.Radius + Radius) * (sphere.Radius + Radius))
		result = false;
	else
		result = true;
}

/// <summary>
/// Gets whether or not a specified <see cref="Plane"/> intersects with this sphere.
/// </summary>
/// <param name="plane">The plane for testing.</param>
/// <returns>Type of intersection.</returns>
PlaneIntersectionType BoundingSphere::Intersects(Plane& plane)
{
	auto result = PlaneIntersectionType::Back;
	// TODO: we might want to inline this for performance reasons
	Intersects(plane, result);
	return result;
}

/// <summary>
/// Gets whether or not a specified <see cref="Plane"/> intersects with this sphere.
/// </summary>
/// <param name="plane">The plane for testing.</param>
/// <param name="result">Type of intersection as an output parameter.</param>
void BoundingSphere::Intersects(Plane& plane, PlaneIntersectionType& result)
{
	float distance = 0;
	// TODO: we might want to inline this for performance reasons
	Vector3::Dot(plane.Normal, Center, distance);
	distance += plane.D;
	if (distance > this->Radius)
		result = PlaneIntersectionType::Front;
	else if (distance < -this->Radius)
		result = PlaneIntersectionType::Back;
	else
		result = PlaneIntersectionType::Intersecting;
}