#pragma once

#include <math.h>
#include "SceneObject.hpp"
#include "HitRecord.hpp"

class Sphere : public SceneObject
{
public:
	Sphere() = delete;
	Sphere(Vector3d c, double r) : center(c), radius(r) {}
	HitRecord HitTest(const Ray3d ray, double tmin, double tmax) const override;
	void SetMaterial(std::shared_ptr<Material> material) override { this->material = material; }

private:
	HitRecord computeHitRecord(Ray3d ray, double t) const;

private:
	Vector3d center;
	double radius;
	std::shared_ptr<Material> material;
};

inline HitRecord Sphere::computeHitRecord(Ray3d ray, double t) const
{
	HitRecord hr;
    hr.hit = true;
	hr.t = t;
	hr.p = ray.PointOnRay(t);
	hr.n = (hr.p - center) / radius;
	hr.m = material;
	return hr;
}

inline HitRecord Sphere::HitTest(const Ray3d ray, double tmin, double tmax) const
{
	// Equation: t^2 * dot(b, b) + 2 * t * dot(b, a - c) + dot(a - c, a - c) == R^2
	// where:	c is center, a is ray origin, b is direction
	// in below implementation redundant 2's has been removed since they cancel each other

	auto oc = ray.Origin() - center;
	auto a = Vector3d::dot(ray.Direction(), ray.Direction());
	auto b = Vector3d::dot(ray.Direction(), oc);
	auto c = Vector3d::dot(oc, oc) - radius * radius;
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

	HitRecord hr{ false, 0 };
	return hr;
}
