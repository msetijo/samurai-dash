#include "Discoball.h"

#include "EventManager.h"

using namespace glm;

Discoball::Discoball(vec3 size) : SphereModel(size, &forEachVertex)
{
}

Discoball::~Discoball() {}

void Discoball::forEachVertex(SphereModel::Vertex* vertexBuffer, int len) {

	for (int i = 0; i < len; i++) {

		float rx = EventManager::GetRandomFloat(0, 1);
		float ry = EventManager::GetRandomFloat(0, 1);
		float rz = EventManager::GetRandomFloat(0, 1);

		vertexBuffer[i].position += vec3(rx, ry, rz);
		vertexBuffer[i].color = vec3(rx, ry, rz);
	}
}