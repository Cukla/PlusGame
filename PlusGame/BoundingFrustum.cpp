#include "BoundingFrustum.h"

BoundingFrustum::BoundingFrustum(Matrix& value)
{
	_matrix = value;
	CreatePlanes();
	CreateCorners();
}

Matrix BoundingFrustum::GetMatrix()
{
	return _matrix;
}

void BoundingFrustum::SetMatrix(Matrix& value)
{
	_matrix = value;
	CreatePlanes();
	CreateCorners();
}

Plane BoundingFrustum::GetNear()
{
	return _planes[0];
}

Plane BoundingFrustum::GetFar()
{
	return _planes[1];
}

Plane BoundingFrustum::GetLeft()
{
	return _planes[2];
}

Plane BoundingFrustum::GetRight()
{
	return _planes[3];
}

Plane BoundingFrustum::GetTop()
{
	return _planes[4];
}

Plane BoundingFrustum::GetBottom()
{
	return _planes[5];
}


/// <summary>
/// Containment test between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingBox"/>.
/// </summary>
/// <param name="box">A <see cref="BoundingBox"/> for testing.</param>
/// <returns>Result of testing for containment between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingBox"/>.</returns>
ContainmentType BoundingFrustum::Contains(BoundingBox& box)
{
	auto result = ContainmentType::Disjoint;
	this->Contains(box, result);
	return result;
}

/// <summary>
/// Containment test between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingBox"/>.
/// </summary>
/// <param name="box">A <see cref="BoundingBox"/> for testing.</param>
/// <param name="result">Result of testing for containment between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingBox"/> as an output parameter.</param>
void BoundingFrustum::Contains(BoundingBox& box, ContainmentType& result)
{
	auto intersects = false;
	for (auto i = 0; i < PlaneCount; ++i)
	{
		auto planeIntersectionType = PlaneIntersectionType::Front;
		box.Intersects(this->_planes[i], planeIntersectionType);
		switch (planeIntersectionType)
		{
		case PlaneIntersectionType::Front:
			result = ContainmentType::Disjoint;
			return;
		case PlaneIntersectionType::Intersecting:
			intersects = true;
			break;
		}
	}
	result = intersects ? ContainmentType::Intersects : ContainmentType::Contains;
}

/// <summary>
/// Containment test between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingFrustum"/>.
/// </summary>
/// <param name="frustum">A <see cref="BoundingFrustum"/> for testing.</param>
/// <returns>Result of testing for containment between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingFrustum"/>.</returns>
ContainmentType BoundingFrustum::Contains(BoundingFrustum& frustum)
{
	if (*this == frustum)                // We check to see if the two frustums are equal
		return ContainmentType::Contains;// If they are, there's no need to go any further.

	auto intersects = false;
	for (auto i = 0; i < PlaneCount; ++i)
	{
		PlaneIntersectionType planeIntersectionType;
		frustum.Intersects(_planes[i], planeIntersectionType);
		switch (planeIntersectionType)
		{
		case PlaneIntersectionType::Front:
			return ContainmentType::Disjoint;
		case PlaneIntersectionType::Intersecting:
			intersects = true;
			break;
		}
	}
	return intersects ? ContainmentType::Intersects : ContainmentType::Contains;
}

/// <summary>
/// Containment test between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingSphere"/>.
/// </summary>
/// <param name="sphere">A <see cref="BoundingSphere"/> for testing.</param>
/// <returns>Result of testing for containment between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingSphere"/>.</returns>
ContainmentType BoundingFrustum::Contains(BoundingSphere& sphere)
{
	auto result = ContainmentType::Disjoint;
	this->Contains(sphere, result);
	return result;
}

/// <summary>
/// Containment test between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingSphere"/>.
/// </summary>
/// <param name="sphere">A <see cref="BoundingSphere"/> for testing.</param>
/// <param name="result">Result of testing for containment between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingSphere"/> as an output parameter.</param>
void BoundingFrustum::Contains(BoundingSphere& sphere, ContainmentType& result)
{
	auto intersects = false;
	for (auto i = 0; i < PlaneCount; ++i)
	{
		auto planeIntersectionType = PlaneIntersectionType::Front;

		// TODO: we might want to inline this for performance reasons
		sphere.Intersects(this->_planes[i], planeIntersectionType);
		switch (planeIntersectionType)
		{
		case PlaneIntersectionType::Front:
			result = ContainmentType::Disjoint;
			return;
		case PlaneIntersectionType::Intersecting:
			intersects = true;
			break;
		}
	}
	result = intersects ? ContainmentType::Intersects : ContainmentType::Contains;
}

/// <summary>
/// Containment test between this <see cref="BoundingFrustum"/> and specified <see cref="Vector3"/>.
/// </summary>
/// <param name="point">A <see cref="Vector3"/> for testing.</param>
/// <returns>Result of testing for containment between this <see cref="BoundingFrustum"/> and specified <see cref="Vector3"/>.</returns>
ContainmentType BoundingFrustum::Contains(Vector3 point)
{
	auto result = ContainmentType::Disjoint;
	this->Contains(point, result);
	return result;
}

/// <summary>
/// Containment test between this <see cref="BoundingFrustum"/> and specified <see cref="Vector3"/>.
/// </summary>
/// <param name="point">A <see cref="Vector3"/> for testing.</param>
/// <param name="result">Result of testing for containment between this <see cref="BoundingFrustum"/> and specified <see cref="Vector3"/> as an output parameter.</param>
void BoundingFrustum::Contains(Vector3& point, ContainmentType& result)
{
	for (auto i = 0; i < PlaneCount; ++i)
	{
		// TODO: we might want to inline this for performance reasons
		if (Plane::ClassifyPoint(point, this->_planes[i]) > 0)
		{
			result = ContainmentType::Disjoint;
			return;
		}
	}
	result = ContainmentType::Contains;
}

bool BoundingFrustum::Intersects(BoundingBox& box)
{
	ContainmentType containment = Contains(box);
	return containment == ContainmentType::Intersects || containment == ContainmentType::Contains;
}

bool BoundingFrustum::Intersects(BoundingFrustum& frustum)
{
	ContainmentType containment = Contains(frustum);
	return containment == ContainmentType::Intersects || containment == ContainmentType::Contains;
}

bool BoundingFrustum::Intersects(BoundingSphere& sphere)
{
	ContainmentType containment = Contains(sphere);
	return containment == ContainmentType::Intersects || containment == ContainmentType::Contains;
}

/// <summary>
/// Gets type of intersection between specified <see cref="Plane"/> and this <see cref="BoundingFrustum"/>.
/// </summary>
/// <param name="plane">A <see cref="Plane"/> for intersection test.</param>
/// <returns>A plane intersection type.</returns>
PlaneIntersectionType BoundingFrustum::Intersects(Plane& plane)
{
	PlaneIntersectionType result;
	Intersects(plane, result);
	return result;
}

/// <summary>
/// Gets type of intersection between specified <see cref="Plane"/> and this <see cref="BoundingFrustum"/>.
/// </summary>
/// <param name="plane">A <see cref="Plane"/> for intersection test.</param>
/// <param name="result">A plane intersection type as an output parameter.</param>
void BoundingFrustum::Intersects(Plane& plane, PlaneIntersectionType& result)
{
	int cornersLenght = sizeof(_corners) / sizeof(_corners[0]);
	result = plane.Intersects(_corners[0]);
	for (int i = 1; i < cornersLenght; i++)
		if (plane.Intersects(_corners[i]) != result)
			result = PlaneIntersectionType::Intersecting;
}

///<summary>
/// Gets the distance of intersection of <see cref="Ray"/> and this <see cref="BoundingFrustum"/> or null if no intersection happens.
/// </summary>
/// <param name="ray">A <see cref="Ray"/> for intersection test.</param>
/// <returns>Distance at which ray intersects with this <see cref="BoundingFrustum"/> or null if no intersection happens.</returns>
float BoundingFrustum::Intersects(Ray& ray)
{
	float result;
	Intersects(ray, result);
	return result;
}

/// <summary>
/// Gets the distance of intersection of <see cref="Ray"/> and this <see cref="BoundingFrustum"/> or null if no intersection happens.
/// </summary>
/// <param name="ray">A <see cref="Ray"/> for intersection test.</param>
/// <param name="result">Distance at which ray intersects with this <see cref="BoundingFrustum"/> or null if no intersection happens as an output parameter.</param>
void BoundingFrustum::Intersects(Ray& ray, float& result)
{
	ContainmentType ctype;
	this->Contains(ray.Position, ctype);

	switch (ctype)
	{
	case ContainmentType::Disjoint:
		result = std::numeric_limits<float>::quiet_NaN();
		return;
	case ContainmentType::Contains:
		result = 0.0f;
		return;
	case ContainmentType::Intersects:
		result = 0.0f;
	default:
		result = 0.0f;
	}
}

Vector3* BoundingFrustum::GetCorners()
{
	return (Vector3*)_corners;
}

bool BoundingFrustum::operator==(BoundingFrustum& other)
{
	return _matrix == other._matrix;
}

bool BoundingFrustum::operator!=(BoundingFrustum& other)
{
	return !(*this == other);
}

void BoundingFrustum::CreateCorners()
{
	IntersectionPoint(this->_planes[0], this->_planes[2], this->_planes[4], this->_corners[0]);
	IntersectionPoint(this->_planes[0], this->_planes[3], this->_planes[4], this->_corners[1]);
	IntersectionPoint(this->_planes[0], this->_planes[3], this->_planes[5], this->_corners[2]);
	IntersectionPoint(this->_planes[0], this->_planes[2], this->_planes[5], this->_corners[3]);
	IntersectionPoint(this->_planes[1], this->_planes[2], this->_planes[4], this->_corners[4]);
	IntersectionPoint(this->_planes[1], this->_planes[3], this->_planes[4], this->_corners[5]);
	IntersectionPoint(this->_planes[1], this->_planes[3], this->_planes[5], this->_corners[6]);
	IntersectionPoint(this->_planes[1], this->_planes[2], this->_planes[5], this->_corners[7]);
}

void BoundingFrustum::CreatePlanes()
{
	this->_planes[0] = Plane(-this->_matrix.M13, -this->_matrix.M23, -this->_matrix.M33, -this->_matrix.M43);
	this->_planes[1] = Plane(this->_matrix.M13 - this->_matrix.M14, this->_matrix.M23 - this->_matrix.M24, this->_matrix.M33 - this->_matrix.M34, this->_matrix.M43 - this->_matrix.M44);
	this->_planes[2] = Plane(-this->_matrix.M14 - this->_matrix.M11, -this->_matrix.M24 - this->_matrix.M21, -this->_matrix.M34 - this->_matrix.M31, -this->_matrix.M44 - this->_matrix.M41);
	this->_planes[3] = Plane(this->_matrix.M11 - this->_matrix.M14, this->_matrix.M21 - this->_matrix.M24, this->_matrix.M31 - this->_matrix.M34, this->_matrix.M41 - this->_matrix.M44);
	this->_planes[4] = Plane(this->_matrix.M12 - this->_matrix.M14, this->_matrix.M22 - this->_matrix.M24, this->_matrix.M32 - this->_matrix.M34, this->_matrix.M42 - this->_matrix.M44);
	this->_planes[5] = Plane(-this->_matrix.M14 - this->_matrix.M12, -this->_matrix.M24 - this->_matrix.M22, -this->_matrix.M34 - this->_matrix.M32, -this->_matrix.M44 - this->_matrix.M42);

	this->NormalizePlane(this->_planes[0]);
	this->NormalizePlane(this->_planes[1]);
	this->NormalizePlane(this->_planes[2]);
	this->NormalizePlane(this->_planes[3]);
	this->NormalizePlane(this->_planes[4]);
	this->NormalizePlane(this->_planes[5]);
}

void BoundingFrustum::IntersectionPoint(Plane& a, Plane& b, Plane& c, Vector3& result)
{
	// Formula used
	//                d1 ( N2 * N3 ) + d2 ( N3 * N1 ) + d3 ( N1 * N2 )
	//P =   -------------------------------------------------------------------------
	//                             N1 . ( N2 * N3 )
	//
	// Note: N refers to the normal, d refers to the displacement. '.' means dot product. '*' means cross product

	Vector3 v1, v2, v3;
	Vector3 cross;

	Vector3::Cross(b.Normal, c.Normal, cross);

	float f;
	Vector3::Dot(a.Normal, cross, f);
	f *= -1.0f;

	Vector3::Cross(b.Normal, c.Normal, cross);
	Vector3::Multiply(cross, a.D, v1);
	//v1 = (a.D * (Vector3.Cross(b.Normal, c.Normal)));


	Vector3::Cross(c.Normal, a.Normal, cross);
	Vector3::Multiply(cross, b.D, v2);
	//v2 = (b.D * (Vector3.Cross(c.Normal, a.Normal)));


	Vector3::Cross(a.Normal, b.Normal, cross);
	Vector3::Multiply(cross, c.D, v3);
	//v3 = (c.D * (Vector3.Cross(a.Normal, b.Normal)));

	result.X = (v1.X + v2.X + v3.X) / f;
	result.Y = (v1.Y + v2.Y + v3.Y) / f;
	result.Z = (v1.Z + v2.Z + v3.Z) / f;
}

void BoundingFrustum::NormalizePlane(Plane& p)
{
	float factor = 1.0f / Vector3::Length(p.Normal);
	p.Normal.X *= factor;
	p.Normal.Y *= factor;
	p.Normal.Z *= factor;
	p.D *= factor;
}
