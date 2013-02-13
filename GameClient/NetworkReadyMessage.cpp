#include "NetworkReadyMessage.h"

NetworkReadyMessage::NetworkReadyMessage() : NetworkMessage(NetworkMessage::MESSAGE_TYPE::Ready)
{

}

NetworkReadyMessage::~NetworkReadyMessage()
{

}

sf::Packet& operator<<(sf::Packet& packet,const NetworkReadyMessage& e)
{
	return packet << *((int*)&e.m_type) << e.m_isPorn;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkReadyMessage& e)
{
	return packet >> e.m_isPorn;
}