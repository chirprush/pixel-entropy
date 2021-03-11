#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include "color.hpp"

struct Window {
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool running;
	int w;
	int h;

	Window(const char *title, int w, int h);
	~Window();

	void clear(const Color &color);
	void present();

	void delay(int ms);
};

#endif // WINDOW_HPP
