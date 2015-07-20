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

	makeOscullatingPlanes(spline);

	return splineModel;
}

const vec2 SplineFactory::controlPointsCount = vec2(20, 30);
const vec2 SplineFactory::deltaMinControlPoint = vec2(20.0f, -10.0f);
const vec2 SplineFactory::deltaMaxControlPoint = vec2(21.0f, 10.0f);

const glm::vec3 SplineFactory::controlPointsColor = vec3(1.0f, 0.0f, 0.0f);

void SplineFactory::makeControlPoints(SplineModel& spline) {

	std::vector<SplineModel::Vertex> controlPoints;

	int N = controlPointsCount.x + rand() % (int) (controlPointsCount.y - controlPointsCount.x);

	controlPoints.push_back({
		vec3(0, 0, deltaMinControlPoint.x),
		controlPointsColor
	});

	for (int i = 1; i < N; i++) {

		SplineModel::Vertex prev = controlPoints[i - 1];
		
		int dz = deltaMinControlPoint.x + rand() % (int) (deltaMaxControlPoint.x - deltaMinControlPoint.x);
		int dy = deltaMinControlPoint.y + rand() % (int) (deltaMaxControlPoint.y - deltaMinControlPoint.y);

		SplineModel::Vertex next = {
			prev.position + vec3(0, dy, -dz),
			controlPointsColor
		};
		controlPoints.push_back(next);
	}

	spline.SetControlPoints(controlPoints);
}

const int SplineFactory::triangleStripSegmentCount = 5;
const float SplineFactory::trackWidth = 20.0f;

void SplineFactory::makeTriangleStrip(SplineModel& spline) {

	std::vector<SplineModel::Vertex> points;

	vec3 red = vec3(1.0f, 0.0f, 0.0f);
	vec3 green = vec3(0.0f, 1.0f, 0.0f);
	vec3 blue = vec3(0.0f, 1.0f, 0.0f);

	vec3 shift = vec3(trackWidth / 2, 0, 0);
	float timeStep = 1.0f / triangleStripSegmentCount;

	vec3 point = spline.At(0);
	points.push_back({
		point + shift,
		red
	});
	points.push_back({
		point - shift,
		green
	});

	int shiftDirection = 1;
	int colorChoice = 2;
	for (float t = timeStep; t <= spline.MaxTime(); t += timeStep) {

		vec3 point = spline.At(t);

		point += (shiftDirection ? 1.0f : -1.0f) * shift;

		points.push_back({
			point,
			colorChoice == 0 ? red : colorChoice == 1 ? green : blue
		});

		shiftDirection = (shiftDirection + 1) % 2;
		colorChoice = (colorChoice + 1) % 3;
	}

	spline.SetPoints(points);
}

void SplineFactory::makeOscullatingPlanes(SplineModel& spline) {
}