#include <chrono>

#include "Renderer.h"
#include "Service.h"


int main()
{
	std::string output_file;
	int image_width;
	int fov;
	int samples;
	CubeMap cm;

	// user sets parameters
	set_parameters(output_file, image_width, fov, samples, cm);

	// init
	Vec3 look_from(0.0, -50.0, 0.0);
	Camera cam(image_width, fov, samples, look_from); // width, fov, samples, look_from
	Renderer renderer(cam, cm);
	BlackHole SgrA(Vec3(0.0, 0.0, 0.0), 1.0);

	// time
	auto start = std::chrono::high_resolution_clock().now();

	// render
	renderer.render(SgrA, output_file);

	// time
	auto end = std::chrono::high_resolution_clock().now();
	auto duration = std::chrono::duration_cast<std::chrono::minutes>(end - start);
	std::cout << "Rendering took " << duration << std::endl;

	return 0;
}
