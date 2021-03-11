#ifndef COLOR_HPP
#define COLOR_HPP

struct Color {
	unsigned int r, g, b, a;

	constexpr Color(int hex) : r(hex >> 16 & 0xFF), g(hex >> 8 & 0xFF), b(hex >> 0 & 0xFF), a(0xFF) {}
};

#endif // COLOR_HPP
