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

auto composeWorld()
{
	// Construct world
	auto world = std::make_unique<CompositeSceneObject>();

	auto sphere1 = std::make_unique<Sphere>(Vector3d{ 0.0, 0.0, -1.0 }, 0.5);
	sphere1->SetMaterial(std::make_shared<Lambertian>(Vector3d{ 0.1, 0.2, 0.5 }));
	world->Add(move(sphere1));

	auto sphere2 = std::make_unique<Sphere>(Vector3d{ 0.0, -100.5, -1.0 }, 100.0);
	sphere2->SetMaterial(std::make_shared<Lambertian>(Vector3d{ 0.8, 0.8, 0.0 }));
	world->Add(move(sphere2));

	auto sphere3 = std::make_unique<Sphere>(Vector3d{ 1.0, 0.0, -1.0 }, 0.5);
	sphere3->SetMaterial(std::make_shared<Metal>(Vector3d{ 0.8, 0.6, 0.2 }, 0.0));
	world->Add(move(sphere3));

	auto sphere4 = std::make_unique<Sphere>(Vector3d{ -1.0, 0.0, -1.0 }, 0.5);
	sphere4->SetMaterial(std::make_shared<Dielectric>(1.5));
	world->Add(move(sphere4));

	auto sphere5 = std::make_unique<Sphere>(Vector3d{ -1.0, 0.0, -1.0 }, -0.45);
	sphere5->SetMaterial(std::make_shared<Dielectric>(1.5));
	world->Add(move(sphere5));

	return world;
}

auto composeWorld2()
{
	// Construct world
	auto world = std::make_shared<CompositeSceneObject>();

	auto sphere0 = std::make_unique<Sphere>(Vector3d{ 0.0, -1000.0, 0.0 }, 1000.0);
	sphere0->SetMaterial(std::make_shared<Lambertian>(Vector3d{ 0.5, 0.5, 0.5 }));
	world->Add(move(sphere0));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> urd(0.0, 1.0);

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

auto simplert(int w, int h, std::shared_ptr<CompositeSceneObject> world)
{
	auto simpleRTd = SimpleRT();

	return Run("SimpleRT", [&simpleRTd, w, h, &world] { return simpleRTd.Render(w, h, *world); });
}

auto multithreadedrt(int w, int h, std::shared_ptr<CompositeSceneObject> world)
{
	auto multithreadedRT = MultiThreadedRT();

	return Run("MultiThreadedRT", [&multithreadedRT, w, h, &world] { return multithreadedRT.Render(w, h, *world); });
}


auto openmprt(int w, int h, std::shared_ptr<CompositeSceneObject> world)
{
	auto openmpRT = OpenMP_RT();

	return Run("OpenMP_RT", [&openmpRT, w, h, &world] { return openmpRT.Render(w, h, *world); });
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

	auto world = composeWorld2();

	auto s2 = simplert(w, h, world);
	write("simplert.ppm", w, h, s2);

	auto s3 = multithreadedrt(w, h, world);
	write("multithreadedrt.ppm", w, h, s3);

	auto s4 = openmprt(w, h, world);
	write("openmprt.ppm", w, h, s4);

	return cin.get();
}
