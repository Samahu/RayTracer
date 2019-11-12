#include <iostream>
#include <fstream>
#include <chrono>


#include <SceneObjects/Sphere.hpp>
#include <SceneObjects/CompositeSceneObject.hpp>
#include <Materials/Lambertian.hpp>
#include <Materials/Metal.hpp>
#include <Materials/Dielectric.hpp>
#include <SimpleRT/SimpleRT.hpp>
#include <MultiThreadedRT/MultiThreadedRT.hpp>
#include <OpenMP_RT/OpenMP_RT.hpp>


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

template <typename T>
auto composeWorld()
{
	// Construct world
	auto world = std::make_unique<CompositeSceneObject>();

	auto sphere1 = std::make_unique<Sphere>(Vector3<T>{ 0.0f, 0.0f, -1.0f }, 0.5f);
	sphere1->SetMaterial(std::make_shared<Lambertian<T>>(Vector3<T>{ 0.1f, 0.2f, 0.5f }));
	world->Add(move(sphere1));

	auto sphere2 = std::make_unique<Sphere>(Vector3<T>{ 0.0f, -100.5f, -1.0f }, 100.0f);
	sphere2->SetMaterial(std::make_shared<Lambertian<T>>(Vector3<T>{ 0.8f, 0.8f, 0.0f }));
	world->Add(move(sphere2));

	auto sphere3 = std::make_unique<Sphere>(Vector3<T>{ 1.0f, 0.0f, -1.0f }, 0.5f);
	sphere3->SetMaterial(std::make_shared<Metal<T>>(Vector3<T>{ 0.8f, 0.6f, 0.2f }, 0.0f));
	world->Add(move(sphere3));

	auto sphere4 = std::make_unique<Sphere>(Vector3<T>{ -1.0f, 0.0f, -1.0f }, 0.5f);
	sphere4->SetMaterial(std::make_shared<Dielectric<T>>(1.5f));
	world->Add(move(sphere4));

	auto sphere5 = std::make_unique<Sphere>(Vector3<T>{ -1.0f, 0.0f, -1.0f }, -0.45f);
	sphere5->SetMaterial(std::make_shared<Dielectric<T>>(1.5f));
	world->Add(move(sphere5));

	return world;
}

auto composeWorld2()
{
	// Construct world
	auto world = std::make_unique<CompositeSceneObject>();

	auto sphere0 = std::make_unique<Sphere>(Vector3d{ 0.0, -1000.0, 0.0 }, 1000.0);
	sphere0->SetMaterial(std::make_shared<Lambertian>(Vector3d{ 0.5, 0.5, 0.5 }));
	world->Add(move(sphere0));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> urd(0.0f, 1.0f);

	for (auto a = -11; a < 11; ++a)
		for (auto b = -11; b < 11; ++b)
		{
			auto choose_mat = urd(gen);
			auto center = Vector3d{ a + 0.9 * urd(gen), 0.2, b + 0.9 * urd(gen) };
			std::unique_ptr<SceneObject> sobj;

			if ((center - Vector3d{4.0, 0.2, 0.0}).Length() > 0.9)
			{
				sobj = std::make_unique<Sphere>(center, 0.2);
				
				if (choose_mat < 0.8)
				{
					sobj->SetMaterial(std::make_shared<Lambertian>(
						Vector3d{ urd(gen)*urd(gen), urd(gen)*urd(gen), urd(gen)*urd(gen) }));
				}
				else if (choose_mat < 0.95)
				{
					sobj->SetMaterial(std::make_shared<Metal>(
						Vector3d{ 0.5 * (1+urd(gen)), 0.5 * (1 + urd(gen)), 0.5 * (1 + urd(gen)) }, 0.5 * urd(gen)));
				}
				else
				{
					sobj->SetMaterial(std::make_shared<Dielectric>(1.5));
				}

				world->Add(move(sobj));
			}
		}

	auto sphere2 = std::make_unique<Sphere>(Vector3d{ 0.0, 1.0, 0.0 }, 1.0);
	sphere2->SetMaterial(std::make_shared<Dielectric>(1.5));

	world->Add(move(sphere2));

	auto sphere3 = std::make_unique<Sphere>(Vector3d{ -4.0, 1.0, 0.0 }, 1.0);
	sphere3->SetMaterial(std::make_shared<Lambertian>(Vector3d{ 0.4, 0.2, 0.1 }));
	world->Add(move(sphere3));

	auto sphere4 = std::make_unique<Sphere>(Vector3d{ 4.0, 1.0, 0.0 }, 1.0);
	sphere4->SetMaterial(std::make_shared<Metal>(Vector3d{ 0.7, 0.2, 0.5 }, 0.0));
	world->Add(move(sphere4));

	return world;
}

auto simplertd(int w, int h)
{
	auto world = composeWorld2();
	auto simpleRTd = SimpleRT();

	return Run("SimpleRTd", [&simpleRTd, w, h, &world] { return simpleRTd.Render(w, h, *world); });
}

auto multithreadedrtd(int w, int h)
{
	auto world = composeWorld2();
	auto multithreadedRTd = MultiThreadedRT();

	return Run("multithreadedrtd", [&multithreadedRTd, w, h, &world] { return multithreadedRTd.Render(w, h, *world); });
}


auto openmprtd(int w, int h)
{
	auto world = composeWorld2();
	auto openmpRTd = OpenMP_RT();

	return Run("openmprtd", [&openmpRTd, w, h, &world] { return openmpRTd.Render(w, h, *world); });
}

void write(string fileName, int w, int h, vector<Vector3i> results)
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
	int w = 100;
	int h = 50;

	auto s2 = simplertd(w, h);
	write("simplertd.ppm", w, h, s2);

	auto s3 = multithreadedrtd(w, h);
	write("multithreadedrtd.ppm", w, h, s3);

	auto s4 = openmprtd(w, h);
	write("openmprtd.ppm", w, h, s4);

	return cin.get();
}
