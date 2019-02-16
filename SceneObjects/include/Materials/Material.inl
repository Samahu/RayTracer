#pragma once

#include <random>

template <typename T>
Vector3<T> Material<T>::random_in_unit_sphere() const
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