#pragma once

#include <vector>

#include <Math/Vector3.hpp>
#include <Math/Ray3.hpp>
#include <SceneObjects/SceneObject.hpp>
#include <SceneObjects/CompositeSceneObject.hpp>

class SimpleRT
{
private:
	Vector3d random_in_unit_sphere() const;
	Vector3d color(const Ray3d ray, const CompositeSceneObject& world, int depth) const;

public:
	std::vector<Vector3i> Render(int w, int h, const CompositeSceneObject& world);
};