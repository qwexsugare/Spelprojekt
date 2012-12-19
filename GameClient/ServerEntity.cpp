#include "ServerEntity.h"

ServerEntity::ServerEntity()
{
	//this->m_messageQueue = new MessageQueue();
	this->m_positon = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_rotation = FLOAT3(0.0f, 0.0f, 0.0f);
}

ServerEntity::~ServerEntity()
{
	//delete this->m_messageQueue;
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
	EntityMessage e = EntityMessage(this->m_id);

	e.setPosition(this->m_positon);
	e.setRotation(this->m_rotation);

	return e;
}

void ServerEntity::setPosition(FLOAT3 _position)
{
	this->m_positon = _position;
}

void ServerEntity::setId(unsigned int _id)
{
	this->m_id = _id;
}