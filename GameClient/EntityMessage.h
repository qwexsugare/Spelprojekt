#ifndef ENTITY_MESSAGE_H
#define ENTITY_MESSAGE_H
#include "DataStructures.h"
#include <SFML\Network.hpp>
#include <string>

class EntityMessage
{
private:
	unsigned int id;
	FLOAT3 pos;
	FLOAT3 rot;
public:
	EntityMessage();
	EntityMessage(unsigned int id);
	~EntityMessage();
	void setPosition(FLOAT3 pos);
	void setRotation(FLOAT3 rot);
	unsigned int getId();
	FLOAT3 getPos();
	FLOAT3 getRotation();

	friend sf::Packet& operator<<(sf::Packet& packet,const EntityMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, EntityMessage& e);
};

#endif