#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
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
	std::vector<std::vector<unsigned char>> swap(rows, std::vector<unsigned char>(cols, 0));
	this->buffer = buffer;
	this->swap = swap;
	this->colors = colors;
}

void State::clear() {
	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			buffer[y][x] = 0;
			swap[y][x] = 0;
		}
	}
}

unsigned char State::get(int x, int y) {
	return buffer[(y + rows) % rows][(x + cols) % cols];
}

void State::set(int x, int y, unsigned char value) {
	swap[(y + rows) % rows][(x + cols) % cols] = value;
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
			int value = get(x, y);
			if (value != 0) {
				set(x, y, value);
				int dx = (rand() % 3) - 1;
				int dy = (rand() % 3) - 1;
				set(x + dx, y + dy, value);
			}
		}
	}
	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			buffer[y][x] = swap[y][x];
		}
	}
}

void State::keyDown(const KeyDownEvent &e) {
	std::string key = e.name;
	if (key == "Space") {
		paused = !paused;
	} else if (key == "D") {
		showDrawColor = !showDrawColor;
	} else if (key == "C") {
		clear();
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
