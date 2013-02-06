#include "PoisonStrike.h"

PoisonStrike::PoisonStrike()
{

}

PoisonStrike::~PoisonStrike()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setPoisonChance(ue->getPoisonChance() - 25);
	}
}

bool PoisonStrike::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setPoisonChance(ue->getPoisonChance() + 25);
	}	

	return true;
}

void PoisonStrike::updateSpecificSkill(float dt)
{

}