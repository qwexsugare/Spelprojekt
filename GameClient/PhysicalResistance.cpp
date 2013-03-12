#include "PhysicalResistance.h"

PhysicalResistance::PhysicalResistance(unsigned int _senderId) : Skill(Skill::PHYSICAL_RESISTANCE, 0.0f)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setPhysicalResistance(ue->getPhysicalResistance() - 0.15f);
	}	
}

PhysicalResistance::~PhysicalResistance()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setPhysicalResistance(ue->getPhysicalResistance() + 0.15f);
	}	
}

void PhysicalResistance::updateSpecificSkill(float dt)
{

}

int PhysicalResistance::getCost()
{
	return PhysicalResistance::COST;
}