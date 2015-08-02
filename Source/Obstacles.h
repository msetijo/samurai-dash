#pragma once

#include <vector>

#include <GLM/glm.hpp>
#include "CubeModel.h"
#include "SphereModel.h"
#include "WolfModel.h"

class PlayerModel;

class Obstacles :Model
{
public:
	static int distance;
	Obstacles();
	glm::vec3 GetPlayerPos();
	void CalculateDistance(double score);
	CubeModel* GetCube();
	Model* GetRandomModel();
private:
	PlayerModel* mPlayerModel;
};
