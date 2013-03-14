#include "NetworkReadyMessageToClient.h"

NetworkReadyMessageToClient::NetworkReadyMessageToClient() : NetworkMessage(NetworkMessage::READY_TO_CLIENT)
{

}

NetworkReadyMessageToClient::NetworkReadyMessageToClient(int _playerIndex) : NetworkMessage(NetworkMessage::READY_TO_CLIENT)
{
	m_playerIndex = _playerIndex;
}

NetworkReadyMessageToClient::~NetworkReadyMessageToClient()
{

}

sf::Packet& operator<<(sf::Packet& packet,const NetworkReadyMessageToClient& e)
{
	return packet << *((int*)&e.m_type) << e.m_playerIndex;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkReadyMessageToClient& e)
{
	return packet >> e.m_playerIndex;
}