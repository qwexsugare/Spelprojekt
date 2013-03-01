#include "TurretLifetime.h"

TurretLifetime::TurretLifetime() : Skill(Skill::TURRET_LIFE, 0)
{

}

TurretLifetime::~TurretLifetime()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		((UnitEntity*)e)->alterTurretDuration(-1);
	}
}

bool TurretLifetime::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(_senderId);

	if(e != NULL)
	{
		((UnitEntity*)e)->alterTurretDuration(1);
	}

	return true;
}

void TurretLifetime::updateSpecificSkill(float _dt)
{

}