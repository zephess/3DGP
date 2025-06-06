#include "Game.h"

Game::Game(Window* window, Shader shader) : window(window), shader(shader), mdl("bird.obj"), mdl2("Bomb.obj") {
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to initialise GLEW");
	}
	
	stbi_set_flip_vertically_on_load(true);
	
	
	obj = new Player(&mdl, shader, "myGrid.png");
	obj2 = new GameObject(&mdl2, shader, "redGrid.png");


	lastTime = SDL_GetTicks();
	float ypos = 0.0f;
	float angle = 0.0f;
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void Game::Update() {

	if (obj->GetAABB().Intersects(obj2->GetAABB())) {
		std::cout << "Collision detected!" << std::endl;
	}
	Uint32 currentTime = SDL_GetTicks();
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	shader.use();
	int width = 0;
	int height = 0;

	SDL_GetWindowSize(window->getWin(), &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	model2 = glm::translate(model2, glm::vec3(-20, 0, -50.0f));
	//model2 = glm::scale(model2, glm::vec3(0.05f, 0.05f, 0.05f));
	//model2 = glm::rotate(model2, glm::radians(angle), glm::vec3(0, 1, 0));
	//angle += 1.0f;
	shader.setMat4("uModel", model2);
	obj2->Draw(1);
	glBindVertexArray(obj2->getModel()->vao_id());
	glDrawArrays(GL_TRIANGLES, 0, obj2->getModel()->vertex_count());

	obj->HandleInput();
	obj->Update(deltaTime);
	glUseProgram(0);


	SDL_GL_SwapWindow(window->getWin());
}