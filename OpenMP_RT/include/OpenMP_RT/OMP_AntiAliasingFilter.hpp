#pragma once

#include <random>
#include <functional>
#include <vector>
#include <thread>

#include <Camera.hpp>

template <typename T>
class OMP_AntiAliasingFilter
{
public:
	virtual Vector3<T> Sample(int x, int y, const Camera<T>& camera, const CompositeSceneObject<T>& world,
		const std::function< Vector3<T> (const Ray<T>&, const CompositeSceneObject<T>&) >& lambda) = 0;
};


template <typename T>
class OMP_RandomAntiAliasingFilter : public OMP_AntiAliasingFilter<T>
{
public:
	Vector3<T> Sample(int x, int y, const Camera<T>& camera, const CompositeSceneObject<T>& world,
		const std::function< Vector3<T>(const Ray<T>&, const CompositeSceneObject<T>&) >& lambda) override;
};

template<typename T>
inline Vector3<T> OMP_RandomAntiAliasingFilter<T>::Sample(int x, int y, const Camera<T>& camera, const CompositeSceneObject<T>& world,
	const std::function< Vector3<T>(const Ray<T>&, const CompositeSceneObject<T>&) >& lambda)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> urd(0.0, 1.0);

	auto w = camera.Width();
	auto h = camera.Height();

	auto samples_count = 16;
	auto c = Vector3<T>::Zero;

#pragma omp parallel
	{
#pragma omp for
		for (auto i = 0; i < samples_count; ++i)
		{
			T u = static_cast<T>(x + urd(gen)) / static_cast<T>(w);
			T v = static_cast<T>(y + urd(gen)) / static_cast<T>(h);

			auto ray = camera.CastRay(u, v);
			auto s = lambda(ray, world);
			c += s;
		}
	}

	return c / static_cast<T>(samples_count);
}
