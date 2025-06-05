#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader {
private:
	GLuint programId;
	GLuint loadShader(std::string& path, GLenum type);
	std::string loadFile(std::string& path);
public:
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();
	void use();
	void unuse();
	GLuint getProgramId();
	void setMat4(std::string name, glm::mat4 matrix);
	void setInt(std::string name, int value);


};