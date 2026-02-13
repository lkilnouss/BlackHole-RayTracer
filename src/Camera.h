#pragma once

#include "Utility.h" // constants and cmath
#include "Vec3.h"
using msl::Vec3;

class Camera
{
public:

	// image
	int image_width;
	int image_height;
	double aspect_ratio;

	// camera
	Vec3 look_from;
	Vec3 look_at;
	double fov;

	// viewport
	double focal_length;
	double viewport_height;
	Vec3 viewport_right;
	Vec3 viewport_down;
	Vec3 viewport_dx;
	Vec3 viewport_dz;

	Vec3 pixel00_location;
	unsigned samples_count;


	// functions
	void initialize(const int width, const double i_fov, const unsigned samples, const Vec3& l_f)
	{
		aspect_ratio = 16.0 / 9.0;
		image_width = width;
		image_height = width / aspect_ratio;

		look_from = l_f;
		look_at = Vec3(0.0, 0.0, 0.0);
		Vec3 viewing_direction = (look_at - look_from).normalized();
		fov = i_fov;

		focal_length = 1.0;
		viewport_height = 2 * focal_length * std::tan(degrees_to_radians(fov / 2));
		double viewport_width = viewport_height * aspect_ratio;

		Vec3 viewport_center = look_from + focal_length * viewing_direction;

		// construct viewport onb
		Vec3 u, v, w;
		Vec3 temp(0.0, 0.0, 1.0);  // DEPENDANT ON WHERE THE CAM IS LOOKING

		u = viewing_direction * -1.0;          // out of viewport (towards camera)
		v = u.cross(temp).normalized() * -1.0; // viewport left to right
		w = u.cross(v).normalized() * -1.0;    // viewport top to bottom

		// construct viewport
		viewport_right = v * viewport_width;
		viewport_down = w * viewport_height;
		viewport_dx = viewport_right / image_width;
		viewport_dz = viewport_down / image_height;

		pixel00_location = viewport_center - (viewport_down / 2) - (viewport_right / 2) + ((viewport_dx + viewport_dz) / 2);

		samples_count = samples;
	}



	// ctors
	Camera() = default;
	Camera(const int width, const double i_fov, const unsigned samples, const Vec3& l_f)
	{
		initialize(width, i_fov, samples, l_f);
	}
};


