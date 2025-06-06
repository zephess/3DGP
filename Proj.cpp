#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stdexcept>
#include "Window.h"
#include "Shader.h"
#include "Game.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#undef main
int main() {

	Window* window = new Window();
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to initialise GLEW");
	}
	Shader shader("vertexShader.glsl", "fragmentShader.glsl");
	Shader fullScreen("fullscreenVert.glsl", "fullscreenFrag.glsl");
	
	Game* game = new Game(window, shader, fullScreen);
	bool quit = false;
	while (!quit) {
		SDL_Event ev = { 0 };
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) {
				quit = true;
			}
		}
		game->Update();
		
	}
	return 0;
}