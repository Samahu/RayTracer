#pragma once

#include "Material.h"

template <typename T>
class Lambertian : public Material<T>
{
public:
	Lambertian(const Vector3<T> albedo)
		: albedo(albedo)
	{

	}

	bool scatter(const Ray<T> &ray_in, const HitRecord<T>& hitRecord, Vector3<T>& attenuation, Ray<T>& scattered) const override;

private:
	Vector3<T> albedo;
};

#include "Lambertian.inl"