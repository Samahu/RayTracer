#pragma once

#include <vector>

#include <Math/Vector3.hpp>
#include <Math/Ray.hpp>

template <class T>
class SimpleRT
{
private:
	bool hitSphere(const Vector3<T> center, float radius, Ray<T> ray);
	Vector3<T> color(const Ray<T> ray);

public:
	std::vector<Vector3<int>> Process(int w, int h);
};

#include "SimpleRT.inl"