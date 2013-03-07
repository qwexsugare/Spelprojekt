#include "HypnoticStareEffect.h"
#include "EntityHandler.h"
#include "Enemy.h"

HypnoticStareEffect::HypnoticStareEffect(unsigned int _affectedUnit, unsigned int _casterId, float _duration)
{
	m_affectedUnit = _affectedUnit;
	m_timer = _duration;

	this->m_obb = NULL;
	this->m_bs = new BoundingSphere();
	m_visible = false;
	m_type = OtherType;
	
	ServerEntity* affectedUnit = EntityHandler::getServerEntity(m_affectedUnit);
	if(affectedUnit)
	{
		((Enemy*)affectedUnit)->setTargetType(UnitEntity::EnemyType);
		this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(
			Skill::HYPNOTIC_STARE, _casterId, affectedUnit->getId(), FLOAT3(_duration, 0, 0))); // Set position.x to the duration so we use it as that instead mohahhaha >:D
	}
	else
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
}

HypnoticStareEffect::~HypnoticStareEffect()
{
	
}

void HypnoticStareEffect::update(float _dt)
{
	ServerEntity* affectedUnit = EntityHandler::getServerEntity(m_affectedUnit);

	if(affectedUnit)
	{
		m_timer = max(m_timer-_dt, 0.0f);
		if(m_timer == 0.0f)
		{
			((Enemy*)affectedUnit)->setTargetType(UnitEntity::HeroType);
		}
	}
	else
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
}