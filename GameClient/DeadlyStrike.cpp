#include "DeadlyStrike.h"

DeadlyStrike::DeadlyStrike() : Skill(Skill::DEADLY_STRIKE, 0.0f)
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

bool DeadlyStrike::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setDeadlyStrikeChance(ue->getDeadlyStrikeChance() + 1);
	}

	return true;
}

void DeadlyStrike::updateSpecificSkill(float dt)
{

}