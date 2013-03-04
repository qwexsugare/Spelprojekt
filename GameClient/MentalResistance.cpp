#include "MentalResistance.h"

MentalResistance::MentalResistance(unsigned int _senderId) : Skill(Skill::MENTAL_RESISTANCE, 0.0f)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setMentalResistance(ue->getMentalResistance() - 0.15f);
	}	
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

void MentalResistance::updateSpecificSkill(float dt)
{

}