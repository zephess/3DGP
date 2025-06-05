#include "Mesh.h"
#include <stdexcept>

Mesh::Mesh(const GLfloat* positions, size_t positionsSize,
	const GLfloat* texCoords, size_t texCoordsSize,
	int vertexCount) : vertexCount(vertexCount){
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vboPositions);
	if (!vboPositions) {
		throw std::exception();
	}
	glBindBuffer(GL_ARRAY_BUFFER, vboPositions);
	glBufferData(GL_ARRAY_BUFFER, positionsSize, positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &vboTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
	glBufferData(GL_ARRAY_BUFFER, texCoordsSize, texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh() {

}

void Mesh::bind() {
	glBindVertexArray(vao);
}

void Mesh::unbind() {
	glBindVertexArray(0);
}

void Mesh::draw() {
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}