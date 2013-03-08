#include "Hero.h"

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
	this->m_startPos=FLOAT3(0.0,0.0,0.0);
	this->m_weaponType = WEAPON_TYPE::NO_WEAPON;
	this->m_alive = true;
}

Hero::Hero(HERO_TYPE _heroType, int _playerId) : UnitEntity()
{
	this->m_heroType = _heroType;
	this->m_playerId = _playerId;
	this->m_type = Type::HeroType;
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_nextPosition = this->m_position;
	this->m_reachedPosition = true;
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 5.0f;
	this->m_hasTarget = false;
	this->m_startPos=FLOAT3(0.0,0.0,0.0);
	this->m_weaponType = WEAPON_TYPE::NO_WEAPON;
	this->m_alive = true;
}

Hero::~Hero()
{

}

void Hero::activateAllPassiveSkills()
{
	for(int i = 0; i < m_skills.size(); i++)
	{
		if(m_skills[i]->getId() == Skill::COURAGE_HONOR_VALOR)
		{
			m_skills[i]->activate(this->getId());
		}
		else if(m_skills[i]->getId() == Skill::LIFE_REGEN)
		{
			m_skills[i]->activate(this->getId());
		}
		else if(m_skills[i]->getId() == Skill::ENIGMATIC_PRESENCE)
		{
			m_skills[i]->activate(this->getId());
		}
		else if(m_skills[i]->getId() == Skill::ENHANCED_DEVELOPMENT)
		{
			m_skills[i]->activate(this->getId());
		}
		else if(m_skills[i]->getId() == Skill::READY_AIM_FIRE)
		{
			m_skills[i]->activate(this->getId());
		}
	}
}

Hero::HERO_TYPE Hero::getHeroType()const
{
	return m_heroType;
}

void Hero::updateSpecificUnitEntity(float dt)
{
	if(this->m_health > 0)
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
				this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::IDLE, this->m_id, this->m_position));
			}
			else
			{
				FLOAT3 distance = se->getPosition() - this->m_position;
				this->m_rotation.x = atan2(-distance.x, -distance.z);

				//If the hero is in range, KILL IT!
				if(se != NULL)
				{
					if((se->getPosition() - this->m_position).length() <= this->m_regularAttack->getRange())
					{
						if(this->m_attackCooldown <= 0.0f)
						{
							//this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::ATTACK, this->m_id, se->getId(), this->m_position));
							//EntityHandler::addEntity(new Arrow((m_position-se->getPosition()).length(), se->getId(), m_id));
							//this->dealDamage(se, this->m_physicalDamage, this->m_mentalDamage); // dont
							this->attack(this->m_target);
							this->m_attackCooldown = this->m_attackSpeed;
							this->m_nextPosition = this->m_position;
							this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
						}

						if(this->m_reachedPosition == false)
						{
							this->m_reachedPosition = true;
							this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::IDLE, this->m_id, this->m_position));
						}
					}
					else //Otherwise you should find a way to get to the enemy
					{
						if(this->m_reachedPosition == true)
						{
							this->m_path = g_pathfinder->getPath(FLOAT2(this->m_position.x, this->m_position.z), FLOAT2(se->getPosition().x, se->getPosition().z));

							if(this->m_path.nrOfPoints > 0)
							{
								this->m_pathCounter = 1;
								this->m_nextPosition = FLOAT3(this->m_path.points[0].x, 0.0f, this->m_path.points[0].y);
								this->m_reachedPosition = false;
								this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::MOVE, this->m_id, this->m_position));
								this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
							}
						}
						else //Move along the path
						{
							distance = this->m_nextPosition - this->m_position;

							if(distance.length() - 0.125f > this->m_movementSpeed * dt)
							{
								distance = distance / distance.length();
								this->m_position = this->m_position + (distance * this->m_movementSpeed * dt);
								this->m_rotation.x = atan2(-distance.x, -distance.z);
							}
							else
							{
								if(this->m_pathCounter < this->m_path.nrOfPoints)
								{
									this->m_nextPosition = FLOAT3(this->m_path.points[this->m_pathCounter].x, 0.0f, this->m_path.points[this->m_pathCounter].y);
									this->m_pathCounter++;
									this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
								}
								else if(this->m_reachedPosition == false)
								{
									this->m_position = this->m_nextPosition;
									this->m_reachedPosition = true;
									this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::IDLE, this->m_id, this->m_position));
									this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
									this->m_messageQueue->pushOutgoingMessage(new UpdateEntityMessage(this->getId(),this->getPosition().x,this->getPosition().z,this->getRotation().x,0.0f,0.0f,0.0f,0.0f,this->getMovementSpeed()));
								}

								this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
							}
						}
					}
				}
				else //The target doesn't exist
				{
					this->m_hasTarget = false;
					this->m_reachedPosition = true;
					this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::IDLE, this->m_id, this->m_position));
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
				if(this->m_pathCounter < this->m_path.nrOfPoints)
				{
					this->m_nextPosition = FLOAT3(this->m_path.points[this->m_pathCounter].x, 0.0f, this->m_path.points[this->m_pathCounter].y);
					this->m_pathCounter++;

					this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
					this->m_rotation.x = atan2(-distance.x, -distance.z);

					this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
				}
				else
				{
					this->m_nextPosition = this->m_position;
					this->m_reachedPosition = true;
					//this->m_startPos= m_nextPosition;
					this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
					this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::IDLE, this->m_id, this->m_position));
				}
			}

			this->m_obb->Center = XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);
			this->m_rotation.x = atan2(-distance.x, -distance.z);
		}
	}
	else if(this->m_alive == true)
	{
		this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::DEATH, this->m_id, this->m_position));
		this->m_position = FLOAT3(-1000.0f, 0.0f, -1000.0f);
		this->m_hasTarget = NULL;
		this->m_reachedPosition = true;
		this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
		this->m_messageQueue->pushOutgoingMessage(new HeroDiedMessage(this->m_id, this->m_playerId));
		this->m_alive = false;
		int id = Statistics::convertSimonsIdToRealId(this->m_id);
		Statistics::getStatisticsPlayer(id).increaseDeathCount();
	}
}

void Hero::setNextPosition(FLOAT3 _nextPosition)
{
	if(this->m_alive == true)
	{
		if(g_pathfinder->sameGridPosition(FLOAT2(this->m_position.x, this->m_position.z), FLOAT2(_nextPosition.x, _nextPosition.z)) == false)
		{
			this->m_path = g_pathfinder->getPath(FLOAT2(this->m_position.x, this->m_position.z), FLOAT2(_nextPosition.x, _nextPosition.z));

			if(this->m_path.nrOfPoints > 1)
			{
				this->m_nextPosition = FLOAT3(this->m_path.points[1].x, 0.0f, this->m_path.points[1].y);
				//this->m_startPos= FLOAT3(this->m_path.points[0].x, 0.0f, this->m_path.points[0].y);
				this->m_goalPosition = _nextPosition;
				this->m_pathCounter = 2;
				this->m_reachedPosition = false;
				this->m_hasTarget = false;
				this->m_target = NULL;
				this->m_reallyReachedPosition = false;

				this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
				this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::MOVE, this->m_id, this->m_position));
			}
			else if(this->m_path.nrOfPoints == 1)
			{
				//this->m_startPos= this->m_nextPosition;
				this->m_nextPosition = _nextPosition;
				this->m_goalPosition = _nextPosition;
				this->m_pathCounter = 1;
				this->m_reachedPosition = false;
				this->m_hasTarget = false;
				this->m_target = NULL;
				this->m_reallyReachedPosition = false;

				this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
				this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::MOVE, this->m_id, this->m_position));
			}
			else
			{
				this->m_path = Path();
				this->m_pathCounter = 0;
				this->m_reachedPosition = true;
				this->m_hasTarget = false;
				this->m_target = NULL;
				this->m_reallyReachedPosition = true;
				this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::IDLE, this->m_id, this->m_position));
				//this->m_startPos= m_nextPosition;

				this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
			} 
		}
		else
		{
			this->m_path = Path();
			this->m_pathCounter = 0;
			this->m_reachedPosition = true;
			this->m_nextPosition = m_position;
			this->m_hasTarget = false;
			this->m_target = NULL;
			this->m_reallyReachedPosition = true;
			this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::IDLE, this->m_id, this->m_position));
			//this->m_startPos= m_nextPosition;

			this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
		}
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

UpdateEntityMessage* Hero::getUpdateEntityMessage()
{	
	return new UpdateEntityMessage(this->getId(),this->getPosition().x,this->getPosition().z,this->getRotation().x,this->m_startPos.x,this->m_startPos.z,this->m_nextPosition.x,this->m_nextPosition.z,this->getMovementSpeed());
}

FLOAT3 Hero::getEndPos()
{
	return this->m_nextPosition;
}

unsigned short Hero::getWeaponType()
{
	return this->m_weaponType;
}

void Hero::respawn(FLOAT3 _position)
{
	this->m_position = _position;
	this->m_health = this->m_maxHealth;
	this->m_hasTarget = false;
	this->m_nextPosition = this->m_position;
	this->m_reachedPosition = true;
	this->m_messageQueue->pushOutgoingMessage(this->getUpdateEntityMessage());
	this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::IDLE, this->m_id, this->m_position));
	this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::RESPAWN, this->m_id, this->m_position));
	this->m_messageQueue->pushOutgoingMessage(new updateEntityHealth(this->m_id, this->m_health));
	this->m_alive = true;
}

bool Hero::getAlive()
{
	return this->m_alive;
}