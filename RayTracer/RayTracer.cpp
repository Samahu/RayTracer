#include <fstream>
#include <SimpleRT/SimpleRT.hpp>

#include <SimpleRT/Sphere.hpp>
#include <SimpleRT/CompositeSceneObject.hpp>

using namespace std;

int main()
{
	// Construct world
	auto world = std::make_unique<CompositeSceneObject<float>>();
	auto sphere1 = std::make_unique<Sphere<float>>(Vector3<float>{ 0.0f, 0.0f, -1.0f }, 0.5f);
	world->Add(move(sphere1));
	auto sphere2 = std::make_unique<Sphere<float>>(Vector3<float>{ 1.5f, 0.0f, -1.0f }, 0.5f);
	world->Add(move(sphere2));
	


	int w = 400;
	int h = 200;

	auto simpleRTf = SimpleRT<float>();
	auto result = simpleRTf.Render(w, h, *world);

	auto out = ofstream();
	out.open("test.ppm", ofstream::out);
	out << "P3" << endl;
	out << w << " " << h << endl;
	out << 255 << endl;
	for (auto v : result)
		out << v.x() << " " << v.y() << " " << v.z() << endl;

	out.close();

	return 0;
}