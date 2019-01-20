#pragma once

#include <Math/Vector3.hpp>
#include <Math/Ray.hpp>

#include <memory>

template <typename T>
struct HitRecord
{
	bool hit;
	T t;
	Vector3<T> p;
	Vector3<T> n;
};

template <typename T>
class SceneObject
{
public:
	virtual ~SceneObject() {}

	virtual HitRecord<T> HitTest(const Ray<T> ray, T tmin, T tmax) const = 0;
};

template <typename T>
class CompositeSceneObject : public SceneObject<T>
{
public:
	HitRecord<T> HitTest(const Ray<T> ray, T tmin, T tmax) const override;

	void Add(std::unique_ptr<SceneObject<T>> sceneObject);

private:
	std::vector<std::unique_ptr<SceneObject<T>>> sceneObjects;
};