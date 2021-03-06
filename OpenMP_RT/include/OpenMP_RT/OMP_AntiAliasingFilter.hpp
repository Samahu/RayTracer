#pragma once

#include <random>
#include <functional>
#include <vector>
#include <thread>

#include <Camera.hpp>

class OMP_AntiAliasingFilter
{
public:
	virtual Vector3d Sample(int x, int y, const Camera& camera, const CompositeSceneObject& world,
		const std::function< Vector3d (const Ray3d&, const CompositeSceneObject&) >& lambda) = 0;
};

class OMP_RandomAntiAliasingFilter : public OMP_AntiAliasingFilter
{
public:
	Vector3d Sample(int x, int y, const Camera& camera, const CompositeSceneObject& world,
		const std::function< Vector3d(const Ray3d&, const CompositeSceneObject&) >& lambda) override;
};

inline Vector3d OMP_RandomAntiAliasingFilter::Sample(int x, int y, const Camera& camera, const CompositeSceneObject& world,
	const std::function< Vector3d(const Ray3d&, const CompositeSceneObject&) >& lambda)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> urd(0.0, 1.0);

	auto w = camera.Width();
	auto h = camera.Height();

	auto samples_count = 16;
	auto c = Vector3d::Zero;

#pragma omp parallel
	{
#pragma omp for
		for (auto i = 0; i < samples_count; ++i)
		{
			auto u = (x + urd(gen)) / w;
			auto v = (y + urd(gen)) / h;

			auto ray = camera.CastRay(u, v);
			auto s = lambda(ray, world);
			c += s;
		}
	}

	return c / samples_count;
}
