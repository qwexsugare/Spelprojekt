#include "Arrow.h"
#include "EntityHandler.h"
#include "Graphics.h"

Arrow::Arrow()
{

}

Arrow::Arrow(float _distance, unsigned int _target, unsigned int _caster)
{
	m_target = _target;
	m_caster = _caster;
	m_timeToImpact = _distance/10.0f;
	m_obb = new BoundingOrientedBox();
}

Arrow::~Arrow()
{

}

void Arrow::updateSpecificUnitEntity(float _dt)
{
	ServerEntity* target = EntityHandler::getServerEntity(m_target);
	if(target)
	{
		ServerEntity* caster = EntityHandler::getServerEntity(m_caster);
		if(caster)
		{
			m_timeToImpact = max(m_timeToImpact-_dt, 0.0f);

			if(m_timeToImpact == 0.0f)
			{
				caster->dealDamage(target, ((UnitEntity*)caster)->getPhysicalDamage(), ((UnitEntity*)caster)->getMentalDamage());
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