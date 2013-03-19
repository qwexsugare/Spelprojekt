#include "HypnoticStare.h"
#include "HypnoticStareEffect.h"
#include "EntityHandler.h"
#include "Hero.h"

const float HypnoticStare::COOLDOWN = 30.0f;

HypnoticStare::HypnoticStare() : Skill(Skill::HYPNOTIC_STARE, COOLDOWN)
{
	
}

HypnoticStare::~HypnoticStare()
{

}

bool HypnoticStare::activate(unsigned int _targetId, unsigned int _senderId)
{
	ServerEntity* caster = EntityHandler::getServerEntity(_senderId);
	ServerEntity* target = EntityHandler::getServerEntity(_targetId);

	if(caster && target)
	{
		if(this->getCurrentCooldown() == 0 && (caster->getPosition() - target->getPosition()).length() <= RANGE)
		{
			EntityHandler::addEntity(new HypnoticStareEffect(_targetId, _senderId, ((Hero*)caster)->getWits()));
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