#include "CourageHonorValor.h"
#include "EntityHandler.h"
#include "CourageHonorValorEffect.h"

CourageHonorValor::CourageHonorValor() : Skill(Skill::COURAGE_HONOR_VALOR, 0)
{
	
}

CourageHonorValor::~CourageHonorValor()
{

}

bool CourageHonorValor::activate(unsigned int _senderId)
{
	ServerEntity* caster = EntityHandler::getServerEntity(_senderId);

	if(caster)
	{
		EntityHandler::addEntity(new CourageHonorValorEffect(_senderId));
	}

	return true;
}

void CourageHonorValor::updateSpecificSkill(float _dt)
{

}