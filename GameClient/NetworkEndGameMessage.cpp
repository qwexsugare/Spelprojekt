#include "NetworkEndGameMessage.h"

NetworkEndGameMessage::NetworkEndGameMessage(bool _victory) : NetworkMessage(NetworkMessage::EndGame)
{
	this->m_victory = _victory;
}

NetworkEndGameMessage::~NetworkEndGameMessage()
{

}

bool NetworkEndGameMessage::getVictory()
{
	return this->m_victory;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkEndGameMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_victory;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkEndGameMessage& e)
{
	return packet>>e.m_victory;
}