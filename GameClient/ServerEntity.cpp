#include "ServerEntity.h"

ServerEntity::ServerEntity()
{
	this->m_messageQueue = new MessageQueue();
	this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_rotation = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_bs = NULL;
	this->m_modelId = 0;
	this->m_visible = true;
}

ServerEntity::ServerEntity(FLOAT3 _pos)
{
	this->m_messageQueue = new MessageQueue();
	this->m_position = _pos;
	this->m_rotation = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_bs = NULL;
	this->m_modelId = 0;
	this->m_visible = true;
}

ServerEntity::ServerEntity(FLOAT3 _position, FLOAT3 _rotation, BoundingOrientedBox* _obb, Type _type)
{
	this->m_messageQueue = new MessageQueue();
	this->m_position = _position;
	this->m_rotation = _rotation;
	this->m_obb = _obb;
	this->m_bs = NULL;
	this->m_type = _type;
	this->m_modelId = 0;
	this->m_visible = false;
}

ServerEntity::~ServerEntity()
{
	delete this->m_messageQueue;
	delete this->m_bs;
	delete this->m_obb;
}

FLOAT3 ServerEntity::getRotation()
{
	return this->m_rotation;
}

void ServerEntity::update(float dt)
{
	//Handle incoming messages
	Message *m;

	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		m = this->m_messageQueue->pullIncomingMessage();


		delete m;
	}
}

MessageQueue *ServerEntity::getMessageQueue()
{
	return this->m_messageQueue;
}

NetworkEntityMessage ServerEntity::getUpdate()
{
	NetworkEntityMessage e = NetworkEntityMessage(this->m_id, this->m_position.x,this->m_position.z, this->m_rotation.y,this->getPosition().x,this->getPosition().z,this->getEndPos().x,this->getEndPos().z,this->getMovementSpeed());

	return e;
}

ContainmentType ServerEntity::contains(const BoundingSphere& _bs)const
{
	if(m_obb)
	{
		return m_obb->Contains(_bs);
	}
	else if(m_bs)
	{
		return m_bs->Contains(_bs);
	}
	else return ContainmentType::DISJOINT;
}

void ServerEntity::setPosition(FLOAT3 _position)
{
	this->m_position = _position;

	if(this->m_obb)
	{
		this->m_obb->Center = XMFLOAT3(_position.x, _position.y, _position.z);
	}
	else if(this->m_bs)
	{
		this->m_bs->Center = XMFLOAT3(_position.x, _position.y, _position.z);
	}
}

void ServerEntity::setId(unsigned int _id)
{
	this->m_id = _id;
}

void ServerEntity::setModelId(unsigned int _modelId)
{
	this->m_modelId = _modelId;
}

void ServerEntity::setVisible(bool _visible)
{
	this->m_visible = _visible;
}

FLOAT3 ServerEntity::getPosition()
{
	return this->m_position;
}

unsigned int ServerEntity::getId()
{
	return this->m_id;
}

unsigned int ServerEntity::getModelId()
{
	return this->m_modelId;
}

bool ServerEntity::getVisible()
{
	return this->m_visible;
}
int ServerEntity::getHealth()
{
	return 0;
}

ServerEntity::Type ServerEntity::getType()
{
	return m_type;
}

void ServerEntity::takeDamage(unsigned int damageDealerId, int physicalDamage, int mentalDamage)
{

}

void ServerEntity::dealDamage(ServerEntity* target, int physicalDamage, int mentalDamage)
{

}

void ServerEntity::heal(int health)
{

}

FLOAT3 ServerEntity::getDirection()
{
	FLOAT3 f;
	f.x=f.y=f.z=0;
	return f;
}

FLOAT3 ServerEntity::getEndPos()
{
	FLOAT3 f;
	f.x=f.y=f.z=0;
	return f;
}
float ServerEntity::getMovementSpeed()
{
	return 0;
}