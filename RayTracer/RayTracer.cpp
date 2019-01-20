#include <iostream>
#include <fstream>
#include <chrono>


#include <SimpleRT/SimpleRT.hpp>
#include <SimpleRT/Sphere.hpp>
#include <SimpleRT/CompositeSceneObject.hpp>

using namespace std;

template <typename T>
auto Run(string desc, T method)
{
	const auto start = chrono::steady_clock::now();
	auto results = method();
	const auto end = chrono::steady_clock::now();

	cout << desc.c_str() << " - Duration: " << chrono::duration<double, milli>(end - start).count() << endl;

	return results;
}

auto simplertf(int w, int h)
{
	// Construct world
	auto world = std::make_unique<CompositeSceneObject<float>>();
	auto sphere1 = std::make_unique<Sphere<float>>(Vector3<float>{ 0.0f, 0.0f, -1.0f }, 0.5f);
	world->Add(move(sphere1));
	auto sphere2 = std::make_unique<Sphere<float>>(Vector3<float>{ 1.5f, 0.0f, -1.0f }, 0.5f);
	world->Add(move(sphere2));
	auto simpleRTf = SimpleRT<float>();

	return Run("SimpleRTf", [&simpleRTf, w, h, &world] { return simpleRTf.Render(w, h, *world); });
}

auto simplertd(int w, int h)
{
	// Construct world
	auto world = std::make_unique<CompositeSceneObject<double>>();
	auto sphere1 = std::make_unique<Sphere<double>>(Vector3<double>{ 0.0, 0.0, -1.0 }, 0.5);
	world->Add(move(sphere1));
	auto sphere2 = std::make_unique<Sphere<double>>(Vector3<double>{ 1.5, 0.0, -1.0 }, 0.5);
	world->Add(move(sphere2));
	auto simpleRTd = SimpleRT<double>();

	return Run("SimpleRTd", [&simpleRTd, w, h, &world] { return simpleRTd.Render(w, h, *world); });
}

void write(string fileName, int w, int h, vector<Vector3<int>> results)
{
	auto out = ofstream();
	out.open(fileName, ofstream::out);
	out << "P3" << endl;
	out << w << " " << h << endl;
	out << 255 << endl;
	for (auto v : results)
		out << v.x() << " " << v.y() << " " << v.z() << endl;
	out.close();
}

int main()
{
	int w = 400;
	int h = 200;
	
	auto s1 = simplertf(w, h);
	write("simplertf.ppm", w, h, s1);

	auto s2 = simplertd(w, h);
	write("simplertd.ppm", w, h, s2);

	return cin.get();
}