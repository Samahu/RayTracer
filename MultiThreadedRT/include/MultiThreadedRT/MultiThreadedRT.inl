#pragma once

#include <random>
#include <limits>

#define _USE_MATH_DEFINES
#include <math.h>

#include <Materials/Material.hpp>

#include <Camera.hpp>
#include "MT_AntiAliasingFilter.hpp"

Vector3d MultiThreadedRT::color(const Ray3d ray, const CompositeSceneObject& world, int depth) const
{
	// avoid possibly getting negative t value by setting t_min to 0.001
	auto hr = world.HitTest(ray, 0.001, std::numeric_limits<double>::max());

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
		Ray3d scattered;
		Vector3d attenuation;

		if (depth < 50 && hr.m->scatter(ray, hr, attenuation, scattered))
			return attenuation * color(scattered, world, depth + 1);
		else
			return Vector3d::Zero;
	}

	auto unit_dir = ray.Direction();
	unit_dir.Normalize();
	auto t = 0.5 * (unit_dir.y() + 1.0);
	return (1.0 - t) * Vector3d::One + t * Vector3d(0.5, 0.7, 1.0);
}

std::vector<Vector3i> MultiThreadedRT::Render(int w, int h, const CompositeSceneObject& world)
{
	std::vector<Vector3i> result(w * h, Vector3i::Zero);
	std::vector<std::future<Vector3i>> a_result(w * h);

	auto eye = Vector3d{ 3.0, 3.0, 2.0 };
	auto lookAt = Vector3d{ 0.0, 0.0, -1.0 };
	auto up = Vector3d{ 0.0, 1.0, 0.0 };
	auto dist_to_focus = (lookAt - eye).Length();
	auto aperture = 2.0;
	auto camera = Camera{ w, h,
		eye, lookAt, up, 
		M_PI_4, aperture, dist_to_focus };
	auto sampler = MT_RandomAntiAliasingFilter{};

	for (auto y = h - 1; y >= 0; --y)
		for (auto x = 0; x < w; ++x)
		{
			auto idx = (h - 1 - y) * w + x;

			//a_result[idx] = std::async(std::launch::deferred, [&] () {

				auto c = sampler.Sample(x, y, camera, world,
					[this](const Ray3d r, const CompositeSceneObject& w) -> Vector3d{ return color(r, w, 0); });

				// SIMPLE GAMMA CORRECTION
				// correct = origin^(1/gamma)	-> here gamma is 2
				c = Vector3d(sqrt(c.x()), sqrt(c.y()), sqrt(c.z()));
				c = Vector3d(sqrt(c.x()), sqrt(c.y()), sqrt(c.z()));

				auto r = int(255.99 * c.x());
				auto g = int(255.99 * c.y());
				auto b = int(255.99 * c.z());

				result[idx] = Vector3i(r, g, b);
			//});
		}

	//for (auto i = 0; i < w * h; ++i)
	//	result[i] = a_result[i].get();

	return result;
}
