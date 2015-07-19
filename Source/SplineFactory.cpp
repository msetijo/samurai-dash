#include "SplineFactory.h"

using namespace glm;

SplineModel* SplineFactory::LoadSpline(ci_istringstream& iss) {
	
	SplineModel* splineModel = new SplineModel();
	SplineModel& spline = *splineModel;

	spline.Load(iss);

	if (!spline.HasControlPoints()) {
		makeControlPoints(spline);
	}

	makeTriangleStrip(spline);

	return splineModel;
}

const vec2 SplineFactory::controlPointsCount = vec2(20, 30);
const vec2 SplineFactory::deltaMinControlPoint = vec2(0.0f, 0.0f);
const vec2 SplineFactory::deltaMaxControlPoint = vec2(20, 3);

void SplineFactory::makeControlPoints(SplineModel& spline) {

	std::vector<SplineModel::Vertex> controlPoints;

	controlPoints.push_back({
		vec3(0, 5, 0),
		vec3(1.0f, 0.0f, 0.0f)
	});

	for (int i = 1; i < controlPointsCount.y; i++) {
		SplineModel::Vertex prev = controlPoints[i - 1];

		int signx = (rand() % 2 ? 1 : -1);
		int signy = (rand() % 2 ? 1 : -1);
		int dx = rand() % (int) deltaMaxControlPoint.x;
		int dy = rand() % (int) deltaMaxControlPoint.y;

		SplineModel::Vertex next = {
			prev.position + vec3(dx, signy * dy, 0),
			vec3(1.0f, 0.0f, 0.0f)
		};
		controlPoints.push_back(next);
	}

	spline.SetControlPoints(controlPoints);
}

const int SplineFactory::triangleStripSegmentCount = 5;
const float SplineFactory::trackWidth = 20.0f;

void SplineFactory::makeTriangleStrip(SplineModel& spline) {

	std::vector<SplineModel::Vertex> controlPoints = spline.GetControlPoints();
	std::vector<SplineModel::Vertex> points;

	vec3 shift = vec3(0, 0, trackWidth);

	vec3 red = vec3(1.0f, 0.0f, 0.0f);
	vec3 green = vec3(0.0f, 1.0f, 0.0f);
	vec3 blue = vec3(0.0f, 1.0f, 0.0f);

	bool start = true;
	int flipFlop = 0;
	int flipFlopFloop = 0;

	for (int j = 0; j < controlPoints.size() - 3; j += 1) {

		SplineModel::Vertex v1 = controlPoints[j];
		SplineModel::Vertex v2 = controlPoints[j + 1];
		SplineModel::Vertex v3 = controlPoints[j + 2];
		SplineModel::Vertex v4 = controlPoints[j + 3];

		vec3 p1 = v1.position;
		vec3 p2 = v2.position;
		vec3 p3 = v3.position;
		vec3 p4 = v4.position;

		for (float t = 0; t <= 1; t += 1.0f / triangleStripSegmentCount) {

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

	spline.SetPoints(points);
}