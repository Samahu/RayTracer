#include "Materials/Material.hpp"
#include <random>
#include "SceneObjects/HitRecord.hpp"

Vector3d Material::random_in_unit_sphere() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> urd(0.0, 1.0);

	Vector3d p;

	do
	{
		p = 2.0 * Vector3d(urd(gen), urd(gen), urd(gen)) - Vector3d::One;
	} while (p.SquaredLength() >= 1.0);

	return p;
}