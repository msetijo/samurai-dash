#include "Vertexes.h"

VertexBuffer::VertexBuffer() : mId() {
	glGenBuffers(1, &mId);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &mId);
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, mId);
}

void VertexBuffer::SetData(GLvoid* data, GLsizeiptr size) {
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	mSize = size;
}

VertexArray::VertexArray() : mId() {
	glGenVertexArrays(1, &mId);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &mId);
}

void VertexArray::Bind() {
	glBindVertexArray(mId);
}