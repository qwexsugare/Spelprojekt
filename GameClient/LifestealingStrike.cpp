#include "LifestealingStrike.h"

LifestealingStrike::LifestealingStrike()
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