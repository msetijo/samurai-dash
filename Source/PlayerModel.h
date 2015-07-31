#ifndef PLAYERMODEL_H
#define PLAYERMODE_H

#include "Model.h"

class PlayerModel : public Model 
{

public: PlayerModel();
		unsigned int mVertexArrayID;
		std::vector<unsigned int> awesomeSheepList;
		virtual void Draw();
		virtual void Update(float dt)
		{

		}
		virtual bool ParseLine(const std::vector<ci_string> &token)
		{
			return true;
		}

};



#endif