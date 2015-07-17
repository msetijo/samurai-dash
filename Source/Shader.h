#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <GLM/glm.hpp>

#include "Vertexes.h"

class Shader {

public:
	Shader(GLuint id) : mId(id) {}

	void Bind() { glUseProgram(mId); }

	void SetMatrix(const char* name, glm::mat4& m) {
		GLuint location = glGetUniformLocation(mId, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
	};

	void SetVertexAttrib(VertexBuffer& vertex, GLuint index, GLint size, GLsizei stride, const GLvoid* offset) {
		glEnableVertexAttribArray(index);
		vertex.Bind();
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, offset);
	}

	void DisableVertexAttrib(GLuint index) { glDisableVertexAttribArray(index); }

private:
	GLuint mId;
};

#endif