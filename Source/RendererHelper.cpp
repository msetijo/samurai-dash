#include "RendererHelper.h"

Shader RendererHelper::GetShader(ShaderType type) {

	unsigned int prevShader = Renderer::GetCurrentShader();

	Renderer::SetShader(type);
	GLuint shaderId = Renderer::GetShaderProgramID();

	Renderer::SetShader((ShaderType)prevShader);

	return Shader(shaderId);
}