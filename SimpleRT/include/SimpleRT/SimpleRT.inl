#pragma once

#include <random>
#include <limits>

#include "Camera.hpp"
#include "AntiAliasingFilter.hpp"

template <typename T>
Vector3<T> SimpleRT<T>::random_in_unit_sphere() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<T> urd(0.0, 1.0);

	Vector3<T> p;

	do
	{
		p = static_cast<T>(2.0) * Vector3<T>(urd(gen), urd(gen), urd(gen)) - Vector3<T>::One;
	} while (p.SquaredLength() >= 1.0);

	return p;
}

template <typename T>
Vector3<T> SimpleRT<T>::color(const Ray<T> ray, const CompositeSceneObject<T>& world) const
{
	// avoid possibly getting negative t value by setting t_min to 0.001
	auto hr = world.HitTest(ray, 0.001f, numeric_limits<T>::max());

	if (hr.hit)
	{
		/* normals */
		//auto n = hr.n;
		//return static_cast<T>(0.5) * Vector3<T>(n.x() + 1, n.y() + 1, n.z() + 1);

		/* matte */
		auto target = hr.p + hr.n + random_in_unit_sphere();
		Ray<T> new_ray(hr.p, target - hr.p);
		return static_cast<T>(0.5) * color(new_ray, world); 
	}

	auto unit_dir = ray.Direction();
	unit_dir.Normalize();
	auto t = static_cast<T>(0.5) * (unit_dir.y() + static_cast<T>(1.0));
	return static_cast<T>(1.0 - t) * Vector3<T>::One + t * Vector3<T>(0.5f, 0.7f, 1.0f);
}

template <typename T>
std::vector<Vector3<int>> SimpleRT<T>::Render(int w, int h, const CompositeSceneObject<T>& world)
{
	std::vector<Vector3<int>> result(w * h, Vector3<int>::Zero);
	auto camera = Camera<T>{ w, h };
	auto sampler = RandomAntiAliasingFilter<T>{};

	for (auto y = h - 1; y >= 0; --y)
		for (auto x = 0; x < w; ++x)
		{
			auto c = sampler.Sample(x, y, camera, world, [this](const Ray<T> r, const CompositeSceneObject<T>& w) -> Vector3<T> { return color(r, w); });

			// SIMPLE GAMMA CORRECTION
			// correct = origin^(1/gamma)	-> here gamma is 2
			c = Vector3<T>(sqrt(c.x()), sqrt(c.y()), sqrt(c.z()));

			auto r = int(255.99 * c.x());
			auto g = int(255.99 * c.y());
			auto b = int(255.99 * c.z());

			auto idx = (h - 1 - y) * w + x;

			result[idx] = Vector3<int>(r, g, b);
		}

	return result;
}
