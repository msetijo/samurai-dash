#ifndef VERTEXES_H
#define VERTEXES_H

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

class VertexBuffer {

public:
	VertexBuffer();
	~VertexBuffer();

	void Bind();

	void SetData(GLvoid* data, GLsizeiptr size);

	GLsizeiptr GetSize() { return mSize; }

private:
	GLuint mId;
	GLsizeiptr mSize;
};

class VertexArray {

public:
	VertexArray();
	~VertexArray();

	void Bind();
private:
	GLuint mId;
};

#endif