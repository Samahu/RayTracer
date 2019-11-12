#pragma once

#include <memory>

#include <Math/Vector3.hpp>
#include <Math/Ray3.hpp>

class Material;
struct HitRecord;

class SceneObject
{
public:
	virtual ~SceneObject() {}

	virtual HitRecord HitTest(const Ray3d ray, double tmin, double tmax) const = 0;

	virtual void SetMaterial(std::shared_ptr<Material> material) = 0;
};