#include "Obstacles.h"
#include "PlayerModel.h"
#include "SplineModel.h"
#include "World.h"
#include <GL/glew.h>
using namespace std;

Obstacles::Obstacles() : listObstacles()
{

}

void Obstacles::RemoveObstacles(int position)
{
}

void Obstacles::AddObstacles(Model* m)
{
	listObstacles.push_back(m);
}

glm::vec3 Obstacles::GetPlayerPos()
{
	mPlayerModel = new PlayerModel();
	return mPlayerModel->GetPosition();
}

void Obstacles::PopulateRandomSample()
{
	int count = 0;
	float maxTime = World::GetInstance()->GetSpline()->MaxTime();
	float distanceTime = maxTime / 15.0f;

	for (int i = 0; i < 15; i++)
	{
		listObstacles.push_back(GetRandomModel());
	}

	for each (Model* m in listObstacles)
	{
		count++;
		SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(distanceTime * count);
		m->SetPosition(p.position);
	}
}

Model* Obstacles::GetRandomModel()
{
	int randomNumb = rand() % 3;
	if (randomNumb == 0){
		return new CubeModel();
	}
	else if (randomNumb == 1)
	{
		return new WolfModel();
	}
	else
	{
		return new SphereModel();
	}
}

void Obstacles::CalculateDistance(double score)
{
	//get the score and change the distance between the cube
}

void Obstacles::TransformToWorld()
{

}

void Obstacles::Draw()
{
	for (std::vector<Model*>::iterator it = listObstacles.begin(); it != listObstacles.end(); ++it) {
		(*it)->Draw();
	}

}



