#pragma once

#include "RelativisticRay.h"
#include "Camera.h"
#include "CubeMap.h"

class Renderer
{
private:

	Camera cam;
	CubeMap cube_map;

public:

	Renderer() = default;
	Renderer(const Camera& c, const CubeMap& cube) : cam(c), cube_map(cube) {}

	void render(const BlackHole& SgrA, const std::string filename);

private:

	inline Vec3 get_ray_direction(const int i, const int j) const;
	Color ray_color(RelativisticRay& ray, const BlackHole& SgrA) const;
	Color deflected_ray_color(RelativisticRay& ray, const BlackHole& SgrA) const;
	Vec3 calculate_sky_direction(RelativisticRay& ray, const BlackHole& SgrA) const;
	double delta_phi(const RelativisticRay& ray) const;
};





