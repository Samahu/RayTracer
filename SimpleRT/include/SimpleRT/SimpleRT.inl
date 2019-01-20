#pragma once

template <class T>
bool SimpleRT<T>::hitSphere(const Vector3<T> center, float radius, Ray<T> ray)
{
	// Equation: t^2 * dot(b, b) + 2 * t * dot(b, a - c) + dot(a - c, a - c) == R^2
	// where:	c is center, a is ray origin, b is direction

	auto oc = ray.Origin() - center;
	auto a = Vector3<T>::dot(ray.Direction(), ray.Direction());
	auto b = 2 * Vector3<T>::dot(ray.Direction(), oc);
	auto c = Vector3<T>::dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

template <class T>
Vector3<T> SimpleRT<T>::color(const Ray<T> ray)
{
	if (hitSphere(Vector3<T>(0, 0, -1), 0.5, ray))
		return Vector3<T>(1.0f, 0.0f, 0.0f);

	auto unit_dir = ray.Direction();
	unit_dir.Normalize();
	T t = static_cast<T>(0.5) * (unit_dir.y() + static_cast<T>(1.0));
	return static_cast<T>(1.0 - t) * Vector3<T>::One + t * Vector3<T>(0.5f, 0.7f, 1.0f);
}

template <class T>
std::vector<Vector3<int>> SimpleRT<T>::Process(int w, int h)
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
			
			Ray<T> ray(origin, lower_left_corner + u * horizontal + v * vertical);

			auto c = color(ray);

			auto r = int(255.99 * c.x());
			auto g = int(255.99 * c.y());
			auto b = int(255.99 * c.z());

			auto idx = (h - 1 - y) * w + x;

			result[idx] = Vector3<int>(r, g, b);
		}

	return result;
}