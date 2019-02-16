#pragma once

#include "Material.h"

template <typename T>
class Metal : public Material<T>
{
public:
	Metal(const Vector3<T> albedo, T fuzz)
		: albedo(albedo), fuzz(fuzz)
	{

	}

	bool scatter(const Ray<T> &ray_in, const HitRecord<T>& hitRecord, Vector3<T>& attenuation, Ray<T>& scattered) const override;

private:
	Vector3<T> reflect(const Vector3<T>& v, const Vector3<T> n) const
	{
		return v - 2.0f * Vector3<T>::dot(v, n) * n;
	}

private:
	Vector3<T> albedo;
	T fuzz;
};

#include "Metal.inl"