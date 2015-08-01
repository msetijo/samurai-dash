#ifndef WOLFMODEL_H
#define WOLFMODEL_H

#include "Model.h"
#include "ObjectModel.h"

class WolfModel : public ObjectModel
{
public:
	static const glm::vec3 WOLF_SHAPE_COLORS[];
	WolfModel();
};
#endif