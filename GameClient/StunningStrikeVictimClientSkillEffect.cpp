#include "StunningStrikeVictimClientSkillEffect.h"

StunningStrikeVictimClientSkillEffect::StunningStrikeVictimClientSkillEffect(unsigned int _id)
{
	this->m_lifetime = 8.0f;
	this->m_masterId = _id;

	Entity *entity = ClientEntityHandler::getEntity(_id);
	if(entity != NULL)
	{
		if(entity->m_type == ServerEntity::EnemyType)
		{
			switch(entity->m_subtype)
			{
			case Enemy::EnemyType::BRUTE_STEED:
				entity->m_model->getAnimation()->PlayLoop("BeastStunned", 4);
				break;
			case Enemy::EnemyType::FROST_DEMON:
				entity->m_model->getAnimation()->PlayLoop("ImpStunned", 4);
				break;
			case Enemy::EnemyType::HELLFIRE_STEED:
				entity->m_model->getAnimation()->PlayLoop("BeastStunned", 4);
				break;
			case Enemy::EnemyType::IMP:
				entity->m_model->getAnimation()->PlayLoop("ImpStunned", 4);
				break;
			case Enemy::EnemyType::SHADE:
				entity->m_model->getAnimation()->PlayLoop("ImpStunned", 4);
				break;
			case Enemy::EnemyType::SOUL_EATER_STEED:
				entity->m_model->getAnimation()->PlayLoop("BeastStunned", 4);
				break;
			case Enemy::EnemyType::SPITTING_DEMON:
				entity->m_model->getAnimation()->PlayLoop("ImpStunned", 4);
				break;
			case Enemy::EnemyType::THUNDERSTEED:
				entity->m_model->getAnimation()->PlayLoop("BeastStunned", 4);
				break;
			}
		}
		else if(entity->m_type == ServerEntity::HeroType)
		{
			if(entity->m_weapon == ModelIdHolder::AOE)
			{
				entity->m_model->getAnimation()->PlayLoop("2Hidle");
				entity->m_model->getAnimation()->Play("Stunn2Hand");
			}
			else
			{
				entity->m_model->getAnimation()->PlayLoop("idle");
				entity->m_model->getAnimation()->Play("Stunn1Hand");
			}
		}
	}
}

StunningStrikeVictimClientSkillEffect::~StunningStrikeVictimClientSkillEffect()
{

}

void StunningStrikeVictimClientSkillEffect::update(float _dt)
{
	this->m_lifetime = this->m_lifetime - _dt;
}

bool StunningStrikeVictimClientSkillEffect::getActive()
{
	if(this->m_lifetime > 0.0f)
	{
		return true;
	}
	else
	{
		Entity *entity = ClientEntityHandler::getEntity(this->m_masterId);

		if(entity != NULL)
		{
			entity->m_model->getAnimation()->PlayLoop("run");
		}

		return false;
	}
}