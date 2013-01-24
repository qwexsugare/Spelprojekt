#include "NetworkEntityMessage.h"

NetworkEntityMessage::NetworkEntityMessage() : NetworkMessage()
{

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

NetworkEntityMessage::NetworkEntityMessage(sf::Packet packet)
{
	packet>>*((int*)this->m_type)>>this->m_entityId>>this->m_entityType>>this->m_modelId>>this->m_position.x>>this->m_position.y>>this->m_position.z>>this->m_rotation.x>>this->m_rotation.y>>this->m_rotation.z>>this->m_scale.x>>this->m_scale.y>>this->m_scale.z;
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

sf::Packet NetworkEntityMessage::toPacket()
{
	sf::Packet packet;
	packet<<*((int*)this->m_type)<<this->m_entityId<<this->m_entityType<<this->m_modelId<<this->m_position.x<<this->m_position.y<<this->m_position.z<<this->m_rotation.x<<this->m_rotation.y<<this->m_rotation.z<<this->m_scale.x<<this->m_scale.y<<this->m_scale.z;

	return packet;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkEntityMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_entityId<<e.m_entityType<<e.m_modelId<<e.m_position.x<<e.m_position.y<<e.m_position.z<<e.m_rotation.x<<e.m_rotation.y<<e.m_rotation.z<<e.m_scale.x<<e.m_scale.y<<e.m_scale.z;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkEntityMessage& e)
{
	return packet>>*((int*)&e.m_type)>>e.m_entityId>>e.m_entityType>>e.m_modelId>>e.m_position.x>>e.m_position.y>>e.m_position.z>>e.m_rotation.x>>e.m_rotation.y>>e.m_rotation.z>>e.m_scale.x>>e.m_scale.y>>e.m_scale.z;
}