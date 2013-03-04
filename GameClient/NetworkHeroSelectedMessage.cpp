#include "NetworkHeroSelectedMessage.h"

NetworkHeroSelectedMessage::NetworkHeroSelectedMessage() : NetworkMessage(NetworkMessage::HeroSelected)
{

}

NetworkHeroSelectedMessage::NetworkHeroSelectedMessage(int _heroId, int _playerId) : NetworkMessage(NetworkMessage::HeroSelected)
{
	this->m_heroId = _heroId;
	this->m_playerId = _playerId;
}

NetworkHeroSelectedMessage::~NetworkHeroSelectedMessage()
{

}

sf::Packet& operator<<(sf::Packet& packet,const NetworkHeroSelectedMessage& e)
{
	return packet << *((int*)&e.m_type) << e.m_heroId << e.m_playerId;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkHeroSelectedMessage& e)
{
	return packet >> e.m_heroId >> e.m_playerId;
}