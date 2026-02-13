#include "Color.h"
#include "Utility.h"

void write_color(std::ofstream& out, const Color& c)
{
	double r = c.x();
	double g = c.y();
	double b = c.z();

	// gamma correct
	r = gamma_corrected(r);
	g = gamma_corrected(g);
	b = gamma_corrected(b);

	// convert to bit space
	int bit_r = static_cast<int>(255 * clamp(r, 0.0, 0.999));
	int bit_g = static_cast<int>(255 * clamp(g, 0.0, 0.999));
	int bit_b = static_cast<int>(255 * clamp(b, 0.0, 0.999));

	out << bit_r << " " << bit_g << " " << bit_b << "\n";
}

double gamma_corrected(double rgb_value)
{
	if (rgb_value > 0.0)
		return std::sqrt(rgb_value);
	else
		return 0.0;
}

Color color_multiplication(const Color& first, const Color& second)
{
	return Color(first.x() * second.x(), first.y() * second.y(), first.z() * second.z());
}

double srgb_to_linear(double c)
{
	if (c <= 0.4045)
		return c / 12.92;
	else
		return std::pow((c + 0.055) / 1.055, 2.4);
}