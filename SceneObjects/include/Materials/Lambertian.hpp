#pragma once

#include "Material.hpp"

class Lambertian : public Material
{
public:
	Lambertian(const Vector3d albedo)
		: albedo(albedo)
	{

	}

	bool scatter(const Ray3d &ray_in, const HitRecord& hitRecord, Vector3d& attenuation, Ray3d& scattered) const override;

private:
	Vector3d albedo;
};