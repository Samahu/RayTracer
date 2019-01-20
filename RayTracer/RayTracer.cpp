#include <fstream>
#include <SimpleRT/SimpleRT.hpp>

using namespace std;

int main()
{
	int w = 400;
	int h = 200;

	auto simpleRTf = SimpleRT<float>();
	auto result = simpleRTf.Process(w, h);

	auto out = ofstream();
	out.open("test.ppm", ofstream::out);
	out << "P3" << endl;
	out << w << " " << h << endl;
	out << 255 << endl;
	for (auto v : result)
		out << v.x() << " " << v.y() << " " << v.z() << endl;

	out.close();
}