#include "ChainStrike.h"
#include "EntityHandler.h"
#include "ChainStrikeEffect.h"

ChainStrike::ChainStrike() : Skill(0, 1.0f)
{

}

ChainStrike::~ChainStrike()
{

}

void ChainStrike::activate(unsigned int _targetId)
{
	if(this->getCooldown() == 0)
	{
		EntityHandler::addEntity(new ChainStrikeEffect());
	}
}

void ChainStrike::updateSpecificSkill(float _dt)
{

}