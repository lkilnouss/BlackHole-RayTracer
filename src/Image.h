#pragma once

#include <string>
#include <vector>

#include "Color.h"


struct Image
{

	int width;
	int height;
	std::vector<Color> pixels;

	//ctors
	Image() = default;
	Image(std::string filename);

	const Color& at(int index) const
	{
		return pixels.at(index);
	}

	Color& at(int index)
	{
		return pixels.at(index);
	}
};
