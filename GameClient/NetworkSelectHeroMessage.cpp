#include "NetworkSelectHeroMessage.h"

NetworkSelectHeroMessage::NetworkSelectHeroMessage() : NetworkMessage(NetworkMessage::SelectHero)
{

}

NetworkSelectHeroMessage::NetworkSelectHeroMessage(int _heroId, int _weapon) : NetworkMessage(NetworkMessage::SelectHero)
{
	this->m_heroId = _heroId;
	this->m_weapon = _weapon;
}

NetworkSelectHeroMessage::~NetworkSelectHeroMessage()
{

}

sf::Packet& operator<<(sf::Packet& packet,const NetworkSelectHeroMessage& e)
{
	return packet << *((int*)&e.m_type) << e.m_heroId << e.m_weapon;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkSelectHeroMessage& e)
{
	return packet >> e.m_heroId >> e.m_weapon;
}