#include <chrono>

#include "Renderer.h"


int main()
{

	Vec3 look_from(0.0, -50.0, 0.0);
	std::string filename = "HDRENDER_100xAA.ppm";

	// init
	Camera cam(1920, 100, 100, look_from); // width, fov, samples, look_from
	CubeMap milky_way(Image("cm_px.png"), Image("cm_nx.png"), Image("cm_py.png"), Image("cm_ny.png"), Image("cm_pz.png"), Image("cm_nz.png"));
	Renderer renderer(cam, milky_way);
	BlackHole SgrA(Vec3(0.0, 0.0, 0.0), 1.0);


	// time
	auto start = std::chrono::high_resolution_clock().now();

	// render
	renderer.render(SgrA, filename);

	// time
	auto end = std::chrono::high_resolution_clock().now();
	auto duration = std::chrono::duration_cast<std::chrono::minutes>(end - start);
	std::cout << "Rendering took " << duration << std::endl;

	return 0;
}
