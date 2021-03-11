#include <iostream>
#include <SDL2/SDL.h>
#include "window.hpp"
#include "color.hpp"

constexpr Color BACKGROUND_COLOR = 0x1d2021;
constexpr int delay = 1000 / 30;

int main(int argc, char *argv[]) {
	Window window = Window("Entropy", 600, 600);
	SDL_Event e;
	while (window.running) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				window.running = false;
			}
		}
		window.clear(BACKGROUND_COLOR);
		window.present();
		window.delay(delay);
	}
	return 0;
}
