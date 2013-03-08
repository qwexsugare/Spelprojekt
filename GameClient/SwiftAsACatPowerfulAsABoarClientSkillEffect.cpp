#include "SwiftAsACatPowerfulAsABoarClientSkillEffect.h"
#include "SoundWrapper.h"
#include "MyAlgorithms.h"

SwiftAsACatPowerfulAsABoarClientSkillEffect::SwiftAsACatPowerfulAsABoarClientSkillEffect(unsigned int _masterId)
{
	Entity *e = ClientEntityHandler::getEntity(_masterId);

	if(e != NULL)
	{
		if(e->m_weapon == ModelIdHolder::WEAPON_TYPE::AOE)
		{
			e->m_model->getAnimation()->Play("SwiftAsButterfly2Hand");
		}
		else
		{
			e->m_model->getAnimation()->Play("SwiftAsButterfly_1H");
		}

		int sound;
		switch(random(0, 1))
		{
		case 0:
			sound = createSoundHandle("skills/saacpaab0", false, true, e->m_startPos);
			break;
		case 1:
			sound = createSoundHandle("skills/saacpaab1", false, true, e->m_startPos);
			break;
		}
		playSound(sound);
		deactivateSound(sound);
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