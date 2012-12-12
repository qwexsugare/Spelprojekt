#ifndef ENTITY_MESSAGE_H
#define ENTITY_MESSAGE_H
#include "DataStructures.h"
#include <SFML\Network.hpp>
#include <string>

class EntityMessage
{
private:
	FLOAT3 pos;
	FLOAT3 rot;
public:
	EntityMessage();
	~EntityMessage();
	void setPosition(FLOAT3 pos);
	void setRotation(FLOAT3 rot);
	FLOAT3 getPos();

	friend sf::Packet& operator<<(sf::Packet& packet,const EntityMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, EntityMessage& e);
};

#endif