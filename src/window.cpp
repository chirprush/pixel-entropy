#include <SDL2/SDL.h>
#include "window.hpp"

Window::Window(const char *title, int w, int h) {
	this->w = w;
	this->h = h;
	this->running = true;
	SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	this->window = window;
	this->renderer = renderer;
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::renderRect(int x, int y, int w, int h, const Color &color) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Window::clear(const Color &color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
}

void Window::present() {
	SDL_RenderPresent(renderer);
}

void Window::delay(int ms) {
	SDL_Delay(ms);
}
