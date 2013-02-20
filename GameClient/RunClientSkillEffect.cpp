#include "RunClientSkillEffect.h"

RunClientSkillEffect::RunClientSkillEffect(unsigned int masterId)
{
	Entity* master = ClientEntityHandler::getEntity(masterId);

	if(master != NULL)
	{
		master->m_model->getAnimation()->PlayLoop("run");
	}
}

RunClientSkillEffect::~RunClientSkillEffect()
{

}

void RunClientSkillEffect::update(float dt)
{

}

bool RunClientSkillEffect::getActive()
{
	return false;
}