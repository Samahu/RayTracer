#pragma once

template <class T>
class Vector3
{
	template <class T>
	friend Vector3<T> operator*(T t, const Vector3<T> v);

	template <class T>
	friend Vector3<T> operator+(const Vector3<T> v1, const Vector3<T> v2);

private:
	T e[3];

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

	Vector3 operator+(const Vector3 v) { e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2]; return *this; }
	Vector3 operator-(const Vector3 v) { e[0] -= v.e[0]; e[1] -= v.e[1]; e[2] -= v.e[2]; return *this; }
	Vector3 operator*(T t) { e[0] *= t; e[1] *= t; e[2] *= t; return *this; }


	static const Vector3<T> Zero;
};

template <class T>
Vector3<T> operator*(T t, const Vector3<T> v) { return Vector3<T>(v.e[0] * t, v.e[1] * t, v.e[2] * t); }

template <class T>
Vector3<T> operator+(const Vector3<T> v1, const Vector3<T> v2) { return Vector3<T>(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]); }