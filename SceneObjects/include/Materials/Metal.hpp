#pragma once

#include "Material.hpp"

class Metal : public Material
{
public:
	Metal(const Vector3d albedo, double fuzz)
		: albedo(albedo), fuzz(fuzz)
	{

	}

	bool scatter(const Ray3d& ray_in, const HitRecord& hitRecord, Vector3d& attenuation, Ray3d& scattered) const override;

private:
	Vector3d reflect(const Vector3d v, const Vector3d n) const
	{
		return v - 2.0f * Vector3d::dot(v, n) * n;
	}

private:
	Vector3d albedo;
	double fuzz;
};