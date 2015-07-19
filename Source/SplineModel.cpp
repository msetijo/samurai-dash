#include <vector>
#include <algorithm>

#include "SplineModel.h"

#include "World.h"
#include "Camera.h"
#include "RendererHelper.h"
//#include "ParsingHelper.h"

#include <glm/gtc/type_ptr.hpp>

using namespace glm;

SplineModel::SplineModel() : Model(), mControlPoints(), mArray(), mControlPointsBuffer(), mPointsBuffer()
{
}

SplineModel::~SplineModel()
{
}

void SplineModel::Draw()
{
	Shader shader = RendererHelper::GetShader(SHADER_SPLINE);

	shader.Bind();

	shader.SetMatrix("ViewProjectonTransform", World::GetInstance()->GetCamera()->GetViewProjectionMatrix());
	shader.SetMatrix("WorldTransform", GetWorldMatrix());

	mArray.Bind();

	int stride = sizeof(Vertex);
	shader.SetVertexAttrib(mPointsBuffer, 0, 3, stride, 0);
	shader.SetVertexAttrib(mPointsBuffer, 2, 3, stride, (void*)sizeof(vec3));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, mPointsBuffer.GetSize() / sizeof(Vertex));

	shader.DisableVertexAttrib(0);
}

void SplineModel::SetControlPoints(std::vector<Vertex>& controlPoints) {

	mControlPoints.resize(controlPoints.size());
	copy(controlPoints.begin(), controlPoints.end(), mControlPoints.begin());

	mControlPointsBuffer.SetData(&mControlPoints[0], mControlPoints.size() * sizeof(Vertex));
}

void SplineModel::SetPoints(std::vector<Vertex>& points) {

	mPointsBuffer.SetData(&points[0], points.size() * sizeof(Vertex));
}

void SplineModel::Load(ci_istringstream& iss) {

	Model::Load(iss);

	if (HasControlPoints()) {
		mControlPointsBuffer.SetData(&mControlPoints[0], mControlPoints.size() * sizeof(Vertex));
	}
}

bool SplineModel::ParseLine(const std::vector<ci_string> &token)
{
	bool r = Model::ParseLine(token);

	if (r) {
		return true;
	}
	else if (token[0] == "controlPoint") {

		vec3 controlPoint;
		vec3 color(1.0f,0.0f,0.0f);
		
		PasingHelper::parseVec3(token, controlPoint);
		
		mControlPoints.push_back({ controlPoint, color });
	}
	else {
		return false;
	}
}