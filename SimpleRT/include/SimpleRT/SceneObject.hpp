#pragma once

#include <Math/Vector3.hpp>
#include <Math/Ray.hpp>

#include <memory>

template <class T>
struct HitRecord
{
	bool hit;
	T t;
	Vector3<T> p;
	Vector3<T> n;
};

template <class T>
class SceneObject
{
public:
	virtual ~SceneObject() {}

	virtual HitRecord<T> HitTest(const Ray<T> ray, T tmin, T tmax) const = 0;
};

template <class T>
class CompositeSceneObject : public SceneObject<T>
{
private:
	std::vector<std::unique_ptr<SceneObject<T>>> sceneObjects;

public:
	void Add(std::unique_ptr<SceneObject<T>> sceneObject);

	HitRecord<T> HitTest(const Ray<T> ray, T tmin, T tmax) const override;
};