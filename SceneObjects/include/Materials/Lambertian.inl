#pragma once

template <typename T>
bool Lambertian<T>::scatter(const Ray<T> &ray_in, const HitRecord<T>& hr, Vector3<T>& attenuation, Ray<T>& scattered) const
{
	auto target = hr.p + hr.n + random_in_unit_sphere();
	scattered = Ray<T>(hr.p, target - hr.p);
	attenuation = albedo;
	return true;
}