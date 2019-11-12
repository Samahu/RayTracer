#pragma once

#include <vector>
#include "SceneObject.hpp"
#include "HitRecord.hpp"

class CompositeSceneObject : public SceneObject
{
public:
	HitRecord HitTest(const Ray3d ray, double tmin, double tmax) const override;
	void SetMaterial(std::shared_ptr<Material> material) override {}

	void Add(std::unique_ptr<SceneObject> sceneObject);

private:
	std::vector<std::unique_ptr<SceneObject>> sceneObjects;
};

inline void CompositeSceneObject::Add(std::unique_ptr<SceneObject> sceneObject)
{
	sceneObjects.push_back(std::move(sceneObject));
}

inline HitRecord CompositeSceneObject::HitTest(const Ray3d ray, double tmin, double tmax) const
{
	auto hr = HitRecord{ false };

	auto closestHit = tmax;

	for (auto& so : sceneObjects)
	{
		auto hr_temp = so->HitTest(ray, tmin, closestHit);

		if (hr_temp.hit)
		{
			closestHit = hr_temp.t;
			hr = hr_temp;
		}
	}

	return hr;
}
