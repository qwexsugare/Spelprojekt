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
		ue->setAttackSpeed(ue->getAttackSpeed() + 0.15f);
	}
}

bool Aim::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setAttackSpeed(ue->getAttackSpeed() - 0.15f);
	}

	return true;
}