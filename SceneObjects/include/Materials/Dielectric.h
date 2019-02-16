#pragma once
#pragma once

#include "Material.h"

template <typename T>
class Dielectric : public Material<T>
{
public:
	Dielectric(T refractiveIndex)
		: refractiveIndex(refractiveIndex)
	{

	}

	bool scatter(const Ray<T> &ray_in, const HitRecord<T>& hitRecord, Vector3<T>& attenuation, Ray<T>& scattered) const override;

private:
	Vector3<T> reflect(const Vector3<T>& v, const Vector3<T> n) const
	{
		return v - 2.0f * Vector3<T>::dot(v, n) * n;
	}

	bool refract(const Vector3<T>& v, const Vector3<T> n, T ni_over_nt, Vector3<T>& refracted) const
	{
		auto uv = v;
		uv.Normalize();
		auto dt = Vector3<T>::dot(uv, n);
		auto d = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);

		if (d > 0)
		{
			refracted = ni_over_nt * (uv - n * dt) - n * sqrt(d);
			return true;
		}

		return false;
	}

	T schlick(T cosine, T refractiveIndex) const
	{
		T r0 = (1.0f - refractiveIndex) / (1.0f + refractiveIndex);
		r0 = r0 * r0;
		return r0 + (1.0f - r0)*pow(static_cast<T>(1 - cosine), static_cast<T>(5.0));
	}

private:
	T refractiveIndex;
};

#include "Dielectric.inl"