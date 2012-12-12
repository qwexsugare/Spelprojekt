#include "MessageQueue.h"

MessageQueue::MessageQueue()
{

}

MessageQueue::~MessageQueue()
{

}

Message MessageQueue::pullIncomingMessage()
{
	Message m  = this->m_incomingMessages.front();
	this->m_incomingMessages.pop();

	return m;
}

Message MessageQueue::pullOutgoingMessage()
{
	Message m  = this->m_outgoingMessages.front();
	this->m_outgoingMessages.pop();

	return m;
}

void MessageQueue::pushIncomingMessage(Message _message)
{
	this->m_incomingMessages.push(_message);
}

void MessageQueue::pushOutgoingMessage(Message _message)
{
	_message.senderId = this->m_id;
	this->m_outgoingMessages.push(_message);
}