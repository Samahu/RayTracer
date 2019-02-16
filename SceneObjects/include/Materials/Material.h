#pragma once

#include <Math/Vector3.hpp>
#include <Math/Ray.hpp>

template <typename T>
class Material
{
public:
	virtual bool scatter(const Ray<T> &ray_in, const HitRecord<T>& hitRecord, Vector3<T>& attenuation, Ray<T>& scattered) const = 0;

protected:
	Vector3<T> random_in_unit_sphere() const;
};

#include "Material.inl"