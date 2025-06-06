#include "Player.h"
void Player::HandleInput() {
	SDL_Event evt;
	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {

		case SDL_QUIT:
			SDL_Quit();
			return;
			break;
		case SDL_KEYDOWN:
			switch (evt.key.keysym.sym) {
			case SDLK_SPACE:
				std::cout << "SPACE PRESSED";
				yVel = 20;
				break;
			}
		}
	}
}
void Player::Update(float deltaTime) {
	yVel += -20.0f * deltaTime;
	yPos += yVel * deltaTime;
	xPos += xVel * deltaTime;
	if (xPos <= xMin || xPos >= xMax) {
		
		xVel *= -1;
		if (xVel < 50 && xVel > -50) {
			xVel *= 1.1;
			std::cout << xVel;
		}
		
	}
	if (yPos <= yMin) {
		yPos = yMax - 2;
	}
	if (yPos >= yMax) {
		yPos = yMin + 2;
	}
	setPosition(glm::vec3(xPos, yPos, -50.0f));
	//std::cout << xPos << " " << yPos << std::endl;
}

float Player::GetYPos() {
	return yPos;
}

float Player::GetXPos() {
	return xPos;
}

float Player::GetXVel() {
	return xVel;
}