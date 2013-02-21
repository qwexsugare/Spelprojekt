#pragma once

#include "networkmessage.h"
#include "Hero.h"

class NetworkHeroInitMessage :
	public NetworkMessage
{
private:
	unsigned int m_yourId;
	vector<unsigned int> m_ids;
	vector<Hero::HERO_TYPE> m_heroTypes;
public:
	NetworkHeroInitMessage();
	NetworkHeroInitMessage(vector<unsigned int> _ids, vector<Hero::HERO_TYPE> _heroTypes);
	~NetworkHeroInitMessage();
	
	vector<unsigned int> getIds()const;
	vector<Hero::HERO_TYPE> getHeroTypes()const;
	unsigned int getYourId()const;

	void setYourId(unsigned int _id);

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkHeroInitMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkHeroInitMessage& e);
};