#include "Obstacles.h"
#include "PlayerModel.h"
#include "SplineModel.h"
#include <GL/glew.h>
using namespace std;

Obstacles::Obstacles() :Model()
{
	//distance = 5;
}

glm::vec3 Obstacles::GetPlayerPos()
{
	mPlayerModel = new PlayerModel();
	return mPlayerModel->GetPosition();
}


Model* Obstacles::GetRandomModel()
{
	int randomNumb = rand() % 3;
	if (randomNumb == 0){
		return new CubeModel();
	}
	//else if (randomNumb == 1)
	//{
	//	return new WolfModel();
	//}
	else
	{
		return new SphereModel();
	}
}

void Obstacles::CalculateDistance(double score)
{
	//get the score and change the distance between the cube
	
}

CubeModel* Obstacles::GetCube()
{
	return new CubeModel();
}


