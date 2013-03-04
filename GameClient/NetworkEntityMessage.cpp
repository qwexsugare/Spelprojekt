#include "NetworkEntityMessage.h"

NetworkEntityMessage::NetworkEntityMessage() : NetworkMessage()
{
	this->m_type = NetworkMessage::Entity;
	this->m_entityId = 0;
	this->xPos=0;
	this->zPos=0;
	this->yRot=0;
	this->sx=this->sz=this->ex=this->ez=0;
	this->movementspeed=0;
}
NetworkEntityMessage::NetworkEntityMessage(unsigned short _entityId, float xpos, float zpos,float yrot,float sx, float sz,float ex, float ez,float mms) : NetworkMessage(NetworkMessage::Entity)
{
	this->m_entityId = _entityId;
	this->xPos = xpos;
	this->zPos = zpos;
	this->yRot=yrot;
	this->sx=sx;
	this->sz=sz;
	this->ex=ex;
	this->ez=ez;
	this->movementspeed=mms;
}

NetworkEntityMessage::~NetworkEntityMessage()
{

}

unsigned int NetworkEntityMessage::getEntityId()
{
	return this->m_entityId;
}


float NetworkEntityMessage::getXPos()
{
	return this->xPos;
}
float NetworkEntityMessage::getZPos()
{
	return this->zPos;
}

float NetworkEntityMessage::getYRot()
{
	return this->yRot;
}

float NetworkEntityMessage::getStartX()
{
	return this->sx;
}
float NetworkEntityMessage::getStartZ()
{
	return this->sz;
}
float NetworkEntityMessage::getEndX()
{
	return this->ex;
}
float NetworkEntityMessage::getEndZ()
{
	return this->ez;
}
float NetworkEntityMessage::getMovementSpeed()
{
	return this->movementspeed;
}
sf::Packet& operator<<(sf::Packet& packet,const NetworkEntityMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_entityId<<e.xPos<<e.zPos<<e.yRot<<e.sx<<e.sz<<e.ex<<e.ez<<e.movementspeed;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkEntityMessage& e)
{
	return packet>>e.m_entityId>>e.xPos>>e.zPos>>e.yRot>>e.sx>>e.sz>>e.ex>>e.ez>>e.movementspeed;
}