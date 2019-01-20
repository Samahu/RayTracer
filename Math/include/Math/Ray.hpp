#pragma once

#include "Vector3.hpp"

template <class T>
class Ray
{
	Vector3<T> origin;
	Vector3<T> direction;

public:
	Ray(const Vector3<T> origin, const Vector3<T> direction)
		: origin(origin), direction(direction)
	{
	}

	const Vector3<T> Origin() const { return origin; }
	const Vector3<T> Direction() const { return direction; }

	Vector3<T> PointOnRay(T t) const { return origin + t * direction; }

};