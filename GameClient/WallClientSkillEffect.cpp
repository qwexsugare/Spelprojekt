#include "WallClientSkillEffect.h"

WallClientSkillEffect::WallClientSkillEffect(unsigned int _masterId, FLOAT3 _position)
{
	Entity *master = ClientEntityHandler::getEntity(_masterId);

	if(master != NULL)
	{
		master->m_model->getAnimation()->Play("Spell");
	}
}

WallClientSkillEffect::~WallClientSkillEffect()
{

}

void WallClientSkillEffect::update(float _dt)
{

}

bool WallClientSkillEffect::getActive()
{
	return false;
}