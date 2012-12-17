#ifndef PLAYER_H
#define PLAYER_H

#include "DataStructures.h"
#include "EntityMessage.h"

class Player
{
private:
	unsigned int m_id;
	FLOAT3 m_position;
public:
	Player(unsigned int id);

	void handleEntityMessage(EntityMessage e);
	EntityMessage getUpdate();
};

#endif