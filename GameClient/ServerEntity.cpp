#include "ServerEntity.h"

ServerEntity::ServerEntity()
{
	this->m_messageQueue = new MessageQueue();
	this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_rotation = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_bs = NULL;
	this->m_modelId = 0;
	this->m_visible = true;
}

ServerEntity::ServerEntity(FLOAT3 _pos)
{
	this->m_messageQueue = new MessageQueue();
	this->m_position = _pos;
	this->m_rotation = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_bs = NULL;
	this->m_modelId = 0;
	this->m_visible = true;
}

ServerEntity::~ServerEntity()
{
	delete this->m_messageQueue;
	delete this->m_bs;
	delete this->m_obb;
}

void ServerEntity::update(float dt)
{
	//Handle incoming messages
	Message *m;

	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		m = this->m_messageQueue->pullIncomingMessage();


		delete m;
	}
}

MessageQueue *ServerEntity::getMessageQueue()
{
	return this->m_messageQueue;
}

EntityMessage ServerEntity::getUpdate()
{
	EntityMessage e = EntityMessage(this->m_id, this->m_modelId, this->m_type, this->m_position, this->m_rotation);

	return e;
}

void ServerEntity::setPosition(FLOAT3 _position)
{
	this->m_position = _position;
}

void ServerEntity::setId(unsigned int _id)
{
	this->m_id = _id;
}

void ServerEntity::setModelId(unsigned int _modelId)
{
	this->m_modelId = _modelId;
}

void ServerEntity::setVisible(bool _visible)
{
	this->m_visible = _visible;
}

FLOAT3 ServerEntity::getPosition()
{
	return this->m_position;
}

unsigned int ServerEntity::getId()
{
	return this->m_id;
}

unsigned int ServerEntity::getModelId()
{
	return this->m_modelId;
}

bool ServerEntity::getVisible()
{
	return this->m_visible;
}

ServerEntity::Type ServerEntity::getType()
{
	return m_type;
}

void ServerEntity::takeDamage(int damage, bool physical)
{

}

void ServerEntity::dealDamage(ServerEntity* target, int damage, bool physical)
{

}

void ServerEntity::heal(int health)
{

}