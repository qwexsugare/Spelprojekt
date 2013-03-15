#include "TurretDamage.h"

TurretDamage::TurretDamage() : Skill(Skill::TURRET_DAMAGE, 0)
{

}

TurretDamage::~TurretDamage()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		((UnitEntity*)e)->alterTurretDamageUpgrade(-1);
	}
}

bool TurretDamage::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(_senderId);

	if(e != NULL)
	{
		((UnitEntity*)e)->alterTurretDamageUpgrade(1);
	}

	return true;
}

void TurretDamage::updateSpecificSkill(float _dt)
{

}

int TurretDamage::getCost()
{
	return TurretDamage::COST;
}