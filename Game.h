#pragma once
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
#include "Game.h"
#include "Player.h"
class Game
{
private:
	
	Model mdl;
	Model mdl2;
	Window* window;
	Player* obj;
	GameObject* obj2;
	Shader shader;
	float lastTime;
public:
	Game(Window* window, Shader shader);
	void Update();
	
};

