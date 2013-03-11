#include "NetworkWelcomeMessage.h"


NetworkWelcomeMessage::NetworkWelcomeMessage(void) :NetworkMessage(NetworkMessage::MESSAGE_TYPE::welcomeMessage)
{
	this->mapName="";
}
NetworkWelcomeMessage::NetworkWelcomeMessage(string mapname):NetworkMessage(NetworkMessage::MESSAGE_TYPE::welcomeMessage)
{
	this->mapName=mapname;
}

NetworkWelcomeMessage::~NetworkWelcomeMessage(void)
{
}
string NetworkWelcomeMessage::getMapName()
{
	return this->mapName;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkWelcomeMessage& e)
{
	return packet << *((int*)&e.m_type) << e.mapName;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkWelcomeMessage& e)
{
	return packet >> e.mapName;
}