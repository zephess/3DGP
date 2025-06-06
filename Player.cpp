#include "Player.h"
void Player::HandleInput() {
	SDL_Event evt;
	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {

		case SDL_QUIT:
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
}

float Player::GetYPos() {
	return yPos;
}