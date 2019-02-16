#pragma once

#include <random>

template <typename T>
bool Dielectric<T>::scatter(const Ray<T> &ray_in, const HitRecord<T>& hr, Vector3<T>& attenuation, Ray<T>& scattered) const
{
	Vector3<T> outward_n;

	auto in_dir = ray_in.Direction();

	auto reflected = reflect(in_dir, hr.n);
	attenuation = Vector3<T>{ 1.0f, 1.0f, 1.0f };

	T ni_over_nt;
	T reflect_prob;
	T cosine;

	if (Vector3<T>::dot(in_dir, hr.n) > 0)
	{
		outward_n = -hr.n;
		ni_over_nt = refractiveIndex;
		cosine = refractiveIndex * Vector3<T>::dot(in_dir, hr.n) / in_dir.Length();
	}
	else
	{
		outward_n = hr.n;
		ni_over_nt = 1.0f / refractiveIndex;
		cosine = -Vector3<T>::dot(in_dir, hr.n) / in_dir.Length();
	}

	Vector3<T> refracted;
	if (refract(ray_in.Direction(), outward_n, ni_over_nt, refracted))
	{
		reflect_prob = schlick(cosine, refractiveIndex);
	}
	else
	{
		reflect_prob = 1.0f;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<T> urd(0.0, 1.0);

	if (urd(gen) < reflect_prob)
	{
		scattered = Ray<T>(hr.p, reflected);
	}
	else
	{
		scattered = Ray<T>(hr.p, refracted);
	}

	return true;
}