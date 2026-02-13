#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Image.h"



Image::Image(std::string filename)
{
	std::string filepath = "./SkyBox/" + filename;

	// init loading of image
	int w, h, channels;
	unsigned char* image_data = stbi_load(filepath.c_str(), &w, &h, &channels, 3); // malloc!

	// check for healthy image
	if (image_data == nullptr)
	{
		std::cout << "Could not read image file: " << filename << std::endl;
		std::abort();
	}

	// init members
	width = w;
	height = h;

	// load image into vector (member)
	unsigned char* working = image_data;
	int total = width * height;
	pixels.reserve(total);

	for (int k = 0; k < total; ++k)
	{
		Color pixel;
		for (int c = 0; c < 3; ++c)
		{
			pixel[c] = srgb_to_linear(*(working + c) / 255.0);
		}
		pixels.push_back(pixel);
		working += 3;
	}

	// deallocate memory -> data is on stack now instead of heap
	stbi_image_free(image_data);
}


