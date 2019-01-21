#pragma once

#include <vector>

#include <Math/Vector3.hpp>
#include <Math/Ray.hpp>
#include <SceneObjects/SceneObject.hpp>
#include <SceneObjects/CompositeSceneObject.hpp>

template <typename T>
class SimpleRT
{
private:
	Vector3<T> color(const Ray<T> ray, const CompositeSceneObject<T>& world);

public:
	std::vector<Vector3<int>> Render(int w, int h, const CompositeSceneObject<T>& world);
};

#include "SimpleRT.inl"