#pragma once

#include <Math/Vector3.hpp>
#include <vector>

template <class T>
class SimpleRT
{
public:
	std::vector<Vector3<int>> Process(int w, int h);
};

#include "SimpleRT.inl"