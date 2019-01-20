#pragma once

#include "SceneObject.hpp"

template<typename T>
inline void CompositeSceneObject<T>::Add(std::unique_ptr<SceneObject<T>> sceneObject)
{
	sceneObjects.push_back(std::move(sceneObject));
}

template<typename T>
inline HitRecord<T> CompositeSceneObject<T>::HitTest(const Ray<T> ray, T tmin, T tmax) const
{
	auto hr = HitRecord<T>{ false };

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
