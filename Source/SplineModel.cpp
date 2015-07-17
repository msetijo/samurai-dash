#include "SplineModel.h"

#include "World.h"
#include "Camera.h"
#include "RendererHelper.h"

#include <vector>

#include <glm/gtc/type_ptr.hpp>

using namespace glm;

SplineModel::SplineModel() : Model(), mArray(), mControlPoints(), mPoints()
{
	srand(time(nullptr));

	int N = 20;
	int M = 5;
	int W = 20; // the track width
	int RPx = 20;
	int RPy = 3;

	std::vector<Vertex> controlPoints;
	std::vector<Vertex> points;

	controlPoints.push_back({
		vec3(0, 5, 0),
		vec3(1.0f, 0.0f, 0.0f)
	});
	for (int i = 1; i < N; i++) {
		Vertex prev = controlPoints[i - 1];

		int signx = (rand() % 2 ? 1 : -1);
		int signy = (rand() % 2 ? 1 : -1);
		int dx = rand() % RPx;
		int dy = rand() % RPy;

		Vertex next = {
			prev.position + vec3(dx, signy * dy, 0),
			vec3(1.0f,0.0f,0.0f)
		};
		controlPoints.push_back(next);
	}

	vec3 shift = vec3(0, 0, W);
	
	vec3 red = vec3(1.0f, 0.0f, 0.0f);
	vec3 green = vec3(0.0f, 1.0f, 0.0f);
	vec3 blue = vec3(0.0f, 1.0f, 0.0f);

	bool start = true;
	int flipFlop = 0;
	int flipFlopFloop = 0;

	for (int j = 0; j < N - 3; j+=1) {

		Vertex v1 = controlPoints[j];
		Vertex v2 = controlPoints[j + 1];
		Vertex v3 = controlPoints[j + 2];
		Vertex v4 = controlPoints[j + 3];

		vec3 p1 = v1.position;
		vec3 p2 = v2.position;
		vec3 p3 = v3.position;
		vec3 p4 = v4.position;



		for (float t = 0; t <= 1; t += 1.0f / M) {

			float u3 = t * t * t;
			float u2 = t * t;
			float u = t;

			float six = 1.0f / 6.0f;

			float b0 = six * (-u3 + 3 * u2 - 3 * u + 1);
			float b1 = six * (3 * u3 - 6 * u2 + 4);
			float b2 = six * (-3 * u3 + 3 * u2 + 3 * u + 1);
			float b3 = six * (u3);

			vec3 point = vec3(
				b0 * p1.x + b1 * p2.x + b2 * p3.x + b3 * p4.x,
				b0 * p1.y + b1 * p2.y + b2 * p3.y + b3 * p4.y,
				b0 * p1.z + b1 * p2.z + b2 * p3.z + b3 * p4.z
			);

			if (start) {
				points.push_back({
					point + shift,
					flipFlopFloop == 0 ? red : flipFlopFloop == 1 ? green : blue
				});
				start = false;
			}
			
			if (flipFlop) {
				point += shift;
			}

			points.push_back({
				point,
				flipFlopFloop == 0 ? red : flipFlopFloop == 1 ? green : blue
			});

			flipFlop = (flipFlop + 1) % 2;
			flipFlopFloop = (flipFlopFloop + 1) % 3;
		}
	}

	mControlPoints.SetData(&controlPoints[0], controlPoints.size() * sizeof(vec3));
	mPoints.SetData(&points[0], points.size() * sizeof(vec3));
}

SplineModel::~SplineModel()
{
}

void SplineModel::Draw()
{
	Shader shader = RendererHelper::GetShader(SHADER_SPLINE);

	shader.Bind();

	shader.SetMatrix("ViewProjectonTransform", World::GetInstance()->GetCamera()->GetViewProjectionMatrix());
	shader.SetMatrix("WorldTransform", mat4(1));

	mArray.Bind();

	int stride = sizeof(Vertex);

	// shader.SetVertexAttrib(mControlPoints, 0, 3, stride, 0);
	//glDrawArrays(GL_LINE_STRIP, 0, mControlPoints.GetSize() / sizeof(vec3));

	shader.SetVertexAttrib(mPoints, 0, 3, stride, 0);
	shader.SetVertexAttrib(mPoints, 2, 3, stride, (void*)sizeof(vec3));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, mPoints.GetSize() / sizeof(Vertex));

	shader.DisableVertexAttrib(0);
}

bool SplineModel::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}