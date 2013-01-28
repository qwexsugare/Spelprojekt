#include "NetworkRemoveEntityMessage.h"

NetworkRemoveEntityMessage::NetworkRemoveEntityMessage() : NetworkMessage()
{

}

NetworkRemoveEntityMessage::NetworkRemoveEntityMessage(unsigned int _entityId) : NetworkMessage(MESSAGE_TYPE::RemoveEntity)
{
	this->m_entityId = _entityId;
}

NetworkRemoveEntityMessage::~NetworkRemoveEntityMessage()
{

}

unsigned int NetworkRemoveEntityMessage::getEntityId()
{
	return this->m_entityId;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkRemoveEntityMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_entityId;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkRemoveEntityMessage& e)
{
	return packet>>e.m_entityId;
}