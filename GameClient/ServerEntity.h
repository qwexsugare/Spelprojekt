#ifndef SERVER_ENTITY
#define SERVER_ENTITY

#include "MessageQueue.h"
#include "EntityMessage.h"
#include "DataStructures.h"
#include "DirectXMath.h"
#include "DirectXCollision.h"
using namespace DirectX;

class ServerEntity
{
protected:
	MessageQueue *m_messageQueue;
	unsigned int m_id;
	
	BoundingSphere* m_bs;
	BoundingOrientedBox* m_obb;
	FLOAT3 m_positon;
	FLOAT3 m_rotation;

	int m_health;
	int m_modelId;
public:
	ServerEntity();
	virtual ~ServerEntity();

	virtual void update(float dt);
	const BoundingSphere* getBoundingSphere()const { return this->m_bs; }
	const BoundingOrientedBox* getObb()const { return this->m_obb; }
	MessageQueue *getMessageQueue();
	EntityMessage getUpdate();

	void setId(unsigned int _id);
	void setPosition(FLOAT3 _position);

	FLOAT3 getPosition();
	unsigned int getId();
};

#endif