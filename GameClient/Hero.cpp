#include "Hero.h"

Hero::Hero() : UnitEntity()
{
	this->m_type = Type::HeroType;
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_nextPosition = this->m_position;
	this->m_reachedPosition = true;
	this->m_movementSpeed = 5.0f;

	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 15.0f;
	this->m_hasTarget = false;
	m_strength = 5;
	m_agility = 5;
	m_wits = 20;
	m_fortitude = 5;
}

Hero::~Hero()
{

}

void Hero::update(float dt)
{
	//Handle incoming messages
	Message *m;

	while(this->m_messageQueue->incomingQueueEmpty() == false)
	{
		m = this->m_messageQueue->pullIncomingMessage();

		if(m->type == Message::Collision)
		{
			//this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
		}

		delete m;
	}

	if(this->m_attackCooldown > 0.0f)
	{
		this->m_attackCooldown = this->m_attackCooldown - dt;
	}

	if(this->m_hasTarget == true)
	{
		ServerEntity *se = EntityHandler::getServerEntity(this->m_target);

		if(se == NULL)
		{
			this->m_hasTarget = false;
		}
		else
		{
			FLOAT3 distance = se->getPosition() - this->m_position;
			this->m_rotation.x = atan2(-distance.x, -distance.z);

			if(se != NULL && (se->getPosition() - this->m_position).length() <= this->m_attackRange)
			{
				if(this->m_attackCooldown <= 0.0f)
				{
					EntityHandler::addEntity(new Projectile(this->m_position, se->getPosition() - this->m_position, 2.0f, 6.0f));
					this->m_attackCooldown = 0.2f;
				}
			}
			else
			{
				if(distance.length() - this->m_attackRange > this->m_movementSpeed * dt)
				{
					distance = distance / distance.length();
					this->m_position = this->m_position + (distance * this->m_movementSpeed * dt);
				}
				else
				{
					this->m_position = this->m_position + distance * (distance.length() - this->m_attackRange);
				}

				this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
				this->m_rotation.x = atan2(-distance.x, -distance.z);
			}
		}
	}
	else if(this->m_reachedPosition == false)
	{
		FLOAT3 distance = this->m_nextPosition - this->m_position;
		if(distance.length() > this->m_movementSpeed * dt)
		{
			distance = distance / distance.length();
			this->m_position = this->m_position + (distance * this->m_movementSpeed * dt);
		}
		else
		{
			this->m_position = this->m_nextPosition;
			this->m_reachedPosition = true;
		}

		this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
		this->m_rotation.x = atan2(-distance.x, -distance.z);
	}

	if(this->m_health <= 0)
	{
		this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
		this->m_health = 100;
		this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
	}
}

void Hero::setNextPosition(FLOAT3 _nextPosition)
{
	this->m_nextPosition = _nextPosition;
	this->m_reachedPosition = false;
	this->m_hasTarget = false;
}

void Hero::setTarget(unsigned int _target)
{
	ServerEntity *se = EntityHandler::getServerEntity(_target);

	if(se != NULL && se->getType() == ServerEntity::EnemyType)
	{
		this->m_hasTarget = true;
		this->m_target = _target;
	}
}

FLOAT3 Hero::getDirection()
{
	if( (m_nextPosition - m_position).length() > 0)
	{
		return m_nextPosition-m_position;
		
	}
	else
		return m_position;
}

void Hero::takeDamage(int damage)
{
	this->m_health = this->m_health - damage;
}

