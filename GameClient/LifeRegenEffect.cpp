#include "LifeRegenEffect.h"
#include "EntityHandler.h"
#include "UnitEntity.h"

const float LifeRegenEffect::HEAL_FACTOR = 0.2f;

LifeRegenEffect::LifeRegenEffect(unsigned int _caster)
{
	m_caster = _caster;
	m_excessHeal = 0.0f;
	m_tickTimer = 0.0f;
	this->m_obb = NULL;
	this->m_bs = new BoundingSphere();
	m_visible = false;
	m_type = OtherType;
}

LifeRegenEffect::~LifeRegenEffect()
{
	
}

void LifeRegenEffect::update(float _dt)
{
	ServerEntity* caster = EntityHandler::getServerEntity(m_caster);

	if(caster)
	{
		m_tickTimer += _dt;
		if(m_tickTimer >= 1.0f)
		{
			int healAmount = ((UnitEntity*)caster)->getWits()*HEAL_FACTOR;
			((UnitEntity*)caster)->heal(healAmount + m_excessHeal);
			m_excessHeal = ((UnitEntity*)caster)->getWits()*HEAL_FACTOR - healAmount;

			m_tickTimer -= 1.0f;
		}
	}
	else
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
}