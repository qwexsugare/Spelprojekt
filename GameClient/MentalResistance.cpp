#include "MentalResistance.h"

MentalResistance::MentalResistance() : Skill(Skill::MENTAL_RESISTANCE, 0.0f)
{

}

MentalResistance::~MentalResistance()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setMentalResistance(ue->getMentalResistance() + 0.15f);
	}	
}

bool MentalResistance::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setMentalResistance(ue->getMentalResistance() - 0.15f);
	}	

	return true;
}

void MentalResistance::updateSpecificSkill(float dt)
{

}