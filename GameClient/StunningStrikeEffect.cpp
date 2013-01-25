#include "StunningStrikeEffect.h"
#include "EntityHandler.h"
#include "MyAlgorithms.h"

StunningStrikeEffect::StunningStrikeEffect(FLOAT3 _position, int _damage)
{
	m_damage = _damage;
	m_position = _position;

	this->m_obb = new BoundingOrientedBox();
	m_modelId = 0;
	m_timer = 0.0f;
	m_type = OtherType;

	if(random(1, 100) <= 50)
	{
		vector<ServerEntity*>* enemies = EntityHandler::getAllEnemies();

		for(int i = 0; i < enemies->size(); i++)
		{
			if(((*enemies)[i]->getPosition()-m_position).length() <= AOE)
			{
				((UnitEntity*)EntityHandler::getClosestEnemy(this))->stun(8);
				this->dealDamage((*enemies)[i], this->m_damage, false);
			}
		}

		delete enemies;
	}
	else
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}

StunningStrikeEffect::~StunningStrikeEffect()
{

}

void StunningStrikeEffect::update(float _dt)
{
	m_timer += _dt;

	if(m_timer > LIFETIME)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}