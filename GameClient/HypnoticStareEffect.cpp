#include "HypnoticStareEffect.h"
#include "EntityHandler.h"
#include "Enemy.h"
#include "EnigmaticPresenceEffect.h"

HypnoticStareEffect::HypnoticStareEffect(unsigned int _affectedUnit, unsigned int _casterId, int _wits)
{
	m_affectedUnit = _affectedUnit;
	this->m_obb = NULL;
	this->m_bs = new BoundingSphere();
	m_visible = false;
	m_type = OtherType;

	m_timer = _wits*2;
	m_mentalDamage = _wits;
	m_movementSpeed = EnigmaticPresenceEffect::MOVEMENT_SPEED_FACTOR*_wits;
	
	ServerEntity* affectedUnit = EntityHandler::getServerEntity(m_affectedUnit);
	if(affectedUnit)
	{
		((UnitEntity*)affectedUnit)->alterMentalDamage(m_mentalDamage);
		((UnitEntity*)affectedUnit)->alterMovementSpeed(m_movementSpeed);
		((Enemy*)affectedUnit)->setTargetType(UnitEntity::EnemyType);
		this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(
			Skill::HYPNOTIC_STARE, _casterId, affectedUnit->getId(), FLOAT3(m_timer, 0, 0))); // Set position.x to the duration so we use it as that instead mohahhaha >:D
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
			((UnitEntity*)affectedUnit)->alterMentalDamage(-m_mentalDamage);
			((UnitEntity*)affectedUnit)->alterMovementSpeed(-m_movementSpeed);
			((Enemy*)affectedUnit)->setTargetType(UnitEntity::HeroType);
		}
	}
	else
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
}