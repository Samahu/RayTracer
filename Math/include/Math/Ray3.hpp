#pragma once

#include "Vector3.hpp"

template <typename T>
class Ray3
{
public:
	Ray3()
	{
	}

	Ray3(const Vector3<T> origin, const Vector3<T> direction)
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

typedef Ray3<float> Ray3f;
typedef Ray3<double> Ray3d;