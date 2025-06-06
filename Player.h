#pragma once
#include "GameObject.h"
#include <SDL2/SDL.h>

class Player : public GameObject
{
	using GameObject::GameObject;
private: 
	float yVel;
	float yPos;
public:
	//Player(Model* model, Shader shader, const char* texturePath);
	void Update(float deltaTime);
	void HandleInput();
	float GetYPos();
};

