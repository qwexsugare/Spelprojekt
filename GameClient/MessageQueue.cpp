#include "MessageQueue.h"

MessageQueue::MessageQueue()
{
	this->m_incomingMessages = queue<Message*>();
	this->m_outgoingMessages = queue<Message*>();
}

MessageQueue::~MessageQueue()
{
	while(this->m_incomingMessages.empty() == false)
	{
		delete this->m_incomingMessages.front();
		this->m_incomingMessages.pop();
	}

	while(this->m_outgoingMessages.empty() == false)
	{
		delete this->m_outgoingMessages.front();
		this->m_outgoingMessages.pop();
	}
}

int MessageQueue::getId()
{
	return this->m_id;
}

void MessageQueue::setId(int _id)
{
	this->m_id = _id;
}

Message *MessageQueue::pullIncomingMessage()
{
	Message *m  = this->m_incomingMessages.front();
	this->m_incomingMessages.pop();

	return m;
}

Message *MessageQueue::pullOutgoingMessage()
{
	Message *m  = this->m_outgoingMessages.front();
	this->m_outgoingMessages.pop();

	return m;
}

bool MessageQueue::incomingQueueEmpty()
{
	return this->m_incomingMessages.empty();
}

bool MessageQueue::outgoingQueueEmpty()
{
	return this->m_outgoingMessages.empty();
}

void MessageQueue::pushIncomingMessage(Message* _message)
{
	this->m_incomingMessages.push(_message);
}

void MessageQueue::pushOutgoingMessage(Message *_message)
{
	_message->senderId = this->m_id;
	this->m_outgoingMessages.push(_message);
}