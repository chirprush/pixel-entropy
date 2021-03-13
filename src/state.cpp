#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "state.hpp"
#include "window.hpp"
#include "color.hpp"
#include "event.hpp"

State::State(const Window &window, const std::vector<Color> &colors) {
	this->paused = false;
	this->drawColor = 0;
	this->showDrawColor = false;
	this->cols = window.w / pixl;
	this->rows = window.h / pixl;
	std::vector<std::vector<unsigned char>> buffer(rows, std::vector<unsigned char>(cols, 0));
	this->buffer = buffer;
	this->colors = colors;
}

unsigned char State::at(int x, int y) {
	return buffer[(y + rows) % rows][(x + cols) % cols];
}

void State::render(Window &window) const {
	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			window.renderRect(x * pixl, y * pixl, pixl, pixl, colors[buffer[y][x]]);
		}
	}
	if (showDrawColor) {
		// Draw color border rectangle
		window.renderRect(
			drawColorPadding,
			drawColorPadding,
			drawColorSize + 2 * drawColorBorderPadding,
			drawColorSize + 2 * drawColorBorderPadding,
			drawColorBorder);
		// Draw color rectangle
		window.renderRect(
			drawColorPadding + drawColorBorderPadding,
			drawColorPadding + drawColorBorderPadding,
			drawColorSize,
			drawColorSize,
			colors[drawColor]);
	}
}

void State::update() {
	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			int sum = 0;
			for (int dy = -1; dy <= 1; dy += 2) {
				for (int dx = -1; dx <= 1; dx += 2) {
					sum += this->at(x + dx, y + dy);
				}
			}
			int avg = sum / 4;
			buffer[y][x] = std::max(avg, (int)buffer[y][x]);
		}
	}
}

void State::keyDown(const KeyDownEvent &e) {
	std::string key = e.name;
	if (key == "Space") {
		paused = !paused;
	} else if (key == "D") {
		showDrawColor = !showDrawColor;
	}
}

void State::mouseDown(const MouseDownEvent &e) {
	mouseX = e.x;
	mouseY = e.y;
	if (e.button == MouseButton::Left) {
		isMouseDown = true;
		buffer[mouseY / pixl][mouseX / pixl] = drawColor;
		showDrawColor = false;
	} else if (e.button == MouseButton::Right) {
		drawColor = (drawColor + 1) % colors.size();
		showDrawColor = true;
	}
}

void State::mouseMove(const MouseMoveEvent &e) {
	mouseX = e.x;
	mouseY = e.y;
	if (isMouseDown) {
		buffer[mouseY / pixl][mouseX / pixl] = drawColor;
	}
}

void State::mouseUp(const MouseUpEvent &e) {
	mouseX = e.x;
	mouseY = e.y;
	if (e.button == MouseButton::Left) {
		isMouseDown = false;
	}
}
