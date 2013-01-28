#include "DeadlyStrike.h"

DeadlyStrike::DeadlyStrike()
{

}

DeadlyStrike::~DeadlyStrike()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setDeadlyStrikeChance(ue->getDeadlyStrikeChance() - 1);
	}
}

void DeadlyStrike::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setDeadlyStrikeChance(ue->getDeadlyStrikeChance() + 1);
	}
}