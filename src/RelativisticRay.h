#pragma once

#include "BlackHole.h"
#include "Utility.h"


using Point3 = msl::Vec3;

class RelativisticRay
{
public:

	// set at begin
	Point3 init_origin;
	Vec3 init_direction;

	// calculated for GR
	double r;
	double phi;
	double impact_parameter;
	double dr_dphi_squared;

	// orbital plane: radially outward and tangential basis
	Vec3 plane_er;
	Vec3 plane_ephi;

	// turning point
	bool inward;
	double r_min;


	// Black Hole properties
	double r_s;

	RelativisticRay() = default;
	RelativisticRay(const Point3& orig, const Vec3& direc, const BlackHole& SgrA);


	// helpers
	inline void update(double delta_phi)
	{
		// get the sign 
		set_sign();
		double sign = get_sign();
		dr_dphi_squared = dr_over_dphi_squared();

		// update
		phi += delta_phi;
		r += sign * std::sqrt(dr_dphi_squared) * delta_phi;
	}

	void calculate_r_min();


private:

	double calculate_sin_alpha(const BlackHole& SgrA) const;
	double calculate_b(const BlackHole& SgrA) const;
	double dr_over_dphi_squared() const;
	double get_sign() const;
	void set_sign();
};
