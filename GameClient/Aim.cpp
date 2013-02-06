#include "Aim.h"

Aim::Aim()
{

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

bool Aim::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->alterAttackSpeed(-0.15f);
	}

	return true;
}

void Aim::updateSpecificSkill(float dt)
{

}