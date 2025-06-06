#include "GameObject.h"

GameObject::GameObject(Model* model, Shader shader, const char* texturePath) : shader(shader), model(model),
texturePath(texturePath), textureId(0) {
	stbi_set_flip_vertically_on_load(true);
	/*Model mdl("bird.obj");
	Model mdl2("bird.obj");*/

	unsigned char whitePixel[] = { 255, 255, 0, 255 };
	int w = 1, h = 1;
	unsigned char* data = whitePixel;
	if (!data) {
		std::cerr << "Failed to load texture image\n";
		return;
	}
	
	//GLuint textureId = 0;
	int texWidth, texHeight, channels;
	unsigned char* image = stbi_load(texturePath, &texWidth, &texHeight, &channels, STBI_rgb_alpha);
	if (!image) {
		std::cerr << "Failed to load image\n";
	}
	glGenTextures(1, &this->textureId);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);

	
	if (!textureId) {
		throw std::exception();
	}
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CW);
	//Draw();
}

GameObject::~GameObject() {

}

void GameObject::Draw(int textureUnit) {
	
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, this->textureId);


	shader.setInt("inTexture", textureUnit);
	//Shader shader("vertexShader.glsl", "fragmentShader.glsl");
	shader.use();
	


}

void GameObject::Update() {
	std::cout << this->GetAABB().x;
}

Model* GameObject::getModel() {
	return model;
}

glm::vec3 GameObject::getPosition() {
	return position;
}

void GameObject::setPosition(glm::vec3 pos) {
	position = pos;
}

