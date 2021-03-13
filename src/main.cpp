#include <SDL2/SDL.h>
#include <vector>
#include "state.hpp"
#include "window.hpp"
#include "color.hpp"
#include "event.hpp"

constexpr Color BACKGROUND_COLOR = 0x1d2021;
constexpr int delay = 1000 / 30;

int main(int argc, char *argv[]) {
	std::vector<Color> colors = { BACKGROUND_COLOR, Color(0x02006c), Color(0x61afef), Color(0xefefef) };
	Window window = Window("Entropy", 600, 600);
	State state = State(window, colors);
	Event e = {};
	while (window.running) {
		while (Event::get_event(&e)) {
			switch (e.type) {
			case EventType::Quit:
				window.running = false;
				break;
			case EventType::KeyDown:
				state.keyDown(e.key_down);
				break;
			case EventType::MouseDown:
				state.mouseDown(e.mouse_down);
				break;
			case EventType::MouseMove:
				state.mouseMove(e.mouse_move);
				break;
			case EventType::MouseUp:
				state.mouseUp(e.mouse_up);
				break;
			default:
				continue;
			}
		}
		window.clear(BACKGROUND_COLOR);
		state.render(window);
		if (!state.paused) {
			state.update();
		}
		window.present();
		window.delay(delay);
	}
	return 0;
}
