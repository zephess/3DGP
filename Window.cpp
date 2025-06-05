#include "Window.h"
#include <stdexcept>
Window::Window() {
	SDL_Window* window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!SDL_GL_CreateContext(window)) {
		throw std::runtime_error("Failed to create OpenGL context");
	}
	win = window;
}
Window::~Window() {

}

void Window::Init(Window window) {

}

SDL_Window* Window::getWin() {
	return win;
}