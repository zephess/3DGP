#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stdexcept>
#include "Model.h"
#include "Shader.h"
#include <stb_image.h>
#include <stdexcept>
#include <iostream>
class GameObject {
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	Shader shader;
	Model* model;
	const char* texturePath;
	GLuint textureId;
	float yPos;
	float yVel;
public:
	GameObject();
	GameObject(Model* model, Shader shader, const char* texturePath);
	~GameObject();
	void Draw(int textureUnit);
	void Update();
	Model* getModel();
};