#pragma once

#include "Image.h"
#include "Utility.h"
#include <stdexcept>

class CubeMap
{
private:

	Image x_pos, x_neg, y_pos, y_neg, z_pos, z_neg;

	int determine_face(const Vec3& ray_dir) const;

public:

	CubeMap() = default;
	CubeMap(const Image& pos_x, const Image& neg_x, const Image& pos_y, const Image& neg_y, const Image& pos_z, const Image& neg_z)
	{
		x_pos = pos_x;
		x_neg = neg_x;
		y_pos = pos_y;
		y_neg = neg_y;
		z_pos = pos_z;
		z_neg = neg_z;
	}

	Color get_pixel(const Vec3& ray_dir) const;
};

CubeMap get_cube_map(int i);

class _invalid_cube_map_exception
	: public std::runtime_error
{
public:
	_invalid_cube_map_exception(const std::string& msg) : std::runtime_error(msg) {}
};

