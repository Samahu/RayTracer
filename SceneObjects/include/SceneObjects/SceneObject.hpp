#pragma once

#include <memory>

#include <Math/Vector3.hpp>
#include <Math/Ray.hpp>

template <typename T>
class Material;

template <typename T>
struct HitRecord
{
	bool hit;
	T t;
	Vector3<T> p;
	Vector3<T> n;
	std::shared_ptr<Material<T>> m;
};

template <typename T>
class SceneObject
{
public:
	virtual ~SceneObject() {}

	virtual HitRecord<T> HitTest(const Ray<T> ray, T tmin, T tmax) const = 0;

	virtual void SetMaterial(std::shared_ptr<Material<T>> material) = 0;
};