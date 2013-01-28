#include "Greed.h"

Greed::Greed()
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