#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>
Shader::Shader(std::string vertexPath,std::string fragmentPath) {
	GLuint vertShader = loadShader(vertexPath, GL_VERTEX_SHADER);
	GLuint fragShader = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

	programId = glCreateProgram();
	glAttachShader(programId, vertShader);
	glAttachShader(programId, fragShader);
	glLinkProgram(programId);
	glDetachShader(programId, vertShader);
	glDeleteShader(vertShader);
	glDetachShader(programId, fragShader);
	glDeleteShader(fragShader);
}
Shader::~Shader() {

}

void Shader::use() {
	glUseProgram(programId);
}

void Shader::unuse() {
	glUseProgram(0);
}

GLuint Shader::getProgramId() {
	return programId;
}

std::string Shader::loadFile(std::string& path) {
	std::ifstream file(path);
	if (!file) {
		throw std::runtime_error("Failed to open shader file: " + path);
	}
	std::stringstream buff;
	buff << file.rdbuf();
	return buff.str();
}

GLuint Shader::loadShader(std::string& path, GLenum type) {
	std::string src = loadFile(path);
	const char* csrc = src.c_str();
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &csrc, nullptr);
	glCompileShader(shader);
	GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		throw std::runtime_error("Shader compilation failed (" + path + "):\n" + std::string(infoLog));
	}
	return shader;
}

void Shader::setMat4(std::string name, glm::mat4 matrix) {
	GLuint loc = glGetUniformLocation(programId, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setInt(std::string name, int value) {
	GLuint loc = glGetUniformLocation(programId, name.c_str());
	glUniform1i(loc, value);
}