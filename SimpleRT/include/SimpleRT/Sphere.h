#pragma once

#include <Math/Vector3.hpp>
#include <Math/Ray.hpp>

template <class T>
struct HitRecord
{
	T t;
	Vector3<T> p;
	Vector3<T> n;
};

template <class T>
class Object
{
public:
	virtual bool HitTest(const Ray<T> ray, T tmin, T tmax, HitRecord<T> & hitRecord) const = 0;
};

template <class T>
class Sphere : public Object<T>
{
private:
	Vector3<T> center;
	T radius;

public:
	Sphere() = delete;
	Sphere(Vector3<T> c, T r) : center(c), radius(r) {}
	bool HitTest(const Ray<T> ray, T tmin, T tmax, HitRecord<T> & hitRecord) const override;
};

template<class T>
inline bool Sphere<T>::HitTest(const Ray<T> ray, T tmin, T tmax, HitRecord<T>& hitRecord) const
{
	// Equation: t^2 * dot(b, b) + 2 * t * dot(b, a - c) + dot(a - c, a - c) == R^2
	// where:	c is center, a is ray origin, b is direction

	auto oc = ray.Origin() - center;
	auto a = Vector3<T>::dot(ray.Direction(), ray.Direction());
	auto b = 2 * Vector3<T>::dot(ray.Direction(), oc);
	auto c = Vector3<T>::dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;

	hitRecord.t = discriminant < 0 ? -1 : (-b - sqrt(discriminant)) / (2 * a);

	return (hitRecord.t > 0);
}
