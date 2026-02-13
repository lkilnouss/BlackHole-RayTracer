#pragma once

#include "Constants.h"
#include "Vec3.h"
using msl::Vec3;

class RelativisticRay;
class BlackHole;

////////////////////////////////////////////////////////////////////////////////////////
// utility
static inline double degrees_to_radians(const double angle_deg)
{
	return angle_deg * (CONST_PI / 180);
}

static inline double clamp(double input, double x_min, double x_max)
{
	if (input < x_min)
		return x_min;
	else if (input > x_max)
		return x_max;
	else return input;
}

static inline double random_double()
{
	return static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
}

// need members: 
double delta_phi(const RelativisticRay& ray);
Vec3 calculate_sky_direction(RelativisticRay& ray, const BlackHole& SgrA);






