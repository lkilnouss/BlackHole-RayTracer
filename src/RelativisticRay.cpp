#include "RelativisticRay.h"

// public
RelativisticRay::RelativisticRay(const Point3& orig, const Vec3& direc, const BlackHole& SgrA)
{
	// initializing 
	init_origin = orig;
	init_direction = direc;

	Vec3 radial = init_origin - SgrA.position;

	// convert to spherical
	r = (radial).length();
	phi = 0.0;
	inward = true;
	r_min = 0.0;

	dr_dphi_squared = dr_over_dphi_squared();

	r_s = SgrA.r_s;
	impact_parameter = calculate_b(SgrA);

	// orbital plane
	Vec3 plane_normal = radial.cross(init_direction);
	plane_er = radial.normalized();
	plane_ephi = plane_normal.cross(plane_er).normalized();
}

void RelativisticRay::calculate_r_min()
{
	double psi = std::acos(-3.0 * sqrt_three * r_s / (2 * impact_parameter));

	// set r_min
	r_min = (2.0 * impact_parameter / sqrt_three) * std::cos(psi / 3.0);
}

// private
double RelativisticRay::calculate_sin_alpha(const BlackHole& SgrA) const
{
	Vec3 radial = (init_origin - SgrA.position).normalized();
	double sin_alpha = radial.cross(init_direction).length() / (radial.length() * init_direction.length());

	return sin_alpha;
}

double RelativisticRay::calculate_b(const BlackHole& SgrA) const
{
	double sin_a = calculate_sin_alpha(SgrA);
	double b = (sin_a * r) / std::sqrt(1 - r_s / r);

	return b;
}

double RelativisticRay::dr_over_dphi_squared() const
{
	// calculate squared
	return (r * r * r * r) * ((1 / (impact_parameter * impact_parameter)) - (1 / (r * r)) * (1 - r_s / r));
}

double RelativisticRay::get_sign() const
{
	if (inward)
		return -1.0;
	else
		return 1.0;
}

void RelativisticRay::set_sign()
{
	if (inward)
	{
		if (r <= r_min)
		{
			r = r_min + CONST_EPS;
			inward = false;
			//std::cout << "\nturning point reached\n";
			return;
		}
	}
}
