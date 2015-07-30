#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <GLM/glm.hpp>

#include "Vertexes.h"

#include "Textures.h"

#include "Camera.h"
#include "World.h"

class Shader {

public:
	Shader(GLuint id) : mId(id) {}

	void Bind() { glUseProgram(mId); }

	void SetMatrix(const char* name, glm::mat4& m) {
		GLuint location = glGetUniformLocation(mId, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
	};

	void SetViewProjectionMatrix() {
		SetMatrix("ViewProjectionTransform", World::GetInstance()->GetCamera()->GetViewProjectionMatrix());
	}

	void SetTexture(const char* name, Texture2D& t, GLenum textureUnit) {
		GLuint location = glGetUniformLocation(mId, name);
		t.Bind(textureUnit);
		glUniform1i(location, textureUnit - GL_TEXTURE0);
	}

	void SetTexture(const char* name, TextureCubemap& t, GLenum textureUnit) {
		GLuint location = glGetUniformLocation(mId, name);
		t.Bind(textureUnit);
		glUniform1i(location, textureUnit - GL_TEXTURE0);
	}

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