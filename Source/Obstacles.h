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
	void CalculateDistance(double score);
	void RemoveObstacles(int position);
	void AddObstacles(Model* m);
	void TransformToWorld();
	void PopulateRandomSample();
	void Draw();
	Model* GetRandomModel();
};
