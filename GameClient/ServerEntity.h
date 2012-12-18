#ifndef SERVER_ENTITY
#define SERVER_ENTITY

#include "MessageQueue.h"
#include "EntityMessage.h"
#include "DataStructures.h"

class ServerEntity
{
protected:
	MessageQueue *m_messageQueue;
	unsigned int m_id;

	FLOAT3 m_positon;
	FLOAT3 m_rotation;
	int m_modelId;
public:
	ServerEntity();
	virtual ~ServerEntity();

	virtual void update();
	MessageQueue *getMessageQueue();
	EntityMessage getUpdate();

	void setId(unsigned int _id);
	void setPosition(FLOAT3 _position);
};

#endif