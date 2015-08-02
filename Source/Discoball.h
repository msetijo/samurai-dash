#ifndef DISCOBALL_H
#define DISCOBALL_H

#include "SphereModel.h"


class Discoball : public SphereModel {

public:
	Discoball(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~Discoball();

private:
	static void forEachVertex(SphereModel::Vertex* vertexBuffer, int len);
};

#endif DISCOBALL_H