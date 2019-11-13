#pragma once

#include <Math/Vector3.hpp>

class Camera
{
public:
	Camera(int width, int height, Vector3d eye, Vector3d lookAt, Vector3d up, double vfov, double aperture, double focus_dist)
		: width(width), height(height), lens_radius(aperture / 2)
	{
		auto aspect = width / height;
		auto half_height = tan(0.5 * vfov);
		auto half_width = aspect * half_height;

		origin = eye;
		w = eye - lookAt;
		w.Normalize();
		u = Vector3d::cross(up, w);
		u.Normalize();
		v = Vector3d::cross(w, u);

		lower_left_corner = origin - (u * focus_dist * half_width + v * focus_dist * half_height + w * focus_dist);
		horizontal = 2 * focus_dist * half_width * u;
		vertical = 2 * focus_dist * half_height * v;
	}

	Ray3d CastRay(double s, double t) const
	{
		auto rd = random_in_unit_disk() * lens_radius;
		auto offset = u * rd.x() + v * rd.y();
		return Ray3d{ origin + offset, lower_left_corner + s * horizontal + t * vertical - (origin + offset) };
	}

	int Width() const { return width; }
	int Height() const { return height; }

private:
	Vector3d random_in_unit_disk() const
	{
		Vector3d p;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> urd(0.0, 1.0);

		do
		{
			p = Vector3d{ urd(gen), urd(gen), 0.0 } - Vector3d{ 1.0, 1.0, 0 };
		} while (Vector3d::dot(p, p) >= 1.0);

		return p;
	}

private:
	int width;
	int height;
	Vector3d lower_left_corner;
	Vector3d horizontal;
	Vector3d vertical;
	Vector3d origin{ Vector3d::Zero };
	Vector3d u, v, w;
	double lens_radius;
};