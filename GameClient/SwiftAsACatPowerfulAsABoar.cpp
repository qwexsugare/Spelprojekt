#include "SwiftAsACatPowerfulAsABoar.h"
#include "EntityHandler.h"

const float SwiftAsACatPowerfulAsABoar::COOLDOWN = 45.0f;

SwiftAsACatPowerfulAsABoar::SwiftAsACatPowerfulAsABoar() : Skill(Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR, COOLDOWN)
{

}

SwiftAsACatPowerfulAsABoar::~SwiftAsACatPowerfulAsABoar()
{

}

bool SwiftAsACatPowerfulAsABoar::activate(unsigned int _senderId)
{
	if(this->getCurrentCooldown() == 0)
	{
		ServerEntity *e = EntityHandler::getServerEntity(_senderId);

		if(e)
		{
			UnitEntity* ue = (UnitEntity*)e;
			ue->setSwiftAsACatPowerfulAsABear(true);
			this->resetCooldown();;
			e->getMessageQueue()->pushOutgoingMessage(new CreateActionMessage(Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR, e->getId(), e->getPosition()));
			
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

void SwiftAsACatPowerfulAsABoar::updateSpecificSkill(float dt)
{

}