#include "LifeRegenEffect.h"
#include "EntityHandler.h"
#include "UnitEntity.h"

const float LifeRegenEffect::HEAL_FACTOR = 0.2f;

LifeRegenEffect::LifeRegenEffect(unsigned int _caster)
{
	m_caster = _caster;

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
		caster->heal(max(int(((UnitEntity*)caster)->getWits()*HEAL_FACTOR), 1));
	else
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
}