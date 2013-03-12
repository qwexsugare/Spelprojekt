#include "Greed.h"

Greed::Greed() : Skill(Skill::GREED, 0.0f)
{

}

Greed::~Greed()
{
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setGreed(ue->getGreed() - 0.2f);
	}	
}

bool Greed::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(this->m_senderId);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setGreed(ue->getGreed() + 0.2f);
	}

	return true;
}

void Greed::updateSpecificSkill(float dt)
{

}

int Greed::getCost()
{
	return Greed::COST;
}