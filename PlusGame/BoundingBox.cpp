#include "BoundingBox.h"

const Vector3 BoundingBox::MaxVector3(std::numeric_limits<float>::max());
const Vector3 BoundingBox::MinVector3(std::numeric_limits<float>::min());
/// <summary>
///   Check if this <see cref="BoundingBox"/> contains another <see cref="BoundingBox"/>.
/// </summary>
/// <param name="box">The <see cref="BoundingBox"/> to test for overlap.</param>
/// <returns>
///   A value indicating if this <see cref="BoundingBox"/> contains,
///   intersects with or is disjoint with <paramref name="box"/>.
/// </returns>
ContainmentType BoundingBox::Contains(BoundingBox& box)
{
	//test if all corner is in the same side of a face by just checking min and max
	if (box.Max.X < Min.X
		|| box.Min.X > Max.X
		|| box.Max.Y < Min.Y
		|| box.Min.Y > Max.Y
		|| box.Max.Z < Min.Z
		|| box.Min.Z > Max.Z)
		return ContainmentType::Disjoint;


	if (box.Min.X >= Min.X
		&& box.Max.X <= Max.X
		&& box.Min.Y >= Min.Y
		&& box.Max.Y <= Max.Y
		&& box.Min.Z >= Min.Z
		&& box.Max.Z <= Max.Z)
		return ContainmentType::Contains;

	return ContainmentType::Intersects;
}

/// <summary>
///   Check if this <see cref="BoundingBox"/> contains another <see cref="BoundingBox"/>.
/// </summary>
/// <param name="box">The <see cref="BoundingBox"/> to test for overlap.</param>
/// <param name="result">
///   A value indicating if this <see cref="BoundingBox"/> contains,
///   intersects with or is disjoint with <paramref name="box"/>.
/// </param>
void BoundingBox::Contains(BoundingBox& box, ContainmentType& result)
{
	result = Contains(box);
}

/// <summary>
///   Check if this <see cref="BoundingBox"/> contains a point.
/// </summary>
/// <param name="point">The <see cref="Vector3"/> to test.</param>
/// <returns>
///   <see cref="ContainmentType.Contains"/> if this <see cref="BoundingBox"/> contains
///   <paramref name="point"/> or <see cref="ContainmentType.Disjoint"/> if it does not.
/// </returns>
ContainmentType BoundingBox::Contains(Vector3& point)
{
	ContainmentType result;
	this->Contains(point, result);
	return result;
}

/// <summary>
///   Check if this <see cref="BoundingBox"/> contains a point.
/// </summary>
/// <param name="point">The <see cref="Vector3"/> to test.</param>
/// <param name="result">
///   <see cref="ContainmentType.Contains"/> if this <see cref="BoundingBox"/> contains
///   <paramref name="point"/> or <see cref="ContainmentType.Disjoint"/> if it does not.
/// </param>
void BoundingBox::Contains(Vector3& point, ContainmentType& result)
{
	//first we get if point is out of box
	if (point.X < this->Min.X
		|| point.X > this->Max.X
		|| point.Y < this->Min.Y
		|| point.Y > this->Max.Y
		|| point.Z < this->Min.Z
		|| point.Z > this->Max.Z)
	{
		result = ContainmentType::Disjoint;
	}
	else
	{
		result = ContainmentType::Contains;
	}
}

/// <summary>
/// Create a bounding box from the given list of points.
/// </summary>
/// <param name="points">The array of Vector3 instances defining the point cloud to bound</param>
/// <param name="index">The base index to start iterating from</param>
/// <param name="count">The number of points to iterate</param>
/// <returns>A bounding box that encapsulates the given point cloud.</returns>
/// <exception cref="System.ArgumentException">Thrown if the given array is null or has no points.</exception>
BoundingBox BoundingBox::CreateFromPoints(Vector3* points, int index = 0, int count = -1)
{
	if (count == -1)
		count = sizeof(points) / sizeof(points[0]);

	auto minVec = MaxVector3;
	auto maxVec = MinVector3;
	for (int i = index; i < count; i++)
	{
		minVec.X = (minVec.X < points[i].X) ? minVec.X : points[i].X;
		minVec.Y = (minVec.Y < points[i].Y) ? minVec.Y : points[i].Y;
		minVec.Z = (minVec.Z < points[i].Z) ? minVec.Z : points[i].Z;

		maxVec.X = (maxVec.X > points[i].X) ? maxVec.X : points[i].X;
		maxVec.Y = (maxVec.Y > points[i].Y) ? maxVec.Y : points[i].Y;
		maxVec.Z = (maxVec.Z > points[i].Z) ? maxVec.Z : points[i].Z;
	}

	return BoundingBox(minVec, maxVec);
}

/// <summary>
///   Create the <see cref="BoundingBox"/> enclosing two other <see cref="BoundingBox"/> instances.
/// </summary>
/// <param name="original">A <see cref="BoundingBox"/> to enclose.</param>
/// <param name="additional">A <see cref="BoundingBox"/> to enclose.</param>
/// <returns>
///   The <see cref="BoundingBox"/> enclosing <paramref name="original"/> and <paramref name="additional"/>.
/// </returns>
BoundingBox BoundingBox::CreateMerged(BoundingBox& original, BoundingBox& additional)
{
	BoundingBox result;
	CreateMerged(original, additional, result);
	return result;
}

/// <summary>
///   Create the <see cref="BoundingBox"/> enclosing two other <see cref="BoundingBox"/> instances.
/// </summary>
/// <param name="original">A <see cref="BoundingBox"/> to enclose.</param>
/// <param name="additional">A <see cref="BoundingBox"/> to enclose.</param>
/// <param name="result">
///   The <see cref="BoundingBox"/> enclosing <paramref name="original"/> and <paramref name="additional"/>.
/// </param>
void BoundingBox::CreateMerged(BoundingBox& original, BoundingBox& additional, BoundingBox& result)
{
	result.Min.X = MathHelper::Min(original.Min.X, additional.Min.X);
	result.Min.Y = MathHelper::Min(original.Min.Y, additional.Min.Y);
	result.Min.Z = MathHelper::Min(original.Min.Z, additional.Min.Z);
	result.Max.X = MathHelper::Max(original.Max.X, additional.Max.X);
	result.Max.Y = MathHelper::Max(original.Max.Y, additional.Max.Y);
	result.Max.Z = MathHelper::Max(original.Max.Z, additional.Max.Z);
}

/// <summary>
///   Get an array of <see cref="Vector3"/> containing the corners of this <see cref="BoundingBox"/>.
/// </summary>
/// <returns>An array of <see cref="Vector3"/> containing the corners of this <see cref="BoundingBox"/>.</returns>
Vector3* BoundingBox::GetCorners()
{
	Vector3 array[8] = {
		  Vector3(this->Min.X, this->Max.Y, this->Max.Z),
		  Vector3(this->Max.X, this->Max.Y, this->Max.Z),
		  Vector3(this->Max.X, this->Min.Y, this->Max.Z),
		  Vector3(this->Min.X, this->Min.Y, this->Max.Z),
		  Vector3(this->Min.X, this->Max.Y, this->Min.Z),
		  Vector3(this->Max.X, this->Max.Y, this->Min.Z),
		  Vector3(this->Max.X, this->Min.Y, this->Min.Z),
		  Vector3(this->Min.X, this->Min.Y, this->Min.Z)
	};
	return array;
}

/// <summary>
///   Fill the first 8 places of an array of <see cref="Vector3"/>
///   with the corners of this <see cref="BoundingBox"/>.
/// </summary>
/// <param name="corners">The array to fill.</param>
/// <exception cref="ArgumentNullException">If <paramref name="corners"/> is <code>null</code>.</exception>
/// <exception cref="ArgumentOutOfRangeException">
///   If <paramref name="corners"/> has a length of less than 8.
/// </exception>
void BoundingBox::GetCorners(Vector3* corners)
{
	corners[0].X = this->Min.X;
	corners[0].Y = this->Max.Y;
	corners[0].Z = this->Max.Z;
	corners[1].X = this->Max.X;
	corners[1].Y = this->Max.Y;
	corners[1].Z = this->Max.Z;
	corners[2].X = this->Max.X;
	corners[2].Y = this->Min.Y;
	corners[2].Z = this->Max.Z;
	corners[3].X = this->Min.X;
	corners[3].Y = this->Min.Y;
	corners[3].Z = this->Max.Z;
	corners[4].X = this->Min.X;
	corners[4].Y = this->Max.Y;
	corners[4].Z = this->Min.Z;
	corners[5].X = this->Max.X;
	corners[5].Y = this->Max.Y;
	corners[5].Z = this->Min.Z;
	corners[6].X = this->Max.X;
	corners[6].Y = this->Min.Y;
	corners[6].Z = this->Min.Z;
	corners[7].X = this->Min.X;
	corners[7].Y = this->Min.Y;
	corners[7].Z = this->Min.Z;
}

/// <summary>
///   Check if this <see cref="BoundingBox"/> intersects another <see cref="BoundingBox"/>.
/// </summary>
/// <param name="box">The <see cref="BoundingBox"/> to test for intersection.</param>
/// <returns>
///   <code>true</code> if this <see cref="BoundingBox"/> intersects <paramref name="box"/>,
///   <code>false</code> if it does not.
/// </returns>
bool BoundingBox::Intersects(BoundingBox& box)
{
	bool result;
	Intersects(box, result);
	return result;
}

/// <summary>
///   Check if this <see cref="BoundingBox"/> intersects another <see cref="BoundingBox"/>.
/// </summary>
/// <param name="box">The <see cref="BoundingBox"/> to test for intersection.</param>
/// <param name="result">
///   <code>true</code> if this <see cref="BoundingBox"/> intersects <paramref name="box"/>,
///   <code>false</code> if it does not.
/// </param>
void BoundingBox::Intersects(BoundingBox& box, bool& result)
{
	if ((this->Max.X >= box.Min.X) && (this->Min.X <= box.Max.X))
	{
		if ((this->Max.Y < box.Min.Y) || (this->Min.Y > box.Max.Y))
		{
			result = false;
			return;
		}

		result = (this->Max.Z >= box.Min.Z) && (this->Min.Z <= box.Max.Z);
		return;
	}

	result = false;
	return;
}

/// <summary>
///   Check if this <see cref="BoundingBox"/> intersects a <see cref="BoundingFrustum"/>.
/// </summary>
/// <param name="sphere">The <see cref="BoundingFrustum"/> to test for intersection.</param>
/// <returns>
///   <code>true</code> if this <see cref="BoundingBox"/> intersects <paramref name="sphere"/>,
///   <code>false</code> if it does not.
/// </returns>
bool BoundingBox::Intersects(BoundingSphere& sphere)
{
	bool result;
	Intersects(sphere, result);
	return result;
}

/// <summary>
///   Check if this <see cref="BoundingBox"/> intersects a <see cref="BoundingFrustum"/>.
/// </summary>
/// <param name="sphere">The <see cref="BoundingFrustum"/> to test for intersection.</param>
/// <param name="result">
///   <code>true</code> if this <see cref="BoundingBox"/> intersects <paramref name="sphere"/>,
///   <code>false</code> if it does not.
/// </param>
void BoundingBox::Intersects(BoundingSphere& sphere, bool& result)
{
	auto squareDistance = 0.0f;
	auto point = sphere.Center;
	if (point.X < Min.X) squareDistance += (Min.X - point.X) * (Min.X - point.X);
	if (point.X > Max.X) squareDistance += (point.X - Max.X) * (point.X - Max.X);
	if (point.Y < Min.Y) squareDistance += (Min.Y - point.Y) * (Min.Y - point.Y);
	if (point.Y > Max.Y) squareDistance += (point.Y - Max.Y) * (point.Y - Max.Y);
	if (point.Z < Min.Z) squareDistance += (Min.Z - point.Z) * (Min.Z - point.Z);
	if (point.Z > Max.Z) squareDistance += (point.Z - Max.Z) * (point.Z - Max.Z);
	result = squareDistance <= sphere.Radius * sphere.Radius;
}

/// <summary>
///   Check if this <see cref="BoundingBox"/> intersects a <see cref="BoundingFrustum"/>.
/// </summary>
/// <param name="sphere">The <see cref="BoundingFrustum"/> to test for intersection.</param>
/// <returns>
///   <code>true</code> if this <see cref="BoundingBox"/> intersects <paramref name="sphere"/>,
///   <code>false</code> if it does not.
/// </returns>
bool BoundingBox::Intersects(BoundingSphere* sphere)
{
	bool result;
	Intersects(*sphere, result);
	return result;
}

/// <summary>
///   Check if this <see cref="BoundingBox"/> intersects a <see cref="BoundingFrustum"/>.
/// </summary>
/// <param name="sphere">The <see cref="BoundingFrustum"/> to test for intersection.</param>
/// <param name="result">
///   <code>true</code> if this <see cref="BoundingBox"/> intersects <paramref name="sphere"/>,
///   <code>false</code> if it does not.
/// </param>
void BoundingBox::Intersects(BoundingSphere* sphere, bool& result)
{
	auto squareDistance = 0.0f;
	auto point = (*sphere).Center;
	if (point.X < Min.X) squareDistance += (Min.X - point.X) * (Min.X - point.X);
	if (point.X > Max.X) squareDistance += (point.X - Max.X) * (point.X - Max.X);
	if (point.Y < Min.Y) squareDistance += (Min.Y - point.Y) * (Min.Y - point.Y);
	if (point.Y > Max.Y) squareDistance += (point.Y - Max.Y) * (point.Y - Max.Y);
	if (point.Z < Min.Z) squareDistance += (Min.Z - point.Z) * (Min.Z - point.Z);
	if (point.Z > Max.Z) squareDistance += (point.Z - Max.Z) * (point.Z - Max.Z);
	result = squareDistance <= (*sphere).Radius * (*sphere).Radius;
}


/// <summary>
///   Check if this <see cref="BoundingBox"/> intersects a <see cref="Plane"/>.
/// </summary>
/// <param name="plane">The <see cref="Plane"/> to test for intersection.</param>
/// <returns>
///   <code>true</code> if this <see cref="BoundingBox"/> intersects <paramref name="plane"/>,
///   <code>false</code> if it does not.
/// </returns>
PlaneIntersectionType BoundingBox::Intersects(Plane& plane)
{
	PlaneIntersectionType result;
	Intersects(plane, result);
	return result;
}

/// <summary>
///   Check if this <see cref="BoundingBox"/> intersects a <see cref="Plane"/>.
/// </summary>
/// <param name="plane">The <see cref="Plane"/> to test for intersection.</param>
/// <param name="result">
///   <code>true</code> if this <see cref="BoundingBox"/> intersects <paramref name="plane"/>,
///   <code>false</code> if it does not.
/// </param>
void BoundingBox::Intersects(Plane& plane, PlaneIntersectionType& result)
{
	// See http://zach.in.tu-clausthal.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/index.html

	Vector3 positiveVertex;
	Vector3 negativeVertex;

	if (plane.Normal.X >= 0)
	{
		positiveVertex.X = this->Max.X;
		negativeVertex.X = Min.X;
	}
	else
	{
		positiveVertex.X = Min.X;
		negativeVertex.X = Max.X;
	}

	if (plane.Normal.Y >= 0)
	{
		positiveVertex.Y = Max.Y;
		negativeVertex.Y = Min.Y;
	}
	else
	{
		positiveVertex.Y = Min.Y;
		negativeVertex.Y = Max.Y;
	}

	if (plane.Normal.Z >= 0)
	{
		positiveVertex.Z = Max.Z;
		negativeVertex.Z = Min.Z;
	}
	else
	{
		positiveVertex.Z = Min.Z;
		negativeVertex.Z = Max.Z;
	}

	// Inline Vector3.Dot(plane.Normal, negativeVertex) + plane.D;
	auto distance = plane.Normal.X * negativeVertex.X + plane.Normal.Y * negativeVertex.Y + plane.Normal.Z * negativeVertex.Z + plane.D;
	if (distance > 0)
	{
		result = PlaneIntersectionType::Front;
		return;
	}

	// Inline Vector3.Dot(plane.Normal, positiveVertex) + plane.D;
	distance = plane.Normal.X * positiveVertex.X + plane.Normal.Y * positiveVertex.Y + plane.Normal.Z * positiveVertex.Z + plane.D;
	if (distance < 0)
	{
		result = PlaneIntersectionType::Back;
		return;
	}

	result = PlaneIntersectionType::Intersecting;
}