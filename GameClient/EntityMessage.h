#ifndef ENTITY_MESSAGE_H
#define ENTITY_MESSAGE_H
#include "DataStructures.h"
#include <SFML\Network.hpp>
#include <string>

class EntityMessage
{
private:
	unsigned int id;
	unsigned int modelId;
	int type;
	FLOAT3 pos;
	FLOAT3 rot;
public:
	EntityMessage();
	EntityMessage(unsigned int id);
	EntityMessage(unsigned int id, unsigned int modelId, int type, FLOAT3 pos, FLOAT3 rot);
	~EntityMessage();
	void setModelId(unsigned int modelId);
	void setType(int type);
	void setPosition(FLOAT3 pos);
	void setRotation(FLOAT3 rot);
	unsigned int getId();
	unsigned int getModelId();
	int getType();
	FLOAT3 getPos();
	FLOAT3 getRotation();

	friend sf::Packet& operator<<(sf::Packet& packet,const EntityMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, EntityMessage& e);
};

#endif