#include "event.hpp"
#include <SDL2/SDL.h>

static constexpr MouseButton code_to_button(int code) {
	switch (code) {
	case SDL_BUTTON_MIDDLE:
		return MouseButton::Middle;
	case SDL_BUTTON_RIGHT:
		return MouseButton::Right;
	case SDL_BUTTON_LEFT:
	default:
		return MouseButton::Left;
	}
}

bool Event::get_event(Event *e) {
	SDL_Event sdl_event;
	if (!SDL_PollEvent(&sdl_event)) {
		return false;
	}
	switch (sdl_event.type) {
	case SDL_QUIT: {
		e->type = EventType::Quit;
		e->quit = QuitEvent();
		break;
	}
	case SDL_MOUSEBUTTONDOWN: {
		e->type = EventType::MouseDown;
		MouseButton button = code_to_button(sdl_event.button.button);
		e->mouse_down = MouseDownEvent(button, sdl_event.button.x, sdl_event.button.y);
		break;
	}
	case SDL_MOUSEMOTION: {
		e->type = EventType::MouseMove;
		e->mouse_move = MouseMoveEvent(sdl_event.motion.x, sdl_event.motion.y);
		break;
	}
	default: {
		e->type = EventType::Unhandled;
		e->unhandled = UnhandledEvent();
		break;
	}
	}
	return true;
}

QuitEvent::QuitEvent() {}

MouseDownEvent::MouseDownEvent(MouseButton button, int x, int y) {
	this->button = button;
	this->x = x;
	this->y = y;
}

MouseMoveEvent::MouseMoveEvent(int x, int y) {
	this->x = x;
	this->y = y;
}

UnhandledEvent::UnhandledEvent() {}
