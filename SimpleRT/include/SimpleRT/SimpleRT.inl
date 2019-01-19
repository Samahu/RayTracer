#pragma once


template <class T>
std::vector<Vector3<int>> SimpleRT<T>::Process(int w, int h)
{
	std::vector<Vector3<int>> result(w * h, Vector3<int>::Zero);

	for (auto y = h - 1; y >= 0; --y)
		for (auto x = 0; x < w; ++x)
		{
			Vector3<T> value(static_cast<T>(x) / static_cast<T>(w), static_cast<T>(y) / static_cast<T>(h), static_cast<T>(0.2));

			auto r = int(255.99 * value.x());
			auto g = int(255.99 * value.y());
			auto b = int(255.99 * value.z());

			auto idx = (h - 1 - y) * w + x;

			result[idx] = Vector3<int>(r, g, b);
		}

	return result;
}