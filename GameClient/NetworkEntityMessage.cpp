#include "NetworkEntityMessage.h"

NetworkEntityMessage::NetworkEntityMessage() : NetworkMessage()
{
	this->m_type = NetworkMessage::Entity;
	this->m_entityId = 0;
	this->m_entityType = 0;
	this->m_modelId = 0;
	this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_rotation = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_scale = FLOAT3(0.0f, 0.0f, 0.0f);
}
NetworkEntityMessage::NetworkEntityMessage(unsigned int _entityId, unsigned int _entityType, unsigned int _modelId, FLOAT3 _position, FLOAT3 _rotation, FLOAT3 _scale) : NetworkMessage(NetworkMessage::Entity)
{
	this->m_entityId = _entityId;
	this->m_entityType = _entityType;
	this->m_modelId = _modelId;
	this->m_position = _position;
	this->m_rotation = _rotation;
	this->m_scale = _scale;
}

NetworkEntityMessage::~NetworkEntityMessage()
{

}

unsigned int NetworkEntityMessage::getEntityId()
{
	return this->m_entityId;
}

unsigned int NetworkEntityMessage::getEntityType()
{
	return this->m_entityType;
}

unsigned int NetworkEntityMessage::getModelId()
{
	return this->m_modelId;
}

FLOAT3 NetworkEntityMessage::getPosition()
{
	return this->m_position;
}

FLOAT3 NetworkEntityMessage::getRotation()
{
	return this->m_rotation;
}

FLOAT3 NetworkEntityMessage::getScale()
{
	return this->m_scale;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkEntityMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_entityId<<e.m_entityType<<e.m_modelId<<e.m_position.x<<e.m_position.y<<e.m_position.z<<e.m_rotation.x<<e.m_rotation.y<<e.m_rotation.z<<e.m_scale.x<<e.m_scale.y<<e.m_scale.z;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkEntityMessage& e)
{
	return packet>>e.m_entityId>>e.m_entityType>>e.m_modelId>>e.m_position.x>>e.m_position.y>>e.m_position.z>>e.m_rotation.x>>e.m_rotation.y>>e.m_rotation.z>>e.m_scale.x>>e.m_scale.y>>e.m_scale.z;
}