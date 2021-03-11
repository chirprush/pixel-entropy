#include <iostream>
#include <SDL2/SDL.h>
#include "window.hpp"

int main(int argc, char *argv[]) {
	Window window = Window("Entropy", 600, 600);
	SDL_Event e;
	SDL_SetRenderDrawColor(window.renderer, 0x1d, 0x20, 0x21, 0xff);
	while (window.running) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				window.running = false;
			}
		}
		SDL_RenderClear(window.renderer);
		SDL_RenderPresent(window.renderer);
	}
	return 0;
}
