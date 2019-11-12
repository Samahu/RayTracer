#pragma once

#include "Material.hpp"

class Dielectric : public Material
{
public:
	Dielectric(double refractiveIndex)
		: refractiveIndex(refractiveIndex)
	{

	}

	bool scatter(const Ray3d &ray_in, const HitRecord& hitRecord, Vector3d& attenuation, Ray3d& scattered) const override;

private:
	Vector3d reflect(const Vector3d& v, const Vector3d n) const;
	bool refract(const Vector3d& v, const Vector3d n, double ni_over_nt, Vector3d& refracted) const;
	double schlick(double cosine, double refractiveIndex) const;

private:
	double refractiveIndex;
};