#include "Plane.h" 


Plane::Plane(Vector4 value)
	: Plane(Vector3(value.X, value.Y, value.Z), value.W)
{
}

Plane::Plane(Vector3 normal, float d)
	: Normal(normal), D(d)
{
}

Plane::Plane(Vector3 a, Vector3 b, Vector3 c)
{
	Vector3 ab = b - a;
	Vector3 ac = c - a;

	Vector3 cross = Vector3::Cross(ab, ac);
	Vector3::Normalize(cross, Normal);
	D = -(Vector3::Dot(Normal, a));
}

Plane::Plane(float a, float b, float c, float d)
	: Plane(Vector3(a, b, c), d)
{
}

Plane::Plane(Vector3 pointOnPlane, Vector3 normal)
	: Normal(normal)
{
	D = -(
		pointOnPlane.X * normal.X +
		pointOnPlane.Y * normal.Y +
		pointOnPlane.Z * normal.Z
		);
}

float Plane::Dot(Vector4 value)
{
	return ((((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z)) + (D * value.W));
}

void Plane::Dot(Vector4& value, float& result)
{
	result = (((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z)) + (D * value.W);
}

float Plane::DotCoordinate(Vector3 value)
{
	return ((((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z)) + D);
}

void Plane::DotCoordinate(Vector3& value, float& result)
{
	result = (((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z)) + D;
}

float Plane::DotNormal(Vector3 value)
{
	return (((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z));
}

void Plane::DotNormal(Vector3& value, float& result)
{
	result = ((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z);
}

Plane Plane::Transform(Plane plane, Matrix matrix)
{
	Plane result;
	Transform(plane, matrix, result);
	return result;
}

void Plane::Transform(Plane& plane, Matrix& matrix, Plane& result)
{
	Matrix transformedMatrix;
	Matrix::Invert(matrix, transformedMatrix);
	Matrix::Transpose(transformedMatrix, transformedMatrix);

	Vector4 vector(plane.Normal, plane.D);

	Vector4 transformedVector;
	Vector4::Transform(vector, transformedMatrix, transformedVector);

	result = Plane(transformedVector);
}

Plane Plane::Transform(Plane plane, Quaternion rotation)
{
	Plane result;
	Transform(plane, rotation, result);
	return result;
}

void Plane::Transform(Plane& plane, Quaternion& rotation, Plane& result)
{
	Vector3::Transform(plane.Normal, rotation, result.Normal);
	result.D = plane.D;
}

void Plane::Normalize()
{
	float length = Vector3::Length(Normal);
	float factor = 1.0f / length;
	Vector3::Multiply(Normal, factor, Normal);
	D = D * factor;
}

Plane Plane::Normalize(Plane value)
{
	Plane ret;
	Normalize(value, ret);
	return ret;
}

void Plane::Normalize(Plane& value, Plane& result)
{
	float length = Vector3::Length(value.Normal);
	float factor = 1.0f / length;
	Vector3::Multiply(value.Normal, factor, result.Normal);
	result.D = value.D * factor;
}

bool Plane::operator!=(Plane& other)
{
	return !Equals(other);
}

bool Plane::operator==(Plane& other)
{
	return Equals(other);
}

bool Plane::Equals(Plane& other)
{
	return (Normal == other.Normal) && (D == other.D);
}

int Plane::GetHashCode()
{
	return 0; //Normal.GetHashCode() ^ std::hash<float>{}(D);
}

PlaneIntersectionType Plane::Intersects(BoundingBox box)
{
	return box.Intersects(*this);
}

void Plane::Intersects(BoundingBox& box, PlaneIntersectionType& result)
{
	box.Intersects(*this, result);
}

PlaneIntersectionType Plane::Intersects(BoundingFrustum frustum)
{
	return frustum.Intersects(*this);
}

PlaneIntersectionType Plane::Intersects(BoundingSphere sphere)
{
	return sphere.Intersects(*this);
}

void Plane::Intersects(BoundingSphere& sphere, PlaneIntersectionType& result)
{
	sphere.Intersects(*this, result);
}

PlaneIntersectionType Plane::Intersects(Vector3& point)
{
	float distance;
	DotCoordinate(point, distance);

	if (distance > 0)
		return PlaneIntersectionType::Front;

	if (distance < 0)
		return PlaneIntersectionType::Back;

	return PlaneIntersectionType::Intersecting;
}

void Plane::Deconstruct(Vector3& normal, float& d)
{
	normal = Normal;
	d = D;
}

/// <summary>
/// Returns a value indicating what side (positive/negative) of a plane a point is
/// </summary>
/// <param name="point">The point to check with</param>
/// <param name="plane">The plane to check against</param>
/// <returns>Greater than zero if on the positive side, less than zero if on the negative size, 0 otherwise</returns>
float Plane::ClassifyPoint(Vector3& point, Plane& plane)
{
	return point.X * plane.Normal.X + point.Y * plane.Normal.Y + point.Z * plane.Normal.Z + plane.D;
}

/// <summary>
/// Returns the perpendicular distance from a point to a plane
/// </summary>
/// <param name="point">The point to check</param>
/// <param name="plane">The place to check</param>
/// <returns>The perpendicular distance from the point to the plane</returns>
float Plane::PerpendicularDistance(Vector3& point, Plane& plane)
{
	// dist = (ax + by + cz + d) / sqrt(a*a + b*b + c*c)
	return (float)abs((plane.Normal.X * point.X + plane.Normal.Y * point.Y + plane.Normal.Z * point.Z)
		/ sqrt(plane.Normal.X * plane.Normal.X + plane.Normal.Y * plane.Normal.Y + plane.Normal.Z * plane.Normal.Z));
}
