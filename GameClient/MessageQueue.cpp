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
	this->m_mutex.Lock();
	Message *m  = this->m_incomingMessages.front();
	this->m_incomingMessages.pop();
	
	this->m_mutex.Unlock();
	return m;
}

Message *MessageQueue::pullOutgoingMessage()
{
	this->m_mutex.Lock();
	Message *m  = this->m_outgoingMessages.front();
	this->m_outgoingMessages.pop();
	this->m_mutex.Unlock();
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
	this->m_mutex.Lock();
	
		this->m_incomingMessages.push(_message);
	
	this->m_mutex.Unlock();
}

void MessageQueue::pushOutgoingMessage(Message *_message)
{
	this->m_mutex.Lock();
		_message->senderId = this->m_id;
		this->m_outgoingMessages.push(_message);
	
	this->m_mutex.Unlock();
}