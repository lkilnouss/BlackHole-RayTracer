#pragma once

#include <fstream>

#include "Vec3.h"
using Color = msl::Vec3;

double gamma_corrected(double rgb_value);
void write_color(std::ofstream& out, const Color& c);
Color color_multiplication(const Color& first, const Color& second);
double srgb_to_linear(double c);

