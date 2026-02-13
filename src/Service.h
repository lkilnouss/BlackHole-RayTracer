#pragma once
#include "CubeMap.h"
#include <string>
#include <iostream>

void printSpacer()
{
	std::cout << "********************************************************************" << std::endl;
}

void set_parameters(std::string& output_file, int& image_width, int& fov, int& samples, CubeMap& skybox)
{
	printSpacer();
	std::cout << "BlackHole RayTracer" << std::endl;
	printSpacer();

	std::cout << "\nEnter image width (huge performance impact; choose 100-400 for testing and HD for final renders): ";
	std::cin >> image_width;

	std::cout << "\nEnter antialiasing samples (huge performance impact; choose 1 - 10 for fast, 100 for best quality): ";
	std::cin >> samples;

	std::cout << "\nenter fov (recommended 60 - 100): ";
	std::cin >> fov;

	bool det_cm = false;

	while (!det_cm)
	{
		unsigned cm;
		std::cout << "\nchoose skybox (milkyway = 0): ";
		std::cin >> cm;

		try
		{
			std::cout << "\nloading cubemap..." << std::endl;
			skybox = get_cube_map(cm);
			det_cm = true;
		}
		catch (_invalid_cube_map_exception& ex)
		{
			std::cout << "\nException: " << ex.what() << std::endl;
			std::cout << "Try again!" << std::endl;
		}
		catch (std::exception ex)
		{
			std::cout << "\nException: " << ex.what() << std::endl;
			std::cout << "Try again!" << std::endl;
		}
	}

	std::string tmp;
	std::cout << "\nname output file (.ppm): ";
	std::cin >> tmp;
	output_file = tmp + ".ppm";

	printSpacer();

	return;
}