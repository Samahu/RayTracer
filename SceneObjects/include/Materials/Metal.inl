#pragma once

template <typename T>
bool Metal<T>::scatter(const Ray<T> &ray_in, const HitRecord<T>& hr, Vector3<T>& attenuation, Ray<T>& scattered) const
{
	auto in_dir = ray_in.Direction();
	in_dir.Normalize();

	auto reflected = reflect(in_dir, hr.n);
	scattered = Ray<T>(hr.p, reflected + fuzz * random_in_unit_sphere());
	attenuation = albedo;
	return (Vector3<T>::dot(scattered.Direction(), hr.n) > 0);
}