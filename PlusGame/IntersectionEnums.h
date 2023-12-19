#pragma once

enum PlaneIntersectionType
{
	/// <summary>
	/// There is no intersection, the bounding volume is in the negative half space of the plane.
	/// </summary>
	Front,
	/// <summary>
	/// There is no intersection, the bounding volume is in the positive half space of the plane.
	/// </summary>
	Back,
	/// <summary>
	/// The plane is intersected.
	/// </summary>
	Intersecting
};

enum ContainmentType
{
	/// <summary>
	/// Indicates that there is no overlap between two bounding volumes.
	/// </summary>
	Disjoint,
	/// <summary>
	/// Indicates that one bounding volume completely contains another volume.
	/// </summary>
	Contains,
	/// <summary>
	/// Indicates that bounding volumes partially overlap one another.
	/// </summary>
	Intersects
};