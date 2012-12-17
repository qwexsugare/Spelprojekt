#include "MessageHandler.h"

MessageHandler::MessageHandler()
{
	this->m_nextId = 0;
}

MessageHandler::~MessageHandler()
{

}

void MessageHandler::addQueue(MessageQueue* _queue)
{
	_queue->setId(this->m_nextId);
	this->m_queues[this->m_nextId] = _queue;
	this->m_nextId++;
}

void MessageHandler::update()
{
	queue<Message*> messages;
	map<int, MessageQueue*>::iterator i = this->m_queues.begin();
	Message *m;
	bool found;

	while(i != this->m_queues.end())
	{
		while(i->second->outgoingQueueEmpty() == false)
		{
			messages.push(i->second->pullOutgoingMessage());
		}

		i++;
	}

	while(messages.empty() == false)
	{
		m = messages.front();
		messages.pop();
		i = this->m_queues.begin();
		found = false;

		while(i != this->m_queues.end())
		{
			if(i->first == m->reciverId)
			{
				i->second->pushIncomingMessage(m);
				i = this->m_queues.end();
				found = true;
			}
			else
			{
				i++;
			}
		}

		if(found == false)
		{
			delete m;
		}
	}
}