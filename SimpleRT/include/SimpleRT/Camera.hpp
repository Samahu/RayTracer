#pragma once

#include <Math/Vector3.hpp>

template <typename T>
class Camera
{
public:
	Camera(int width, int height)
		: width(width), height(height)
	{

	}

	Ray<T> CastRay(T u, T v) const
	{
		return Ray<T>{ origin, lower_left_corner + u * horizontal + v * vertical - origin };
	}

	int Width() const { return width; }
	int Height() const { return height; }

private:
	int width;
	int height;
	Vector3<T> lower_left_corner{ -2.0, -1.0, -1.0 };
	Vector3<T> horizontal{ 4.0, 0.0, 0 };
	Vector3<T> vertical{ 0.0, 2.0, 0 };
	Vector3<T> origin{ Vector3<T>::Zero };
};