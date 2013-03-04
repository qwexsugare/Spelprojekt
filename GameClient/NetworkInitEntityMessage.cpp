#include "NetworkInitEntityMessage.h"

NetworkInitEntityMessage::NetworkInitEntityMessage(void):NetworkMessage(NetworkMessage::initEntities)
{
	this->type=0;
	this->id=0;
	this->modelid=0;
	this->weaponType = 0;
	this->xPos=0.0f;
	this->zPos=0.0f;
	this->scale=0.0f;
	this->yRot=0;
	this->health=100;
	this->sx=this->sz=this->ex=this->ez=0;
	this->movementspeed=0;
}

NetworkInitEntityMessage::NetworkInitEntityMessage(unsigned short type, unsigned short modelid, unsigned short weaponType, unsigned short id, float xPos, float zPos, float yRot, float scale,int health,float sx, float sz,float ex, float ez,float mms):NetworkMessage(NetworkMessage::initEntities)
{
	this->type=type;
	this->modelid=modelid;
	this->weaponType = weaponType;
	this->id=id;
	this->xPos=xPos;
	this->zPos=zPos;
	this->yRot=yRot;
	this->scale=scale;
	this->health=health;
	this->sx=sx;
	this->sz=sz;
	this->ex=ex;
	this->ez=ez;
	this->movementspeed=mms;
}

NetworkInitEntityMessage::~NetworkInitEntityMessage(void)
{
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkInitEntityMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.type<<e.id<<e.modelid<<e.weaponType<<e.xPos<<e.zPos<<e.yRot<<e.scale<<e.health<<e.sx<<e.sz<<e.ex<<e.ez<<e.movementspeed;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkInitEntityMessage& e)
{
	return packet>>e.type>>e.id>>e.modelid>>e.weaponType>>e.xPos>>e.zPos>>e.yRot>>e.scale>>e.health>>e.sx>>e.sz>>e.ex>>e.ez>>e.movementspeed;
}

int NetworkInitEntityMessage::getType()
{
	return this->type;
}
int NetworkInitEntityMessage::getID()
{
	return this->id;
}
int NetworkInitEntityMessage::getModelID()
{
	return this->modelid;
}
int NetworkInitEntityMessage::getWeaponType()
{
	return this->weaponType;
}
float NetworkInitEntityMessage::getXPos()
{
	return this->xPos;
}
float NetworkInitEntityMessage::getZPos()
{
	return this->zPos;
}
float NetworkInitEntityMessage::getScale()
{
	return this->scale;
}
float NetworkInitEntityMessage::getYRot()
{
	return this->yRot;
}
int NetworkInitEntityMessage::getHealth()
{
	return this->health;
}
float NetworkInitEntityMessage::getStartX()
{
	return this->sx;
}
float NetworkInitEntityMessage::getEndX()
{
	return this->ex;
}
float NetworkInitEntityMessage::getStartZ()
{
	return this->sz;
}
float NetworkInitEntityMessage::getEndZ()
{
	return this->ez;
}
float NetworkInitEntityMessage::getMovementSpeed()
{
	return this->movementspeed;
}