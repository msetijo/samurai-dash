#ifndef PLAYERMODEL_H
#define PLAYERMODE_H

#include "Model.h"
#include "ObjectModel.h"

class PlayerModel : public ObjectModel
{

public: 
	static const glm::vec3 SHEEP_SHAPE_COLORS[];
	PlayerModel();
		
};



#endif