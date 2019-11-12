#pragma once

#include <memory>

class Material;

struct HitRecord
{
	bool hit;
	double t;
	Vector3d p;
	Vector3d n;
	std::shared_ptr<Material> m;
};