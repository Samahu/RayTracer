#include "Materials/Lambertian.hpp"
#include "SceneObjects/HitRecord.hpp"

bool Lambertian::scatter(const Ray3d& ray_in, const HitRecord& hr, Vector3d& attenuation, Ray3d& scattered) const
{
	auto target = hr.p + hr.n + random_in_unit_sphere();
	scattered = Ray3d(hr.p, target - hr.p);
	attenuation = albedo;
	return true;
}