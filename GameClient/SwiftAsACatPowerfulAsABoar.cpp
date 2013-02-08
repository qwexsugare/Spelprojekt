#include "SwiftAsACatPowerfulAsABoar.h"
#include "EntityHandler.h"

const float SwiftAsACatPowerfulAsABoar::COOLDOWN = 120.0f;

SwiftAsACatPowerfulAsABoar::SwiftAsACatPowerfulAsABoar() : Skill(Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR, COOLDOWN)
{

}

SwiftAsACatPowerfulAsABoar::~SwiftAsACatPowerfulAsABoar()
{

}

bool SwiftAsACatPowerfulAsABoar::activate(unsigned int _senderId)
{
	m_master = _senderId;
	ServerEntity *e = EntityHandler::getServerEntity(m_master);

	if(e != NULL)
	{
		UnitEntity* ue = (UnitEntity*)e;
		ue->setSwiftAsACatPowerfulAsABear(true);
	}

	return true;
}

void SwiftAsACatPowerfulAsABoar::updateSpecificSkill(float dt)
{

}