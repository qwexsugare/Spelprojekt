#include "MentalResistance.h"

MentalResistance::MentalResistance()
{

}

MentalResistance::~MentalResistance()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setMentalResistance(ue->getMentalResistance() + 15.0f);
	}	
}

bool MentalResistance::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setMentalResistance(ue->getMentalResistance() - 15.0f);
	}	

	return true;
}

void MentalResistance::updateSpecificSkill(float dt)
{

}