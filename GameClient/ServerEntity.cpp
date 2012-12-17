#include "ServerEntity.h"

ServerEntity::ServerEntity()
{
	//this->m_messageQueue = new MessageQueue();
	this->m_positon = FLOAT3(0.0f, 0.0f, 0.0f);
}

ServerEntity::~ServerEntity()
{
	//delete this->m_messageQueue;
}

void ServerEntity::update()
{
	////Handle incoming messages
	//Message *m;

	//while(this->m_messageQueue->incomingQueueEmpty() == false)
	//{
	//	m = this->m_messageQueue->pullIncomingMessage();

	//	if(m->type == MessageTypes::MoveEntity)
	//	{
	//		MoveMessage *mm = (MoveMessage*)m;
	//		this->m_positon = mm->position;
	//	}

	//	delete m;
	//}
}

//MessageQueue *ServerEntity::getMessageQueue()
//{
//	return this->m_messageQueue;
//}

EntityMessage ServerEntity::getUpdate()
{
	EntityMessage e = EntityMessage();
	e.setPosition(this->m_positon);

	return e;
}

void ServerEntity::setPosition(FLOAT3 _position)
{
	this->m_positon = _position;
}