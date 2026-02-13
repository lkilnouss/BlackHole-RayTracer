#include "CubeMap.h"

// private
int CubeMap::determine_face(const Vec3& ray_dir) const
{
	double x = std::abs(ray_dir.x());
	double y = std::abs(ray_dir.y());
	double z = std::abs(ray_dir.z());

	if (x > y && x > z)
	{
		return ray_dir.x() > 0.0 ? 1 : 2;
	}

	else if (y > x && y > z)
	{
		return ray_dir.y() > 0.0 ? 3 : 4;
	}

	else
	{
		return ray_dir.z() > 0.0 ? 5 : 6;
	}
}

Color CubeMap::get_pixel(const Vec3& ray_dir) const
{
	int facing = determine_face(ray_dir);

	switch (facing)
	{
	case 1: // positive x
	{
		// project image basis vectors between -1 and 1
		double v = -1 * ray_dir.z() / std::abs(ray_dir.x());
		double u = -1 * ray_dir.y() / std::abs(ray_dir.x());

		//normalize
		u = 0.5 * (u + 1);
		v = 0.5 * (v + 1);

		// map to row & column
		int col = u * (x_pos.width - 1);
		int row = v * (x_pos.height - 1);

		return x_pos.at(row * x_pos.width + col);
	}

	case 2: // negative x
	{
		double v = -1 * ray_dir.z() / std::abs(ray_dir.x());
		double u = 1 * ray_dir.y() / std::abs(ray_dir.x());

		u = 0.5 * (u + 1);
		v = 0.5 * (v + 1);

		int col = u * (x_neg.width - 1);
		int row = v * (x_neg.height - 1);

		return x_neg.at(row * x_neg.width + col);
	}

	case 3: // positive y
	{
		double u = ray_dir.x() / std::abs(ray_dir.y());
		double v = -1 * ray_dir.z() / std::abs(ray_dir.y());

		u = 0.5 * (u + 1);
		v = 0.5 * (v + 1);

		int col = u * (y_pos.width - 1);
		int row = v * (y_pos.height - 1);

		return y_pos.at(row * y_pos.width + col);
	}

	case 4: // negative y
	{
		double u = -1 * ray_dir.x() / std::abs(ray_dir.y());
		double v = -1 * ray_dir.z() / std::abs(ray_dir.y());

		u = 0.5 * (u + 1);
		v = 0.5 * (v + 1);

		int col = u * (y_neg.width - 1);
		int row = (1 - v) * (y_neg.height - 1);

		return y_neg.at(row * y_neg.width + col);
	}

	case 5: // positive z
	{
		double u = ray_dir.x() / std::abs(ray_dir.z());
		double v = ray_dir.y() / std::abs(ray_dir.z());

		u = 0.5 * (u + 1);
		v = 0.5 * (v + 1);

		int col = u * (z_pos.width - 1);
		int row = (1 - v) * (z_pos.height - 1);

		return z_pos.at(row * z_pos.width + col);
	}

	case 6: // negative z
	{
		double u = 1 * ray_dir.x() / std::abs(ray_dir.z());
		double v = -1 * ray_dir.y() / std::abs(ray_dir.z());

		u = 0.5 * (u + 1);
		v = 0.5 * (v + 1);

		int col = u * (z_neg.width - 1);
		int row = (1 - v) * (z_neg.height - 1);

		return z_neg.at(row * z_neg.width + col);
	}
	}
}

CubeMap get_cube_map(int i)
{

		if (i == 0)
			return CubeMap(Image("milky-way/cm_px.png"), Image("milky-way/cm_nx.png"), Image("milky-way/cm_py.png"), Image("milky-way/cm_ny.png"), Image("milky-way/cm_pz.png"), Image("milky-way/cm_nz.png"));
		else
			throw _invalid_cube_map_exception("invalid cubemap!");
}