#include "Hero.h"
#include "Arrow.h"

extern Pathfinder* g_pathfinder;

Hero::Hero() : UnitEntity()
{
	this->m_type = Type::HeroType;
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_nextPosition = this->m_position;
	this->m_reachedPosition = true;
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 5.0f;
	this->m_hasTarget = false;
	this->m_baseMovementSpeed = 3.1f;
	this->m_movementSpeed = this->m_baseMovementSpeed;
	this->m_baseAttackSpeed = 1.0f;
	this->m_attackSpeed = this->m_baseAttackSpeed;
	this->increaseStrength(5);
	this->increaseAgility(2);
	this->increaseWits(1);
	this->increaseFortitude(4);
}

Hero::Hero(HERO_TYPE _heroType, int _playerId) : UnitEntity()
{
	this->m_heroType = _heroType;
	this->m_playerId = _playerId;
	this->m_type = Type::HeroType;
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_nextPosition = this->m_position;
	this->m_reachedPosition = true;
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 5.0f;
	this->m_hasTarget = false;
}

Hero::~Hero()
{

}

Hero::HERO_TYPE Hero::getHeroType()const
{
	return m_heroType;
}

void Hero::updateSpecificUnitEntity(float dt)
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
					this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::ATTACK, this->m_id, se->getId(), this->m_position));
					EntityHandler::addEntity(new Arrow((m_position-se->getPosition()).length(), se->getId(), m_id));
					//this->dealDamage(se, this->m_physicalDamage, this->m_mentalDamage); // dont
					this->m_attackCooldown = this->m_attackSpeed;
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
		float lol = 0.0f;

		if(this->m_reallyReachedPosition == false)
		{
			lol = 0.125f;
		}

		if(distance.length() - lol > this->m_movementSpeed * dt)
		{
			distance = distance / distance.length();
			this->m_position = this->m_position + (distance * this->m_movementSpeed * dt);
		}
		else
		{
			if(this->m_pathCounter < this->m_path.nrOfPoints - 1)
			{
				this->m_nextPosition = FLOAT3(this->m_path.points[this->m_pathCounter].x, 0.0f, this->m_path.points[this->m_pathCounter].y);
				this->m_pathCounter++;
			}
			else if(this->m_reallyReachedPosition == false)
			{
				//this->m_nextPosition = this->m_goalPosition;
				this->m_reallyReachedPosition = true;
				this->m_position = this->m_nextPosition;
				this->m_reachedPosition = true;
			}
			else
			{
				this->m_position = this->m_nextPosition;
				this->m_reachedPosition = true;
			}
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
	this->m_path = g_pathfinder->getPath(FLOAT2(this->m_position.x, this->m_position.z), FLOAT2(_nextPosition.x, _nextPosition.z));

	if(this->m_path.nrOfPoints > 1)
	{
		this->m_nextPosition = FLOAT3(this->m_path.points[1].x, 0.0f, this->m_path.points[1].y);
		this->m_goalPosition = _nextPosition;
		this->m_pathCounter = 2;
		this->m_reachedPosition = false;
		this->m_hasTarget = false;
		this->m_target = NULL;
		this->m_reallyReachedPosition = false;
	}
	else if(this->m_path.nrOfPoints == 1)
	{
		this->m_nextPosition = _nextPosition;
		this->m_goalPosition = _nextPosition;
		this->m_pathCounter = 1;
		this->m_reachedPosition = false;
		this->m_hasTarget = false;
		this->m_target = NULL;
		this->m_reallyReachedPosition = false;
	}
	else
	{
		this->m_path = Path();
		this->m_pathCounter = 0;
		this->m_reachedPosition = true;
		this->m_hasTarget = false;
		this->m_target = NULL;
		this->m_reallyReachedPosition = true;
	}
}

void Hero::setTarget(unsigned int _target)
{
	ServerEntity *se = EntityHandler::getServerEntity(_target);

	if(se != NULL && se->getType() == ServerEntity::EnemyType)
	{
		this->m_hasTarget = true;
		this->m_target = _target;
		this->m_reachedPosition = true;
		this->m_reallyReachedPosition = true;
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