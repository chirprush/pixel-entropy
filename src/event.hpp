#ifndef EVENT_HPP
#define EVENT_HPP

struct QuitEvent {
	QuitEvent();
};

struct KeyDownEvent {
	const char *name;

	KeyDownEvent(const char *name);
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

struct MouseUpEvent {
	MouseButton button;
	int x, y;

	MouseUpEvent(MouseButton button, int x, int y);
};

struct UnhandledEvent {
	UnhandledEvent();
};

enum class EventType { Quit, KeyDown, MouseDown, MouseMove, MouseUp, Unhandled };

struct Event {
	EventType type;

	union {
		QuitEvent quit;
		KeyDownEvent key_down;
		MouseDownEvent mouse_down;
		MouseMoveEvent mouse_move;
		MouseUpEvent mouse_up;
		UnhandledEvent unhandled;
	};

	static bool get_event(Event *e);
};

#endif // EVENT_HPP
