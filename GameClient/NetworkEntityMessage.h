#pragma once

#include "NetworkMessage.h"
#include "DataStructures.h"

class NetworkEntityMessage : public NetworkMessage
{
private:
	unsigned int m_entityId;
	unsigned int m_entityType;
	unsigned int m_modelId;
	FLOAT3 m_position;
	FLOAT3 m_rotation;
	FLOAT3 m_scale;
public:
	NetworkEntityMessage();
	NetworkEntityMessage(unsigned int _entityId, unsigned int _entityType, unsigned int _modelId, FLOAT3 _position, FLOAT3 _rotation, FLOAT3 _scale);
	~NetworkEntityMessage();

	unsigned int getEntityId();
	unsigned int getEntityType();
	unsigned int getModelId();
	FLOAT3 getPosition();
	FLOAT3 getRotation();
	FLOAT3 getScale();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkEntityMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkEntityMessage& e);
};

