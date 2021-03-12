#include <iostream>
#include <SDL2/SDL.h>
#include "window.hpp"
#include "color.hpp"
#include "event.hpp"

constexpr Color BACKGROUND_COLOR = 0x1d2021;
constexpr int delay = 1000 / 30;

int main(int argc, char *argv[]) {
	Window window = Window("Entropy", 600, 600);
	Event e = {};
	while (window.running) {
		while (Event::get_event(&e)) {
			switch (e.type) {
			case EventType::Quit:
				window.running = false;
				break;
			case EventType::MouseDown:
				break;
			default:
				continue;
			}
		}
		window.clear(BACKGROUND_COLOR);
		window.present();
		window.delay(delay);
	}
	return 0;
}
