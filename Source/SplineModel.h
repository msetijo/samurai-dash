#ifndef SPLINEMODEL_H
#define SPLINEMODEL_H

#include "Model.h"
#include "Vertexes.h"

class SplineModel : public Model {

public:
	SplineModel();
	virtual ~SplineModel();

	virtual void Update(float dt) {};
	
	virtual void Draw();

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

private:
	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;
	};

	VertexArray mArray;
	VertexBuffer mControlPoints;
	VertexBuffer mPoints;
};

#endif
