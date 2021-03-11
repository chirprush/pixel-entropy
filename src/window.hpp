#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>

struct Window {
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool running;
	int w;
	int h;

	Window(const char *title, int w, int h);
	~Window();
};

#endif // WINDOW_HPP
