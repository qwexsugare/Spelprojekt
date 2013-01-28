#ifndef SERVER_ENTITY
#define SERVER_ENTITY

#include "MessageQueue.h"
#include "EntityMessage.h"
#include "NetworkEntityMessage.h"
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
	FLOAT3 m_position;
	FLOAT3 m_rotation;

	unsigned int m_modelId;
	bool m_visible;

public:
	static enum Type{EnemyType, HeroType, OtherType, ProjectileType};
	Type m_type;
	ServerEntity();
	ServerEntity(FLOAT3 m_pos);
	virtual ~ServerEntity();

	virtual void update(float dt);
	const BoundingSphere* getBoundingSphere()const { return this->m_bs; }
	const BoundingOrientedBox* getObb()const { return this->m_obb; }
	MessageQueue *getMessageQueue();
	//EntityMessage getUpdate();
	NetworkEntityMessage getUpdate();

	void setId(unsigned int _id);
	void setModelId(unsigned int _modelId);
	void setPosition(FLOAT3 _position);
	void setVisible(bool _visible);

	FLOAT3 getPosition();
	unsigned int getId();
	unsigned int getModelId();
	Type getType();
	bool getVisible();

	virtual void takeDamage(int physicalDamage, int mentalDamage);
	virtual void dealDamage(ServerEntity* target, int physicalDamage, int mentalDamage);
	void heal(int health);
};

#endif