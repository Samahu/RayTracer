#pragma once

#include <Math/Vector3.hpp>

template <typename T>
class Camera
{
public:
	Camera(int width, int height, Vector3<T> eye, Vector3<T> lookAt, Vector3<T> up, T vfov, T aperture, T focus_dist)
		: width(width), height(height), lens_radius(aperture / 2)
	{

		auto aspect = static_cast<T>(width) / static_cast<T>(height);
		auto half_height = tan(0.5f * vfov);
		auto half_width = aspect * half_height;

		origin = eye;
		w = eye - lookAt;
		w.Normalize();
		u = Vector3<T>::cross(up, w);
		u.Normalize();
		v = Vector3<T>::cross(w, u);

		lower_left_corner = origin - (u * focus_dist * half_width + v * focus_dist * half_height + w * focus_dist);
		horizontal = 2 * focus_dist * half_width * u;
		vertical = 2 * focus_dist * half_height * v;
	}

	Ray<T> CastRay(T s, T t) const
	{
		auto rd = random_in_unit_disk() * lens_radius;
		auto offset = u * rd.x() + v * rd.y();
		return Ray<T>{ origin + offset, lower_left_corner + s * horizontal + t * vertical - (origin + offset) };
	}

	int Width() const { return width; }
	int Height() const { return height; }

private:
	Vector3<T> random_in_unit_disk() const
	{
		Vector3<T> p;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<T> urd(0.0f, 1.0f);

		do
		{
			p = Vector3<T>{ urd(gen), urd(gen), 0.0f } - Vector3<T>{ 1.0f, 1.0f, 0 };
		} while (Vector3<T>::dot(p, p) >= 1.0);

		return p;
	}

private:
	int width;
	int height;
	Vector3<T> lower_left_corner;
	Vector3<T> horizontal;
	Vector3<T> vertical;
	Vector3<T> origin{ Vector3<T>::Zero };
	Vector3<T> u, v, w;
	T lens_radius;
};