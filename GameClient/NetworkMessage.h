#ifndef NETWORK_MESSAGE_H
#define NETWORK_MESSAGE_H

#include <SFML\Network.hpp>

class NetworkMessage
{
public:
	static enum MESSAGE_TYPE {SelectHero, HeroSelected, Ready, Start, Entity, RemoveEntity, UseAction, UseActionPos, UseActionTarget, CreateAction, CreateActionPos, CreateActionTarget, BuySkill, SkillBought, Wave, Money, Disconnect};
	
protected:
	MESSAGE_TYPE m_type;	

public:
	NetworkMessage();
	NetworkMessage(MESSAGE_TYPE _type);
	NetworkMessage(sf::Packet packet);

	MESSAGE_TYPE getType();

	virtual sf::Packet toPacket();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkMessage& e);
};

#endif