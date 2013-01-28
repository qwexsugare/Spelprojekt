#include "PhysicalResistance.h"

PhysicalResistance::PhysicalResistance()
{

}

PhysicalResistance::~PhysicalResistance()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setPhysicalResistance(ue->getPhysicalResistance() + 15.0f);
	}	
}

bool PhysicalResistance::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setPhysicalResistance(ue->getPhysicalResistance() - 15.0f);
	}	

	return true;
}

void PhysicalResistance::updateSpecificSkill(float dt)
{

}