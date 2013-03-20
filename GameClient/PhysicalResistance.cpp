#include "PhysicalResistance.h"

PhysicalResistance::PhysicalResistance(unsigned int _senderId) : Skill(Skill::PHYSICAL_RESISTANCE, 0.0f)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->alterPhysicalResistance(-0.05f);
		ue->alterPhysicalResistanceUpgrades(1);
	}
}

PhysicalResistance::~PhysicalResistance()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->alterPhysicalResistance(0.05f);
		ue->alterPhysicalResistanceUpgrades(-1);
	}	
}

void PhysicalResistance::updateSpecificSkill(float dt)
{

}

int PhysicalResistance::getCost()
{
	return PhysicalResistance::COST;
}