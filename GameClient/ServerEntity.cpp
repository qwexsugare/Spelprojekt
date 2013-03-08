#include "ServerEntity.h"

ServerEntity::ServerEntity()
{
	this->m_messageQueue = new MessageQueue();
	this->m_rotation = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_bs = NULL;
	this->m_obb = NULL;
	this->m_modelId = 0;
	this->m_visible = true;
	this->m_bvOffset = FLOAT3(0.0f, 0.0f, 0.0f);
	this->setPosition(FLOAT3(0.0f, 0.0f, 0.0f)); // Do this last.
}

ServerEntity::ServerEntity(FLOAT3 _pos)
{
	this->m_messageQueue = new MessageQueue();
	this->m_rotation = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_bs = NULL;
	this->m_obb = NULL;
	this->m_modelId = 0;
	this->m_visible = true;
	this->m_bvOffset = FLOAT3(0.0f, 0.0f, 0.0f);
	this->setPosition(_pos); // Do this last.
}

ServerEntity::ServerEntity(FLOAT3 _position, FLOAT3 _rotation, BoundingOrientedBox* _obb, Type _type)
{
	this->m_messageQueue = new MessageQueue();
	this->m_rotation = _rotation;
	this->m_obb = _obb;
	this->m_bvOffset = FLOAT3(_obb->Center.x, _obb->Center.y, _obb->Center.z);
	this->m_bs = NULL;
	this->m_type = _type;
	this->m_modelId = 0;
	this->m_visible = false;
	this->setPosition(_position); // Do this last.
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
		return m_obb->Contains(_bs);
	else if(m_bs)
		return m_bs->Contains(_bs);
	else
		return ContainmentType::DISJOINT;
}

ContainmentType ServerEntity::contains(const BoundingOrientedBox& _obb)const
{
	if(m_obb)
		return m_obb->Contains(_obb);
	else if(m_bs)
		return m_bs->Contains(_obb);
	else
		return ContainmentType::DISJOINT;
}

bool ServerEntity::intersects(const BoundingOrientedBox& _obb)const
{
	if(m_obb)
		return m_obb->Intersects(_obb);
	else if(m_bs)
		return m_bs->Intersects(_obb);
	else
		return false;
}

bool ServerEntity::intersects(const BoundingSphere& _bs)const
{
	if(m_obb)
		return m_obb->Intersects(_bs);
	else if(m_bs)
		return m_bs->Intersects(_bs);
	else
		return false;
}

bool ServerEntity::intersects(float& _dist, D3DXVECTOR3 _origin, D3DXVECTOR3 _direction)const
{
	bool result;
	
	XMVECTOR origin = XMLoadFloat3(&XMFLOAT3(_origin.x, _origin.y, _origin.z));
	_direction = -_direction;
	XMVECTOR direction = XMLoadFloat3(&XMFLOAT3(_direction.x, _direction.y, _direction.z));

	if(this->m_obb)
	{
		result = this->m_obb->Intersects(origin, direction, _dist);
	}
	else if(this->m_bs)
		result = this->m_bs->Intersects(origin, direction, _dist);
	else
	{
		_dist = 0;
		result = false;
	}

	return result;
}

void ServerEntity::setPosition(FLOAT3 _position)
{
	this->m_position = _position;

	if(this->m_obb)
	{
		this->m_obb->Center = XMFLOAT3(m_position.x+m_bvOffset.x, m_position.y+m_bvOffset.y, m_position.z+m_bvOffset.z);
	}
	else if(this->m_bs)
	{
		this->m_bs->Center = XMFLOAT3(m_position.x+m_bvOffset.x, m_position.y+m_bvOffset.y, m_position.z+m_bvOffset.z);
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

int ServerEntity::getSubType()const
{
	return -1;
}

void ServerEntity::takeDamage(unsigned int damageDealerId, int physicalDamage, int mentalDamage)
{

}

void ServerEntity::dealDamage(ServerEntity* target, int physicalDamage, int mentalDamage)
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

unsigned short ServerEntity::getWeaponType()
{
	return 0;
}