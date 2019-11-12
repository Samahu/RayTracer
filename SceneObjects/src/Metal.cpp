#include "Materials/Metal.hpp"
#include "SceneObjects/HitRecord.hpp"

bool Metal::scatter(const Ray3d &ray_in, const HitRecord& hr, Vector3d& attenuation, Ray3d& scattered) const
{
	auto in_dir = ray_in.Direction();
	in_dir.Normalize();

	auto reflected = reflect(in_dir, hr.n);
	scattered = Ray3d(hr.p, reflected + fuzz * random_in_unit_sphere());
	attenuation = albedo;
	return (Vector3d::dot(scattered.Direction(), hr.n) > 0);
}