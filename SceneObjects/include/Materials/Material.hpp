#pragma once

#include <Math/Vector3.hpp>
#include <Math/Ray3.hpp>

struct HitRecord;

class Material
{
public:
	virtual bool scatter(const Ray3d &ray_in, const HitRecord& hitRecord, Vector3d& attenuation, Ray3d& scattered) const = 0;

protected:
	Vector3d random_in_unit_sphere() const;
};