#pragma once
#include <GL/glew.h>

class Mesh
{
private:
	GLuint vao;
	GLuint vboPositions;
	GLuint vboTexCoords;
	int vertexCount;
public:
	Mesh(const GLfloat* positionsVboId, size_t positionsSize,
		const GLfloat* texCoords, size_t texCoordsSize,
		int vertexCount);
	~Mesh();
	void bind();
	void unbind();
	void draw();
};

