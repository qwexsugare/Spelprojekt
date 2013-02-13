#include "NetworkSelectHeroMessage.h"

NetworkSelectHeroMessage::NetworkSelectHeroMessage() : NetworkMessage(NetworkMessage::SelectHero)
{

}

NetworkSelectHeroMessage::NetworkSelectHeroMessage(int _heroId) : NetworkMessage(NetworkMessage::SelectHero)
{
	m_heroId = _heroId;
}

NetworkSelectHeroMessage::~NetworkSelectHeroMessage()
{

}

sf::Packet& operator<<(sf::Packet& packet,const NetworkSelectHeroMessage& e)
{
	return packet << *((int*)&e.m_type) << e.m_heroId;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkSelectHeroMessage& e)
{
	return packet >> e.m_heroId;
}