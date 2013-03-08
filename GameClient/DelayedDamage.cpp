#include "DelayedDamage.h"

DelayedDamage::DelayedDamage(unsigned int _caster, unsigned int _target, float _timeToImpact, int _physicalDamage, int _mentalDamage, Skill::SKILLS skillId)
{
	this->m_timeToImpact = _timeToImpact;
	this->m_caster = _caster;
	this->m_target = _target;
	this->m_physicalDamage = _physicalDamage;
	this->m_mentalDamage = _mentalDamage;
	this->m_visible = false;

	this->m_obb = NULL;
	this->m_bs = NULL;

	ServerEntity *caster = EntityHandler::getServerEntity(_caster);
	this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(skillId, _caster, _target, caster->getPosition()));
}

DelayedDamage::~DelayedDamage()
{

}

void DelayedDamage::update(float dt)
{
	ServerEntity* target = EntityHandler::getServerEntity(this->m_target);
	if(target)
	{
		ServerEntity* caster = EntityHandler::getServerEntity(this->m_caster);
		if(caster)
		{
			this->m_timeToImpact = max(this->m_timeToImpact - dt, 0.0f);

			if(this->m_timeToImpact == 0.0f)
			{
				caster->dealDamage(target, this->m_physicalDamage, this->m_mentalDamage);
				this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
			}
		}
		else
		{
			this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
		}
	}
	else
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}