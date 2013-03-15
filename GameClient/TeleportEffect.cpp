#include "TeleportEffect.h"
#include "EntityHandler.h"

const float TeleportEffect::BOOST = 0.5f;

TeleportEffect::TeleportEffect(unsigned int _casterId)
{
	m_casterId = _casterId;
	m_obb = NULL;
	m_bs = new BoundingSphere();
	m_visible = false;
	m_currentDuration = 1.0f;
	m_type = OtherType;

	ServerEntity* se = EntityHandler::getServerEntity(m_casterId);
	if(se)
	{
		this->m_currentDuration = ((UnitEntity*)se)->getAgility();
		((UnitEntity*)se)->alterMovementSpeed(BOOST);
		this->m_messageQueue->pushOutgoingMessage(new CreateActionPositionMessage(Skill::TELEPORT, _casterId, se->getPosition()));
	}
}

TeleportEffect::~TeleportEffect()
{

}

void TeleportEffect::update(float _dt)
{
	m_currentDuration -= _dt;

	if(m_currentDuration <= 0.0f)
	{
		ServerEntity* se = EntityHandler::getServerEntity(m_casterId);
		if(se)
		{
			UnitEntity* caster = (UnitEntity*)se;
			caster->alterMovementSpeed(-BOOST);
		}
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}