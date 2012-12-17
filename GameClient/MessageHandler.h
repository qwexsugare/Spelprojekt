#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "MessageQueue.h"
#include "Message.h"
#include <map>

class MessageHandler
{
private:
	int m_nextId;
	map<int,MessageQueue*> m_queues;
public:
	MessageHandler();
	~MessageHandler();

	void addQueue(MessageQueue* _queue);
	void update();
};

#endif
