#pragma once

#include "Constants.h"
#include "Vec3.h"
using msl::Vec3;
using Color = Vec3;

class BlackHole
{

public:

	Vec3 position;
	double mass;
	double r_s;


	BlackHole() = default;
	BlackHole(const Vec3& i_p, const double m) : position(i_p), mass(m), r_s(2 * mass) {}

};


