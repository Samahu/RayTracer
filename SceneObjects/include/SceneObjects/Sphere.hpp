#pragma once

#include <math.h>
#include "SceneObject.hpp"

template <typename T>
class Sphere : public SceneObject<T>
{
public:
	Sphere() = delete;
	Sphere(Vector3<T> c, T r) : center(c), radius(r) {}
	HitRecord<T> HitTest(const Ray<T> ray, T tmin, T tmax) const override;
	void SetMaterial(std::shared_ptr<Material<T>> material) override { this->material = material; }

private:
	HitRecord<T> computeHitRecord(Ray<T> ray, T t) const;

private:
	Vector3<T> center;
	T radius;
	std::shared_ptr<Material<T>> material;
};

template<typename T>
inline HitRecord<T> Sphere<T>::computeHitRecord(Ray<T> ray, T t) const
{
	HitRecord<T> hr;
    hr.hit = true;
	hr.t = t;
	hr.p = ray.PointOnRay(t);
	hr.n = (hr.p - center) / radius;
	hr.m = material;
	return hr;
}

template<typename T>
inline HitRecord<T> Sphere<T>::HitTest(const Ray<T> ray, T tmin, T tmax) const
{
	// Equation: t^2 * dot(b, b) + 2 * t * dot(b, a - c) + dot(a - c, a - c) == R^2
	// where:	c is center, a is ray origin, b is direction
	// in below implementation redundant 2's has been removed since they cancel each other

	auto oc = ray.Origin() - center;
	auto a = Vector3<T>::dot(ray.Direction(), ray.Direction());
	auto b = Vector3<T>::dot(ray.Direction(), oc);
	auto c = Vector3<T>::dot(oc, oc) - radius * radius;
	auto delta = b * b - a * c;

	if (delta > 0)
	{
		auto temp = (-b - sqrt(delta)) / a;
		if (temp > tmin && temp < tmax)
			return computeHitRecord(ray, temp);
        
        temp = (-b + sqrt(delta)) / a;
        if (temp > tmin && temp < tmax)
            return computeHitRecord(ray, temp);
    }

	HitRecord<T> hr{ false, 0 };
	return hr;
}
