#pragma once

#include "Vector3.hpp"

template <typename T>
class Ray
{
public:
	Ray()
	{
	}

	Ray(const Vector3<T> origin, const Vector3<T> direction)
		: origin(origin), direction(direction)
	{
	}

	const Vector3<T> Origin() const { return origin; }
	const Vector3<T> Direction() const { return direction; }

	Vector3<T> PointOnRay(T t) const { return origin + t * direction; }

private:
	Vector3<T> origin;
	Vector3<T> direction;
};