#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stdexcept>

class GameObject {
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
public:
	GameObject();
	~GameObject();
	void Draw();

};