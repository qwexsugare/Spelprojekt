#pragma once

#include "Message.h"
#include <queue>

class MessageQueue
{
private:
	int m_id;

	queue<Message> m_incomingMessages;
	queue<Message> m_outgoingMessages;
public:
	MessageQueue();
	~MessageQueue();

	Message pullIncomingMessage();
	Message pullOutgoingMessage();

	void pushIncomingMessage(Message _message);
	void pushOutgoingMessage(Message _message);
};

