#include "NetworkHeroInitMessage.h"

NetworkHeroInitMessage::NetworkHeroInitMessage()
{

}

NetworkHeroInitMessage::NetworkHeroInitMessage(vector<unsigned int> _ids, vector<Hero::HERO_TYPE> _heroTypes) : NetworkMessage(NetworkMessage::HeroInit)
{
	m_ids = _ids;
	m_heroTypes = _heroTypes;
}

NetworkHeroInitMessage::~NetworkHeroInitMessage()
{

}

vector<unsigned int> NetworkHeroInitMessage::getIds()const
{
	return m_ids;
}

vector<Hero::HERO_TYPE> NetworkHeroInitMessage::getHeroTypes()const
{
	return m_heroTypes;
}

unsigned int NetworkHeroInitMessage::getYourId()const
{
	return m_yourId;
}

void NetworkHeroInitMessage::setYourId(unsigned int _id)
{
	m_yourId = _id;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkHeroInitMessage& e)
{
	packet << *((int*)&e.m_type) << e.m_ids.size() << e.m_yourId;
	for(int i = 0; i < e.m_ids.size(); i++)
	{
		packet << e.m_ids[i] << e.m_heroTypes[i];
	}
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkHeroInitMessage& e)
{
	int inty = 0;
	packet >> inty;
	packet >> e.m_yourId;
	e.m_ids.resize(inty);
	e.m_heroTypes.resize(inty);
	for(int i = 0; i < inty; i++)
	{
		packet >> e.m_ids[i] >> *(int*)(&e.m_heroTypes[i]);
	}
	return packet;
}