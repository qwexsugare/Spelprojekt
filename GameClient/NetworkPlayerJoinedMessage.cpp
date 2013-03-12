#include "NetworkPlayerJoinedMessage.h"

NetworkPlayerJoinedMessage::NetworkPlayerJoinedMessage() : NetworkMessage(NetworkMessage::MESSAGE_TYPE::PLAYER_JOINED)
{

}

NetworkPlayerJoinedMessage::NetworkPlayerJoinedMessage(int _playerIndex, string _name) : NetworkMessage(NetworkMessage::MESSAGE_TYPE::PLAYER_JOINED)
{
	m_playerIndex = _playerIndex;
	m_name = _name;
}

NetworkPlayerJoinedMessage::~NetworkPlayerJoinedMessage()
{

}

string NetworkPlayerJoinedMessage::getName()const
{
	return m_name;
}

int NetworkPlayerJoinedMessage::getPlayerIndex()const
{
	return m_playerIndex;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkPlayerJoinedMessage& e)
{
	return packet << *((int*)&e.m_type) << e.m_name << e.m_playerIndex;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkPlayerJoinedMessage& e)
{
	return packet >> e.m_name >> e.m_playerIndex;
}