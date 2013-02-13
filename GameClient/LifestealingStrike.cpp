#include "LifestealingStrike.h"

LifestealingStrike::LifestealingStrike() : Skill(Skill::LIFESTEALING_STRIKE, 0.0f)
{

}

LifestealingStrike::~LifestealingStrike()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setLifeStealChance(ue->getLifeStealChance() - 15.0f);
	}	
}

bool LifestealingStrike::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setLifeStealChance(ue->getLifeStealChance() + 15.0f);
	}	

	return true;
}

void LifestealingStrike::updateSpecificSkill(float dt)
{

}