#pragma once
#include <SDL2/SDL.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
class Window {
private:
	float w;
	float h;
	SDL_Window* win;
public:
	Window();
	~Window();
	void Init(Window window);
	SDL_Window* getWin();
};