#pragma once

template <class T>
Vector3<T> SimpleRT<T>::color(const Ray<T> ray, const CompositeSceneObject<T>& world)
{
	auto hr = world.HitTest(ray, 0, 10);

	if (hr.hit)
	{
		auto n = hr.n;
		return static_cast<T>(0.5) * Vector3<T>(n.x() + 1, n.y() + 1, n.z() + 1);
	}

	auto unit_dir = ray.Direction();
	unit_dir.Normalize();
	auto t = static_cast<T>(0.5) * (unit_dir.y() + static_cast<T>(1.0));
	return static_cast<T>(1.0 - t) * Vector3<T>::One + t * Vector3<T>(0.5f, 0.7f, 1.0f);
}

template <class T>
std::vector<Vector3<int>> SimpleRT<T>::Render(int w, int h, const CompositeSceneObject<T>& world)
{
	std::vector<Vector3<int>> result(w * h, Vector3<int>::Zero);

	Vector3<T> lower_left_corner(-2.0, -1.0, -1.0);
	Vector3<T> horizontal(4.0, 0.0, 0);
	Vector3<T> vertical(0.0, 2.0, 0);
	auto origin = Vector3<T>::Zero;

	for (auto y = h - 1; y >= 0; --y)
		for (auto x = 0; x < w; ++x)
		{
			T u = static_cast<T>(x) / static_cast<T>(w);
			T v = static_cast<T>(y) / static_cast<T>(h);
			
			Ray<T> ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);

			auto c = color(ray, world);

			auto r = int(255.99 * c.x());
			auto g = int(255.99 * c.y());
			auto b = int(255.99 * c.z());

			auto idx = (h - 1 - y) * w + x;

			result[idx] = Vector3<int>(r, g, b);
		}

	return result;
}