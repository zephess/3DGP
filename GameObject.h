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

struct AABB {
	float x, y, width, height;
	bool Intersects(AABB other) {
		return (x + width < other.x ||
			x > other.x + other.width ||
			y + height < other.y ||
			y > other.y + other.height);
	}
};

class GameObject {
private:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation;
	glm::vec3 scale;
	Shader shader;
	Model* model;
	const char* texturePath;
	GLuint textureId;
	float yPos;
	float yVel;
	float width = 50.0f;
	float height =50.0f;

public:
	GameObject();
	GameObject(Model* model, Shader shader, const char* texturePath);
	~GameObject();
	void Draw(int textureUnit);
	void Update();
	Model* getModel();
	AABB GetAABB() {
		return AABB{
		position.x,  
		position.y,
		width,       
		height
		};
	}
	glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);
	
};

