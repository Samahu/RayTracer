#pragma once

#include <random>
#include <limits>

#define _USE_MATH_DEFINES
#include <math.h>

#include <Materials/Material.h>

#include <Camera.hpp>
#include "MT_AntiAliasingFilter.hpp"

template <typename T>
Vector3<T> MultiThreadedRT<T>::color(const Ray<T> ray, const CompositeSceneObject<T>& world, int depth) const
{
	// avoid possibly getting negative t value by setting t_min to 0.001
	auto hr = world.HitTest(ray, 0.001f, numeric_limits<T>::max());

	if (hr.hit)
	{
		/* normals */
		//auto n = hr.n;
		//return static_cast<T>(0.5) * Vector3<T>(n.x() + 1, n.y() + 1, n.z() + 1);

		/* matte */
		//auto target = hr.p + hr.n + random_in_unit_sphere();
		//Ray<T> new_ray(hr.p, target - hr.p);
		//return static_cast<T>(0.5) * color(new_ray, world);

		/* generic */
		Ray<T> scattered;
		Vector3<T> attenuation;

		if (depth < 50 && hr.m->scatter(ray, hr, attenuation, scattered))
			return attenuation * color(scattered, world, depth + 1);
		else
			return Vector3<T>::Zero;
	}

	auto unit_dir = ray.Direction();
	unit_dir.Normalize();
	auto t = static_cast<T>(0.5) * (unit_dir.y() + static_cast<T>(1.0));
	return static_cast<T>(1.0 - t) * Vector3<T>::One + t * Vector3<T>(0.5f, 0.7f, 1.0f);
}

template <typename T>
std::vector<Vector3<int>> MultiThreadedRT<T>::Render(int w, int h, const CompositeSceneObject<T>& world)
{
	std::vector<Vector3<int>> result(w * h, Vector3<int>::Zero);
	std::vector<std::future<Vector3<int>>> a_result(w * h);

	auto eye = Vector3<T>{ 3.0f, 3.0f, 2.0f };
	auto lookAt = Vector3<T>{ 0.0f, 0.0f, -1.0f };
	auto up = Vector3<T>{ 0.0f, 1.0f, 0.0f };
	auto dist_to_focus = (lookAt - eye).Length();
	auto aperture = 2.0f;
	auto camera = Camera<T>{ w, h,
		eye, lookAt, up, 
		static_cast<T>(M_PI_4), aperture, dist_to_focus };
	auto sampler = MT_RandomAntiAliasingFilter<T>{};

	for (auto y = h - 1; y >= 0; --y)
		for (auto x = 0; x < w; ++x)
		{
			auto idx = (h - 1 - y) * w + x;

			//a_result[idx] = std::async(std::launch::deferred, [&] () {

				auto c = sampler.Sample(x, y, camera, world,
					[this](const Ray<T> r, const CompositeSceneObject<T>& w) -> Vector3<T> { return color(r, w, 0); });

				// SIMPLE GAMMA CORRECTION
				// correct = origin^(1/gamma)	-> here gamma is 2
				c = Vector3<T>(sqrt(c.x()), sqrt(c.y()), sqrt(c.z()));

				auto r = int(255.99 * c.x());
				auto g = int(255.99 * c.y());
				auto b = int(255.99 * c.z());

				result[idx] = Vector3<int>(r, g, b);
			//});
		}

	//for (auto i = 0; i < w * h; ++i)
	//	result[i] = a_result[i].get();

	return result;
}
