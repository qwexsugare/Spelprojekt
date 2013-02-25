#ifndef SERVER_ENTITY
#define SERVER_ENTITY

#include "MessageQueue.h"
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
	FLOAT3 m_bvOffset;

	unsigned int m_modelId;
	bool m_visible;

public:
	static enum Type{EnemyType, HeroType, OtherType, ProjectileType, StaticType, TowerType};
	Type m_type;
	ServerEntity();
	ServerEntity(FLOAT3 m_pos);
	ServerEntity(FLOAT3 _position, FLOAT3 _rotation, BoundingOrientedBox* _obb, Type _type);
	virtual ~ServerEntity();

	virtual void update(float dt);
	const BoundingSphere* getBs()const { return this->m_bs; }
	const BoundingOrientedBox* getObb()const { return this->m_obb; }
	MessageQueue *getMessageQueue();
	virtual NetworkEntityMessage getUpdate();

	void setId(unsigned int _id);
	void setModelId(unsigned int _modelId);
	void setPosition(FLOAT3 _position);
	void setVisible(bool _visible);

	FLOAT3 getPosition();
	FLOAT3 getRotation();
	unsigned int getId();
	unsigned int getModelId();
	Type getType();
	bool getVisible();

	virtual int getHealth();

	ContainmentType contains(const BoundingSphere& _bs)const;
	ContainmentType contains(const BoundingOrientedBox& _obb)const;
	bool intersects(const BoundingOrientedBox& _obb)const;

	virtual void takeDamage(unsigned int damageDealerId, int physicalDamage, int mentalDamage);
	virtual void dealDamage(ServerEntity* target, int physicalDamage, int mentalDamage);
	void heal(int health);
	virtual FLOAT3 getDirection();
	virtual FLOAT3 getEndPos();
	virtual float getMovementSpeed();
};

#endif