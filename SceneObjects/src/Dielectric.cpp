#include "Materials/Dielectric.hpp"
#include <random>
#include "SceneObjects/HitRecord.hpp"

bool Dielectric::scatter(const Ray3d &ray_in, const HitRecord& hr, Vector3d& attenuation, Ray3d& scattered) const
{
	Vector3d outward_n;

	auto in_dir = ray_in.Direction();

	auto reflected = reflect(in_dir, hr.n);
	attenuation = Vector3d{ 1.0, 1.0, 1.0 };

	double ni_over_nt;
	double reflect_prob;
	double cosine;

	if (Vector3d::dot(in_dir, hr.n) > 0)
	{
		outward_n = -hr.n;
		ni_over_nt = refractiveIndex;
		cosine = refractiveIndex * Vector3d::dot(in_dir, hr.n) / in_dir.Length();
	}
	else
	{
		outward_n = hr.n;
		ni_over_nt = 1.0f / refractiveIndex;
		cosine = -Vector3d::dot(in_dir, hr.n) / in_dir.Length();
	}

	Vector3d refracted;
	if (refract(ray_in.Direction(), outward_n, ni_over_nt, refracted))
	{
		reflect_prob = schlick(cosine, refractiveIndex);
	}
	else
	{
		reflect_prob = 1.0;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> urd(0.0, 1.0);

	if (urd(gen) < reflect_prob)
	{
		scattered = Ray3d(hr.p, reflected);
	}
	else
	{
		scattered = Ray3d(hr.p, refracted);
	}

	return true;
}

Vector3d Dielectric::reflect(const Vector3d& v, const Vector3d n) const
{
	return v - 2.0 * Vector3d::dot(v, n) * n;
}

bool Dielectric::refract(const Vector3d& v, const Vector3d n, double ni_over_nt, Vector3d& refracted) const
{
	auto uv = v;
	uv.Normalize();
	auto dt = Vector3d::dot(uv, n);
	auto d = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);

	if (d > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(d);
		return true;
	}

	return false;
}

double Dielectric::schlick(double cosine, double refractiveIndex) const
{
	auto r0 = (1.0 - refractiveIndex) / (1.0 + refractiveIndex);
	r0 = r0 * r0;
	return r0 + (1.0 - r0) * pow(1 - cosine, 5.0);
}