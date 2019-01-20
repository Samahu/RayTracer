#pragma once

template <typename T>
class Vector3
{
	template <typename T>
	friend Vector3<T> operator*(T t, const Vector3<T> v);

public:
	Vector3() {}
	Vector3(T x, T y, T z)
	{
		e[0] = x;
		e[1] = y;
		e[2] = z;
	}

	// Data Accessors
	T x() const { return e[0]; }
	T y() const { return e[1]; }
	T z() const { return e[2]; }

	Vector3<T> operator+(const Vector3<T> v) const { return Vector3<T>(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]); }
	Vector3<T> operator-(const Vector3<T> v) const { return Vector3<T>(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]); }

	Vector3 operator*(T t) const { return Vector3<T>(e[0] * t, e[1] * t, e[2] * t); }
	Vector3 operator/(T t) const { return Vector3<T>(e[0] / t, e[1] / t, e[2] / t); }

	Vector3 operator+=(const Vector3 v) { e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2]; return *this; }
	Vector3 operator-=(const Vector3 v) { e[0] -= v.e[0]; e[1] -= v.e[1]; e[2] -= v.e[2]; return *this; }
	Vector3 operator*=(T t) { e[0] *= t; e[1] *= t; e[2] *= t; return *this; }

	T SquaredLength() const;
	T Length() const;

	void Normalize();


	static T dot(const Vector3<T> v1, const Vector3<T> v2);

	static const Vector3<T> Zero;
	static const Vector3<T> One;

private:
	T e[3];
};

#include "Vector3.inl"