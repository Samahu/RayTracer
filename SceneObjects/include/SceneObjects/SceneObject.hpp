#pragma once

#include <memory>

#include <Math/Vector3.hpp>
#include <Math/Ray.hpp>

template <typename T>
struct HitRecord
{
	bool hit;
	T t;
	Vector3<T> p;
	Vector3<T> n;
};

template <typename T>
class SceneObject
{
public:
	virtual ~SceneObject() {}

	virtual HitRecord<T> HitTest(const Ray<T> ray, T tmin, T tmax) const = 0;
};