#pragma once
#include "Vector3.h"
#include "IntersectionEnums.h"
#include "BoundingSphere.h"
#include "Plane.h"
class BoundingBox
{
public:
	static const Vector3 MaxVector3;
	static const Vector3 MinVector3;
	/// <summary>
		///   The minimum extent of this <see cref="BoundingBox"/>.
		/// </summary> 
	Vector3 Min;

	/// <summary>
	///   The maximum extent of this <see cref="BoundingBox"/>.
	/// </summary> 
	Vector3 Max;

	/// <summary>
	///   The number of corners in a <see cref="BoundingBox"/>. This is equal to 8.
	/// </summary>
	const int CornerCount = 8;

	/// <summary>
		///   Create a <see cref="BoundingBox"/>.
		/// </summary>
		/// <param name="min">The minimum extent of the <see cref="BoundingBox"/>.</param>
		/// <param name="max">The maximum extent of the <see cref="BoundingBox"/>.</param>
	BoundingBox(Vector3 min, Vector3 max) : Max(max), Min(min) {}
	BoundingBox() : Max(MaxVector3), Min(MinVector3) {}

	ContainmentType Contains(BoundingBox& box);
	void Contains(BoundingBox& box, ContainmentType& result);
	ContainmentType Contains(Vector3& point);
	void Contains(Vector3& point, ContainmentType& result);
	BoundingBox CreateFromPoints(Vector3* points, int index, int count);
	BoundingBox CreateMerged(BoundingBox& original, BoundingBox& additional);
	void CreateMerged(BoundingBox& original, BoundingBox& additional, BoundingBox& result);
	Vector3* GetCorners();
	void GetCorners(Vector3* corners);
	bool Intersects(BoundingBox& box);
	void Intersects(BoundingBox& box, bool& result);
	bool Intersects(BoundingSphere& sphere);
	void Intersects(BoundingSphere& sphere, bool& result);
	bool Intersects(BoundingSphere* sphere);
	void Intersects(BoundingSphere* sphere, bool& result);

	PlaneIntersectionType Intersects(Plane& plane);
	void Intersects(Plane& plane, PlaneIntersectionType& result);

};

