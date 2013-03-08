#include "NetworkStartGameMessage.h"

NetworkStartGameMessage::NetworkStartGameMessage() : NetworkMessage(NetworkMessage::Start)
{

}

NetworkStartGameMessage::NetworkStartGameMessage(string mapName) : NetworkMessage(NetworkMessage::Start)
{
	this->mapName=mapName;
}

NetworkStartGameMessage::~NetworkStartGameMessage()
{

}

sf::Packet& operator<<(sf::Packet& packet,const NetworkStartGameMessage& e)
{
	return packet << *((int*)&e.m_type)<<e.mapName;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkStartGameMessage& e)
{
	return packet>>e.mapName;
}

void NetworkStartGameMessage::setMapName(string n)
{
	this->mapName=n;
}
string NetworkStartGameMessage::getMapName()
{
	return this->mapName;
}