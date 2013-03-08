#include "StunningStrikeVictimClientSkillEffect.h"

StunningStrikeVictimClientSkillEffect::StunningStrikeVictimClientSkillEffect(unsigned int _id)
{
	this->m_lifetime = 8.0f;
	this->m_masterId = _id;

	Entity *entity = ClientEntityHandler::getEntity(_id);
	if(entity != NULL)
	{
		entity->m_model->getAnimation()->Stop();
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