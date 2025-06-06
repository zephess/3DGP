#include "Game.h"

Game::Game(Window* window, Shader shader, Shader shader2) : window(window), shader(shader), mdl("bird.obj"), mdl2("Bomb.obj"), mdl3("Apple.obj"), fullscreenShader(shader2){
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to initialise GLEW");
	}
	
	stbi_set_flip_vertically_on_load(true);
	
	
	obj = new Player(&mdl, shader, "myGrid.png");
	obj2 = new GameObject(&mdl2, shader, "redGrid.png");
	obj3 = new GameObject(&mdl3, shader, "greenGrid.png");

	lastTime = SDL_GetTicks();
	float ypos = 0.0f;
	float angle = 0.0f;
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	obj2->setPosition(glm::vec3(-10, -10, -50.0f));
	
	const GLfloat quadPositions[] = {
		-1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,

		-1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f
	};

	const GLfloat quadTexCoords[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	const int quadVertexCount = 6;
	fullscreenQuad = new Mesh(quadPositions, sizeof(quadPositions),
		quadTexCoords, sizeof(quadTexCoords),
		quadVertexCount);
}

Game::~Game() {
	delete obj;
	delete obj2;
	delete obj3;
	delete fullscreenQuad;
}
void Game::Update() {

	float time = SDL_GetTicks() / 1000.0f;
	int width, height;
	SDL_GetWindowSize(window->getWin(), &width, &height);
	
	if (obj->GetAABB().Intersects(obj2->GetAABB())) {
		SDL_Quit();
		return;
		//std::cout << "Collision detected!" << std::endl;
	}
	if (obj->GetAABB().Intersects(obj3->GetAABB())) {
		obj3->setPosition(glm::vec3(-20 + (rand() % (20 + 20 + 1)), -25 + (rand() % (10 + 25 + 1)), -50.0f));
		obj2->setPosition(glm::vec3(-20 + (rand() % (20 + 20 + 1)), -25 + (rand() % (10 + 25 + 1)), -50.0f));
		//std::cout << obj3->getPosition().x << " " << obj3->getPosition().y;
		//std::cout << "Collision detected!" << std::endl;
	}
	//std::cout << obj2->GetAABB().x;
	//obj2->Update();
	Uint32 currentTime = SDL_GetTicks();
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	shader.use();
	//int width = 0;
	//int height = 0;

	SDL_GetWindowSize(window->getWin(), &width, &height);
	glViewport(0, 0, width, height);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	fullscreenShader.use();

	fullscreenShader.setFloat("time", time);
	fullscreenQuad->bind();
	fullscreenQuad->draw();
	fullscreenQuad->unbind();
	

	
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	shader.use();
	//glClear(GL_DEPTH_BUFFER_BIT);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	shader.setMat4("uProjection", projection);
	glm::mat4 model(1.0f);


	model = glm::translate(model, glm::vec3(obj->GetXPos(), obj->GetYPos(), -50.0f));
	if (obj->GetXVel() < 0) {
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
	}
	else {
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	}

	//angle += 1.0f;
	//ypos -= 0.05f;
	shader.setMat4("uModel", model);
	obj->Draw(0);
	glBindVertexArray(obj->getModel()->vao_id());
	glDrawArrays(GL_TRIANGLES, 0, obj->getModel()->vertex_count());
	

	glm::mat4 model2(1.0f);
	model2 = glm::translate(model2, glm::vec3(obj2->GetAABB().x, obj2->GetAABB().y +10, - 50.0f));
	//model2 = glm::scale(model2, glm::vec3(0.05f, 0.05f, 0.05f));
	//model2 = glm::rotate(model2, glm::radians(angle), glm::vec3(0, 1, 0));
	//angle += 1.0f;
	shader.setMat4("uModel", model2);
	obj2->Draw(1);
	glBindVertexArray(obj2->getModel()->vao_id());
	glDrawArrays(GL_TRIANGLES, 0, obj2->getModel()->vertex_count());

	glm::mat4 model3(1.0f);
	
	model3 = glm::translate(model3, glm::vec3(obj3->GetAABB().x, obj3->GetAABB().y + 10, -50.0f));
	model3 = glm::scale(model3, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("uModel", model3);
	obj3->Draw(2);
	glBindVertexArray(obj3->getModel()->vao_id());
	glDrawArrays(GL_TRIANGLES, 0, obj3->getModel()->vertex_count());

	obj->HandleInput();
	obj->Update(deltaTime);
	glUseProgram(0);


	SDL_GL_SwapWindow(window->getWin());
}