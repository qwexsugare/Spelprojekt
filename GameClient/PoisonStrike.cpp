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
		ue->setDeadlyStrikeChance(ue->getDeadlyStrikeChance() + 1.0f);
	}
}

void PoisonStrike::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setDeadlyStrikeChance(ue->getPoisonChance() + 1.0f);
	}	
}