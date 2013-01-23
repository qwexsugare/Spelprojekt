#include "EntityMessage.h"

EntityMessage::EntityMessage()
{
	this->pos.x=1.0f;
	this->pos.y=2.0f;
	this->pos.z=3.0f;

	this->rot.x=5.3;
	this->rot.y=7.8;
	this->rot.z=9.23;

	this->id = 0;
}

EntityMessage::EntityMessage(unsigned int id)
{
	this->pos.x=1.0f;
	this->pos.y=2.0f;
	this->pos.z=3.0f;

	this->rot.x=5.3;
	this->rot.y=7.8;
	this->rot.z=9.23;

	this->id = id;
}

EntityMessage::EntityMessage(unsigned int id, unsigned int modelId, int type, FLOAT3 pos, FLOAT3 rot)
{
	this->id = id;
	this->modelId = modelId;
	this->type = type;
	this->pos = pos;
	this->rot = rot;
}

EntityMessage::~EntityMessage()
{

}

void EntityMessage::setModelId(unsigned int modelId)
{
	this->modelId = modelId;
}

void EntityMessage::setType(int type)
{
	this->type = type;
}

void EntityMessage::setPosition(FLOAT3 pos)
{
	this->pos=pos;
}

void EntityMessage::setRotation(FLOAT3 rot)
{
	this->rot=rot;
}

sf::Packet& operator<<(sf::Packet& packet,const EntityMessage& e)
{
	return packet<<"ENT"<<e.id<<e.modelId<<e.type<<e.pos.x<<e.pos.y<<e.pos.z<<e.rot.x<<e.rot.y<<e.rot.z;
}
sf::Packet& operator>>(sf::Packet& packet, EntityMessage& e)
{
	return packet >>e.id>>e.modelId>>*((int*)&e.type)>>e.pos.x>>e.pos.y>>e.pos.z>>e.rot.x>>e.rot.y>>e.rot.z;
}

FLOAT3 EntityMessage::getPos()
{
	return this->pos;
}

FLOAT3 EntityMessage::getRotation()
{
	return this->rot;
}

unsigned int EntityMessage::getId()
{
	return this->id;
}

unsigned int EntityMessage::getModelId()
{
	return this->modelId;
}

int EntityMessage::getType()
{
	return this->type;
}