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
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#undef main
int main() {
	/*SDL_Window* window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!SDL_GL_CreateContext(window)) {
		throw std::runtime_error("Failed to create OpenGL context");
	}*/
	Window* window = new Window();
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to initialise GLEW");
	}
	//int w = 0;
	//int h = 0;
	stbi_set_flip_vertically_on_load(true);
	Model mdl("bird.obj");
	Model mdl2("bird.obj");
	//unsigned char* data = stbi_load("Image.png", &w, &h, NULL, 4);
	unsigned char whitePixel[] = { 255, 255, 0, 255 }; // RGBA
	int w = 1, h = 1;
	unsigned char* data = whitePixel;
	if (!data) {
		std::cerr << "Failed to load texture image\n";
		return 1;
	}
	const GLfloat positions[] = {
		//  X     Y      Z
		-0.5f,  0.5f, 0.0f,  // Top-left
		-0.5f, -0.5f, 0.0f,  // Bottom-left
		 0.5f, -0.5f, 0.0f,  // Bottom-right

		-0.5f,  0.5f, 0.0f,  // Top-left
		 0.5f, -0.5f, 0.0f,  // Bottom-right
		 0.5f,  0.5f, 0.0f   // Top-right
	};

	const GLfloat colors[] = {
		1.0f,0.0f,0.0f,1.0f,
		0.0f,1.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,1.0f
	};

	const GLfloat texCoords[] = {
	0.0f, 1.0f,  // Top-left
	0.0f, 0.0f,  // Bottom-left
	1.0f, 0.0f,  // Bottom-right

	0.0f, 1.0f,  // Top-left
	1.0f, 0.0f,  // Bottom-right
	1.0f, 1.0f   // Top-right
	};

	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	if (!textureId) {
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//free(data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint colorsVboId = 0;

	glGenBuffers(1, &colorsVboId);

	if (!colorsVboId) {
		throw std::exception();
	}

	glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);

	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);




	GLuint positionsVboId = 0;

	glGenBuffers(1, &positionsVboId);
	if (!positionsVboId) {
		throw std::exception();
	}
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	GLuint texCoordVboId = 0;
	glGenBuffers(1, &texCoordVboId);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

	GLuint vaoId = 0;
	glGenVertexArrays(1, &vaoId);

	if (!vaoId) {
		throw std::exception();
	}
	glBindVertexArray(vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, texCoordVboId);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Shader shader("vertexShader.glsl", "fragmentShader.glsl");
	shader.use();
	shader.setInt("inTexture", 1);

	//const GLchar* vertexShaderSrc =
	//
	//	"uniform mat4 uProjection;"
	//	"uniform mat4 uModel;"
	//	"attribute vec3 aPosition;"
	//	"attribute vec2 aTexCoord;"
	//	"varying vec2 vTexCoord;"
	//	"void main(){"
	//	"gl_Position = uProjection * uModel * vec4(aPosition, 1.0);"
	//	"vTexCoord = aTexCoord;"
	//	"}";

	//GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	//glCompileShader(vertexShaderId);
	//GLint success = 0;
	//glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	throw std::exception();
	//}


	//const GLchar* fragmentShaderSrc =
	//	"uniform sampler2D inTexture;"
	//	"varying vec2 vTexCoord;"
	//	"void main(){"
	//	"vec4 tex = texture2D(inTexture, vTexCoord);"
	//	"gl_FragColor = tex;"
	//	//"gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
	//	"}";


	//GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	//glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	//glCompileShader(fragmentShaderId);
	//glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	//if (!success) {
	//	throw std::exception();
	//}


	//GLuint programId = glCreateProgram();
	//glAttachShader(programId, vertexShaderId);
	//glAttachShader(programId, fragmentShaderId);

	//glBindAttribLocation(programId, 0, "aPosition");
	//glBindAttribLocation(programId, 1, "aColor");
	//glBindAttribLocation(programId, 2, "aTexCoord");

	//glLinkProgram(programId);
	//glGetProgramiv(programId, GL_LINK_STATUS, &success);
	//if (!success) {
	//	throw std::exception();
	//}
	//GLuint uniformId = glGetUniformLocation(programId, "inTexture");
	//if (uniformId == -1) {
	//	throw std::exception();
	//}
	//glUseProgram(programId);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, textureId);
	//glBindVertexArray(mdl.vao_id());
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glUniform1i(uniformId, 1);
	//glUseProgram(0);
	//GLint colorUniformId = glGetUniformLocation(programId, "uColor");
	/*if (colorUniformId == -1) {
		throw std::exception();
	}*/

	//GLint modelLoc = glGetUniformLocation(programId, "uModel");
	//GLint projectionLoc = glGetUniformLocation(programId, "uProjection");

	/*glDetachShader(programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);*/
	float angle = 0.0f;
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glFrontFace(GL_CW);
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
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glUseProgram(programId);
		//glUniform4f(colorUniformId, 0, 1, 0, 1);
		//glBindVertexArray(vaoId);

		glBindVertexArray(mdl.vao_id());
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0, -10, -50.0f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
		
		angle += 1.0f;
		shader.setMat4("uModel", model);
		shader.setMat4("uProjection", projection);
		/*glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));*/
		//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glDrawArrays(GL_TRIANGLES, 0, mdl.vertex_count());
		glBindVertexArray(mdl2.vao_id());
		glm::mat4 model2(1.0f);
		model2 = glm::translate(model2, glm::vec3(20, -10, -50.0f));
		model2 = glm::rotate(model2, glm::radians(angle), glm::vec3(0, 1, 0));

		angle += 1.0f;
		shader.setMat4("uModel", model2);
		//shader.setMat4("uProjection", projection);
		/*glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));*/
		//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glDrawArrays(GL_TRIANGLES, 0, mdl2.vertex_count());

		//glBindVertexArray(mdl2.vao_id());
		//glm::mat4 model2(1.0f);
		//shader.setMat4("uModel", model2);
		//shader.setMat4("uProjection", projection);
		//model2 = glm::translate(model2, glm::vec3(10, -10, -100.0f));  // Positioned differently
		//model2 = glm::rotate(model2, glm::radians(angle), glm::vec3(0, 1, 0));

		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glDrawArrays(GL_TRIANGLES, 0, mdl2.vertex_count());
		glBindVertexArray(0);
		glUseProgram(0);
		

		SDL_GL_SwapWindow(window->getWin());
	}
	return 0;
}