#include "PhysicalResistance.h"

PhysicalResistance::PhysicalResistance() : Skill(Skill::PHYSICAL_RESISTANCE, 0.0f)
{

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

bool PhysicalResistance::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setPhysicalResistance(ue->getPhysicalResistance() - 0.15f);
	}	

	return true;
}

void PhysicalResistance::updateSpecificSkill(float dt)
{

}