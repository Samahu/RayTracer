#pragma once

#include <random>
#include <functional>
#include <vector>
#include <thread>
#include <future>

#include <Camera.hpp>

class MT_AntiAliasingFilter
{
public:
	virtual Vector3d Sample(int x, int y, const Camera& camera, const CompositeSceneObject& world,
		const std::function< Vector3d (const Ray3d&, const CompositeSceneObject&) >& lambda) = 0;
};

class MT_RandomAntiAliasingFilter : public MT_AntiAliasingFilter
{
public:
	Vector3d Sample(int x, int y, const Camera& camera, const CompositeSceneObject& world,
		const std::function< Vector3d(const Ray3d&, const CompositeSceneObject&) >& lambda) override;
};

inline Vector3d MT_RandomAntiAliasingFilter::Sample(int x, int y, const Camera& camera, const CompositeSceneObject& world,
	const std::function< Vector3d(const Ray3d&, const CompositeSceneObject&) >& lambda)
{
	auto w = camera.Width();
	auto h = camera.Height();

	auto samples_count = 16;
	auto c = Vector3d::Zero;
	
	std::vector<std::future<Vector3d>> results;
	results.resize(samples_count);

	for (auto i = 0; i < samples_count; ++i)
	{
		results[i] = std::async(std::launch::async, [&c, w, h, x, y, &camera, &world, &lambda]() {

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<double> urd(0.0, 1.0);

			auto u = (x + urd(gen)) / w;
			auto v = (y + urd(gen)) / h;

			auto ray = camera.CastRay(u, v);
			auto s = lambda(ray, world);

			return s;
		});
	}

	for (auto &f : results)
		c += f.get();

	return c / samples_count;
}
