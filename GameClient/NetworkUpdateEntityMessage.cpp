#include "NetworkUpdateEntityMessage.h"

NetworkUpdateEntityMessage::NetworkUpdateEntityMessage(void):NetworkMessage(NetworkMessage::updateEntity)
{
	this->id=0;
	this->xPos=0;
	this->zPos=0;
	this->yRot=0;
}

NetworkUpdateEntityMessage::NetworkUpdateEntityMessage(int id, float xpos, float zpos, float yrot):NetworkMessage(NetworkMessage::updateEntity)
{
	this->id=id;
	this->xPos=xpos;
	this->zPos=zpos;
	this->yRot=yrot;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkUpdateEntityMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.id<<e.xPos<<e.zPos<<e.yRot;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkUpdateEntityMessage& e)
{
	return packet>>e.id>>e.xPos>>e.zPos>>e.yRot;
}


NetworkUpdateEntityMessage::~NetworkUpdateEntityMessage(void)
{
}
float NetworkUpdateEntityMessage::getYRot()
{
	return this->yRot;
}
float NetworkUpdateEntityMessage::getXPos()
{
	return this->xPos;
}
float NetworkUpdateEntityMessage::getZPos()
{
	return this->zPos;
}
int NetworkUpdateEntityMessage::getID()
{
	return this->id;
}