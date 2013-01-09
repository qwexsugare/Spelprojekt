#include "Enemy.h"

Enemy::Enemy() : ServerEntity()
{
	m_type = Type::EnemyType;
	this->m_positon = FLOAT3(40.0f, 0.0f, 40.0f);
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_nextPosition = this->m_positon;
	this->m_reachedPosition = true;
	this->m_movementSpeed = 3.0f;
	this->m_modelId = 0;
	EntityHandler::addEntity(this);
}

void Enemy::update(float dt)
{
	//Handle incoming messages
	Message *m;

	this->setNextPosition(dt);

	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		m = this->m_messageQueue->pullIncomingMessage();

		if(m->type == Message::Collision)
		{
			//this->m_positon = FLOAT3(0.0f, 0.0f, 0.0f);
		}

		delete m;
	}

	if(this->m_reachedPosition == false)
	{
		FLOAT3 distance = this->m_nextPosition - this->m_positon;
		if(distance.length() > this->m_movementSpeed * dt)
		{
			distance = distance / distance.length();
			this->m_positon = this->m_positon + (distance * this->m_movementSpeed * dt);
		}
		else
		{
			this->m_positon = this->m_nextPosition;
			this->m_reachedPosition = true;
		}

		this->m_rotation.x = atan2(-distance.x, -distance.z);
	}

	if(this->m_health <= 0)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}

	this->m_obb->Center = XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z);
}

void Enemy::setNextPosition(float dt)
{
	Hero *hero = (Hero*)(EntityHandler::getAllHeroes()[0]);

	FLOAT3 _playerDirection= hero->getDirection(3*dt);

	FLOAT3 targetPosition = _playerDirection;
	
	//targetPosition = targetPosition * m_movementSpeed*5;

	this->m_nextPosition = targetPosition;
	this->m_reachedPosition = false;
}