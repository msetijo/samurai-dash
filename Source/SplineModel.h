#ifndef SPLINEMODEL_H
#define SPLINEMODEL_H

#include <vector>

#include "Model.h"
#include "Vertexes.h"

class SplineModel : public Model {

public:
	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;
	};

	SplineModel();
	virtual ~SplineModel();

	virtual void Update(float dt) {};

	virtual void Draw();

	glm::vec3 At(float t);

	int MaxTime() { return mControlPoints.size() - 4; }

	bool HasControlPoints() { return !mControlPoints.empty(); }
	std::vector<Vertex>& GetControlPoints() { return mControlPoints; }

	void SetControlPoints(std::vector<Vertex>& controlPoints);

	void SetPoints(std::vector<Vertex>& points);

	void SetOscullatingPlanes(std::vector<Vertex>& oscullatingPlanes);

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

private:

	std::vector<Vertex> mControlPoints;

	VertexArray mArray;
	VertexBuffer mControlPointsBuffer;
	VertexBuffer mPointsBuffer;

	VertexBuffer mOscullatingPlanesBuffer;
};

#endif
