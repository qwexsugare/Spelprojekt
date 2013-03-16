#include "MentalResistance.h"

MentalResistance::MentalResistance(unsigned int _senderId) : Skill(Skill::MENTAL_RESISTANCE, 0.0f)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->alterMentalResistance(-0.05f);
		ue->alterMentalResistanceUpgrades(1);
	}	
}

MentalResistance::~MentalResistance()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->alterMentalResistance(0.05f);
		ue->alterMentalResistanceUpgrades(-1);
	}	
}

void MentalResistance::updateSpecificSkill(float dt)
{

}

int MentalResistance::getCost()
{
	return MentalResistance::COST;
}