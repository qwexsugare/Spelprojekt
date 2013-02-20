#include "HypnoticStare.h"
#include "HypnoticStareEffect.h"
#include "EntityHandler.h"
#include "Hero.h"

const float HypnoticStare::TIME_FACTOR = 0.4f; //2.0f;
const float HypnoticStare::COOLDOWN = 1.0f; //60.0f;

HypnoticStare::HypnoticStare() : Skill(Skill::HYPNOTIC_STARE, COOLDOWN)
{
	
}

HypnoticStare::~HypnoticStare()
{

}

bool HypnoticStare::activate(unsigned int _senderId, unsigned int _targetId)
{
	ServerEntity* caster = EntityHandler::getServerEntity(_senderId);
	ServerEntity* target = EntityHandler::getServerEntity(_targetId);

	if(caster && target)
	{
		if(this->getCurrentCooldown() == 0 && (caster->getPosition() - target->getPosition()).length() <= RANGE)
		{
			EntityHandler::addEntity(new HypnoticStareEffect(target->getId(), ((Hero*)caster)->getWits()*TIME_FACTOR));
			this->resetCooldown();
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

void HypnoticStare::updateSpecificSkill(float _dt)
{

}