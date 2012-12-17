#ifndef SERVER_ENTITY
#define SERVER_ENTITY

#include "MessageQueue.h"
#include "EntityMessage.h"

class ServerEntity
{
private:
	MessageQueue *m_messageQueue;
	FLOAT3 m_positon;
	int m_modelId;
public:
	ServerEntity();
	virtual ~ServerEntity();

	virtual void update();
	MessageQueue *getMessageQueue();
	EntityMessage getUpdate();
};

#endif