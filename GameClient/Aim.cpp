#include "Aim.h"

Aim::Aim(unsigned int _senderId) : Skill(Skill::AIM, 0.0f)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->alterAttackSpeed(-0.15f);
	}
}

Aim::~Aim()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->alterAttackSpeed(0.15f);
	}
}

void Aim::updateSpecificSkill(float dt)
{

}