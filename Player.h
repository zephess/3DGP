#pragma once
#include "GameObject.h"
#include <SDL2/SDL.h>

class Player : public GameObject
{
	using GameObject::GameObject;
private: 
	float yVel;
	float yPos;
	float xPos;
	float xVel = 10.0f;
	float xMin = -30.0f;
	float xMax = 30.0f;
	float yMax = 30.0f;
	float yMin = -30.0f;
public:
	//Player(Model* model, Shader shader, const char* texturePath);
	void Update(float deltaTime);
	void HandleInput();
	float GetYPos();
	float GetXPos();
	float GetXVel();
};

