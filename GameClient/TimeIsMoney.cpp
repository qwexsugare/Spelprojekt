#include "TimeIsMoney.h"

const float TimeIsMoney::COOLDOWN = 30.0f;

TimeIsMoney::TimeIsMoney() : Skill(Skill::TIME_IS_MONEY, TimeIsMoney::COOLDOWN)
{
	this->m_active = false;
}

TimeIsMoney::~TimeIsMoney()
{

}

void TimeIsMoney::updateSpecificSkill(float _dt)
{

}

bool TimeIsMoney::activate(unsigned int _senderId)
{
	if(this->getCurrentCooldown() == 0 && this->m_active == false)
	{
		this->m_active = true;
		ServerEntity* e = EntityHandler::getServerEntity(_senderId);
		if(e)
		{
			e->getMessageQueue()->pushOutgoingMessage(new CreateActionMessage(Skill::TIME_IS_MONEY, _senderId, e->getPosition()));
			this->setCooldown(TimeIsMoney::COOLDOWN - ((UnitEntity*)e)->getTurretConstruction());
		}
		this->resetCooldown();
		return true;
	}
	else
	{
		return false;
	}
}

bool TimeIsMoney::getActive()
{
	return this->m_active;
}

void TimeIsMoney::setActive(bool _active)
{
	this->m_active = _active;
}