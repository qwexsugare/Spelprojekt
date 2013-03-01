#include "SwiftAsACatPowerfulAsABoarClientSkillEffect.h"

SwiftAsACatPowerfulAsABoarClientSkillEffect::SwiftAsACatPowerfulAsABoarClientSkillEffect(unsigned int _masterId)
{
	Entity *e = ClientEntityHandler::getEntity(_masterId);

	if(e != NULL)
	{
		e->m_model->getAnimation()->Play("SwiftAsButterfly");
	}
}

SwiftAsACatPowerfulAsABoarClientSkillEffect::~SwiftAsACatPowerfulAsABoarClientSkillEffect()
{

}

void SwiftAsACatPowerfulAsABoarClientSkillEffect::update(float _dt)
{

}

bool SwiftAsACatPowerfulAsABoarClientSkillEffect::getActive()
{
	return false;
}