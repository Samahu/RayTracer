#include "Math/Vector3.hpp"
#include <math.h>


template <>
const Vector3<int> Vector3<int>::Zero(0, 0, 0);

template <>
const Vector3<float> Vector3<float>::Zero(.0f, .0f, .0f);

template <>
const Vector3<double> Vector3<double>::Zero(0.0, 0.0, 0.0);

template <>
const Vector3<int> Vector3<int>::One{ 1, 1, 1 };

template <>
const Vector3<float> Vector3<float>::One{ 1.0f, 1.0f, 1.0f };

template <>
const Vector3<double> Vector3<double>::One{1.0, 1.0, 1.0};

template <>
float Vector3<float>::Length() const
{
	return sqrtf(SquaredLength());
}

template <>
double Vector3<double>::Length() const
{
	return sqrt(SquaredLength());
}
