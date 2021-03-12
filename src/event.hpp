#ifndef EVENT_HPP
#define EVENT_HPP

struct QuitEvent {
	QuitEvent();
};

enum class MouseButton { Left, Middle, Right };

struct MouseDownEvent {
	MouseButton button;
	int x, y;

	MouseDownEvent(MouseButton button, int x, int y);
};

struct MouseMoveEvent {
	int x, y;

	MouseMoveEvent(int x, int y);
};

struct UnhandledEvent {
	UnhandledEvent();
};

enum class EventType { Quit, MouseDown, MouseMove, Unhandled };

struct Event {
	EventType type;

	union {
		QuitEvent quit;
		MouseDownEvent mouse_down;
		MouseMoveEvent mouse_move;
		UnhandledEvent unhandled;
	};

	static bool get_event(Event *e);
};

#endif // EVENT_HPP
