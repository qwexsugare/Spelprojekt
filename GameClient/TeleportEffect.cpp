#include "TeleportEffect.h"
#include "EntityHandler.h"

const float TeleportEffect::BOOST = 0.5f;

TeleportEffect::TeleportEffect(unsigned int _casterId, FLOAT3 _newPosition)
{
	m_casterId = _casterId;
	m_obb = NULL;
	m_bs = new BoundingSphere();
	m_visible = false;
	this->m_castingDelay = 0.25f;
	m_currentDuration = 1.0f;
	m_type = OtherType;
	this->m_newPosition = _newPosition;
	this->m_messageQueue->pushOutgoingMessage(new CreateActionPositionMessage(Skill::TELEPORT, _casterId, this->m_newPosition));
}

TeleportEffect::~TeleportEffect()
{

}

void TeleportEffect::update(float _dt)
{
	if(this->m_castingDelay > 0.0f)
	{
		this->m_castingDelay -= _dt;

		if(this->m_castingDelay <= 0.0f)
		{
			ServerEntity* se = EntityHandler::getServerEntity(m_casterId);

			if(se != NULL)
			{
				((Hero*)se)->setPosition(this->m_newPosition);
				((Hero*)se)->setNextPosition(((Hero*)se)->getPosition());
				((Hero*)se)->getMessageQueue()->pushOutgoingMessage(((Hero*)se)->getUpdateEntityMessage());

				this->m_currentDuration = ((UnitEntity*)se)->getAgility();
				((UnitEntity*)se)->alterMovementSpeed(BOOST);
			}
		}
	}
	else
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
}