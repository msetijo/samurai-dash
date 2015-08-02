#pragma once

#include <vector>

#include <GLM/glm.hpp>
#include "CubeModel.h"
#include "SphereModel.h"
#include "WolfModel.h"

class PlayerModel;

class Obstacles
{
public:
	std::vector < Model* > listObstacles;
	Obstacles();
	void RemoveObstacles(int position);
	glm::vec3 RandomizeTrack(float t);
	void AddObstacles(Model* m);
	void PopulateRandomSample();
	void Draw();
	Model* GetRandomModel();
};
