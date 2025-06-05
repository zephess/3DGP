#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stdexcept>
#include "Model.h"
#include "Window.h"
#include "GameObject.h"
#include "Shader.h"
#include "Mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#undef main
int main() {

	Window* window = new Window();
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to initialise GLEW");
	}

	stbi_set_flip_vertically_on_load(true);
	Model mdl("bird.obj");
	Model mdl2("bird.obj");

	unsigned char whitePixel[] = { 255, 255, 0, 255 }; 
	int w = 1, h = 1;
	unsigned char* data = whitePixel;
	if (!data) {
		std::cerr << "Failed to load texture image\n";
		return 1;
	}

	GLuint textureId = 0;
	int texWidth, texHeight, channels;
	unsigned char* image = stbi_load("myGrid.png", &texWidth, &texHeight, &channels, STBI_rgb_alpha);
	if (!image) {
		std::cerr << "Failed to load image\n";
	}
	glGenTextures(1, &textureId);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);

	glGenTextures(1, &textureId);
	if (!textureId) {
		throw std::exception();
	}

	//glBindTexture(GL_TEXTURE_2D, textureId);



	Shader shader("vertexShader.glsl", "fragmentShader.glsl");
	shader.use();
	shader.setInt("inTexture", 1);


	//glActiveTexture(GL_TEXTURE0 + 1);
	/*glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);*/
	
	float angle = 0.0f;
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	bool quit = false;
	while (!quit) {
		SDL_Event ev = { 0 };
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) {
				quit = true;
			}
		}
		shader.use();
		int width = 0;
		int height = 0;

		SDL_GetWindowSize(window->getWin(), &width, &height);

		glViewport(0, 0, width, height);

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		glBindVertexArray(mdl.vao_id());
		
		
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0, -10, -50.0f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
		
		angle += 1.0f;
		shader.setMat4("uModel", model);
		shader.setMat4("uProjection", projection);
		
		glDrawArrays(GL_TRIANGLES, 0, mdl.vertex_count());
		
		glBindVertexArray(mdl2.vao_id());
	

		glm::mat4 model2(1.0f);
		model2 = glm::translate(model2, glm::vec3(20, -10, -50.0f));
		model2 = glm::rotate(model2, glm::radians(angle), glm::vec3(0, 1, 0));

		angle += 1.0f;
		shader.setMat4("uModel", model2);
		
	
		glDrawArrays(GL_TRIANGLES, 0, mdl2.vertex_count());
	
		glUseProgram(0);
		

		SDL_GL_SwapWindow(window->getWin());
	}
	return 0;
}