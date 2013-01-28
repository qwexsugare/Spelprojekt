#include "NetworkDisconnectMessage.h"

NetworkDisconnectMessage::NetworkDisconnectMessage() : NetworkMessage()
{

}

NetworkDisconnectMessage::NetworkDisconnectMessage(std::string _message) : NetworkMessage(MESSAGE_TYPE::Disconnect)
{
	this->m_message = _message;
}

NetworkDisconnectMessage::~NetworkDisconnectMessage()
{

}

std::string NetworkDisconnectMessage::getMessage()
{
	return this->m_message;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkDisconnectMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_message;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkDisconnectMessage& e)
{
	return packet>>e.m_message;
}