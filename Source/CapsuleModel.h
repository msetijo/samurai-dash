#ifndef CAPSULEMODEL_H
#define CAPSULEMODEL_H

#include "RealTimeCollisionDetection.h"

#include "Model.h"
#include "Vertexes.h"

class CapsuleModel : public Model {

public:
	CapsuleModel(const rtcd::Capsule& capsule);
	virtual ~CapsuleModel() {}

	virtual void Update(float dt) {}
	virtual void Draw();

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token) { return false; }

private:

	// Number of line segments to make for the cylinder, the more the rounder it is.
	static const int CYLINDER_SEGMENTS = 18;
	// Number of line segments to make for the sphere halves, the more the rounder it is.
	static const int SPHERE_SEGMENTS = 18;

	struct Vertex {
		glm::vec3 position;
	};

	void makeCapsuleLineSegments(std::vector<Vertex>& vertexes, const rtcd::Capsule& capsule);
	void makeHalfCircleLineSegments(std::vector<Vertex>& vertexes, glm::vec3 p, glm::vec3 q, glm::vec3 direction);
	void makeQuarterCircleLineSegments(std::vector<Vertex>& vertexes, glm::vec3 p, glm::vec3 q, glm::vec3 center, float radius);

	VertexArray mArray;
	VertexBuffer mBuffer;
};

#endif