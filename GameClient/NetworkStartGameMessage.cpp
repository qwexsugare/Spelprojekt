#include "NetworkStartGameMessage.h"

NetworkStartGameMessage::NetworkStartGameMessage() : NetworkMessage(NetworkMessage::Start)
{

}

NetworkStartGameMessage::~NetworkStartGameMessage()
{

}

sf::Packet& operator<<(sf::Packet& packet,const NetworkStartGameMessage& e)
{
	return packet << *((int*)&e.m_type);
}

sf::Packet& operator>>(sf::Packet& packet, NetworkStartGameMessage& e)
{
	return packet;
}