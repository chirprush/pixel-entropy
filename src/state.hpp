#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include "color.hpp"
#include "window.hpp"
#include "event.hpp"

constexpr int pixl = 5;

constexpr int drawColorPadding = 5;
constexpr int drawColorBorderPadding = 10;
constexpr int drawColorSize = 30;
constexpr Color drawColorBorder = 0x5a5a5a;

struct State {
	bool paused;
	bool isMouseDown;
	bool showDrawColor;
	unsigned char drawColor;
	int mouseX, mouseY;
	int cols;
	int rows;
	std::vector<std::vector<unsigned char>> buffer;
	std::vector<std::vector<unsigned char>> swap;

	// The length of colors should never really change, so I'm not
	// quite the happiest using std::vector here, but the alternative
	// is using std::array and templating this class, which just
	// doesn't sit right with me either.
	std::vector<Color> colors;

	State(const Window &window, const std::vector<Color> &colors);

	void clear();

	unsigned char get(int x, int y);
	void set(int x, int y, unsigned char value);

	void render(Window &window) const;
	void update();

	void keyDown(const KeyDownEvent &e);

	void mouseDown(const MouseDownEvent &e);
	void mouseMove(const MouseMoveEvent &e);
	void mouseUp(const MouseUpEvent &e);
};

#endif // STATE_HPP
