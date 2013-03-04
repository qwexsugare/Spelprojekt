#pragma once

#include "NetworkMessage.h"
#include "DataStructures.h"

class NetworkEntityMessage : public NetworkMessage
{
private:
	unsigned short m_entityId;
	float xPos;
	float zPos;
	float sx,sz,ex,ez;
	float yRot;
	float movementspeed;
public:
	NetworkEntityMessage();
	NetworkEntityMessage(unsigned short _entityId, float xpos, float zpos,float yrot,float sx,float sz, float ex, float ez,float movementspeed);
	~NetworkEntityMessage();

	unsigned int getEntityId();
	unsigned int getModelId();
	unsigned int getHealth();
	float getXPos();
	float getZPos();
	float getYRot();
	float getStartX();
	float getStartZ();
	float getEndX();
	float getEndZ();
	float getMovementSpeed();
	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkEntityMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkEntityMessage& e);
};

