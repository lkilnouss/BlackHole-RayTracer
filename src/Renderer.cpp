#include "Renderer.h"

#include "Color.h"

// public
void Renderer::render(const BlackHole& SgrA, const std::string filename)
{
	// open file 
	std::string path = "./output/" + filename;
	std::ofstream image(path);
	if (!(image.is_open()))
	{
		std::cout << "Failed to open file!" << std::endl;
	}

	// Render to file
	image << "P3\n" << cam.image_width << " " << cam.image_height << std::endl << "255" << std::endl;

	std::cout << "Progress: ";

	for (int j = 0; j < cam.image_height; ++j)
	{
		if ((j % (cam.image_height / 10) == 0) && j != 0)
			std::cout << "*";
		for (int i = 0; i < cam.image_width; ++i)
		{
			bool GR = true; // BLACKHOLE SWITCH

			if (GR)
			{
				Color pixel_color(0.0, 0.0, 0.0);

				for (int s = 0; s < cam.samples_count; s++) // samples_count is 1
				{
					Vec3 pixel_ray_direction = get_ray_direction(i, j);
					RelativisticRay pixel_ray(cam.look_from, pixel_ray_direction, SgrA);
					pixel_color += ray_color(pixel_ray, SgrA);
				}

				pixel_color /= cam.samples_count;

				write_color(image, pixel_color);
			}
			else
			{
				Color pixel_color(0.0, 0.0, 0.0);
				Vec3 d = get_ray_direction(i, j).normalized();
				pixel_color = cube_map.get_pixel(d);

				write_color(image, pixel_color);
			}

		}
	}
	std::cout << "\nRendering to file complete!\n" << std::endl;
}

// private
Vec3 Renderer::get_ray_direction(const int i, const int j) const
{
	double dx_offset = random_double() - 0.5; // to do: try "-1.0";
	double dz_offset = random_double() - 0.5;

	Point3 ray_destination = cam.pixel00_location + (i + dx_offset) * cam.viewport_dx + (j + dz_offset) * cam.viewport_dz;

	Vec3 ray_direction = (ray_destination - cam.look_from).normalized();

	return Vec3(ray_direction);
}

Color Renderer::ray_color(RelativisticRay& ray, const BlackHole& SgrA) const
{
	// computing impact parameter
	double b = ray.impact_parameter;
	double b_crit = 3 * sqrt_three * SgrA.mass;

	if (b < b_crit)
		return Color(0.0, 0.0, 0.0);
	else
		return deflected_ray_color(ray, SgrA);
}

Color Renderer::deflected_ray_color(RelativisticRay& ray, const BlackHole& SgrA) const
{
	Vec3 final_ray_direction = calculate_sky_direction(ray, SgrA).normalized();

	return cube_map.get_pixel(final_ray_direction);
}

Vec3 Renderer::calculate_sky_direction(RelativisticRay& ray, const BlackHole& SgrA) const
{
	ray.calculate_r_min();

	while (true)
	{
		ray.update(delta_phi(ray));

		if (ray.r > 50.0 * SgrA.r_s)
			break;
	}
	// reconstruct final direction
	Vec3 e_r_final = (std::cos(ray.phi) * ray.plane_er + std::sin(ray.phi) * ray.plane_ephi).normalized();

	return e_r_final;
}

double Renderer::delta_phi(const RelativisticRay& ray) const
{
	const double min_step = 1e-3; // these could be shifted by 1e-1 for an increase in precision but also 10x (!) longer rendering
	const double max_step = 1e-1;
	const double base_step = 1e-2;

	double d_phi = base_step * 1 / std::sqrt(std::max(ray.dr_dphi_squared, 0.0) + CONST_EPS);

	return clamp(d_phi, min_step, max_step);
}
