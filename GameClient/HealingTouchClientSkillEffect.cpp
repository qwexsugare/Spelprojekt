#include "HealingTouchClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"

HealingTouchClientSkillEffect::HealingTouchClientSkillEffect(FLOAT3 _position, unsigned int casterId, unsigned int _targetId)
{
	m_position = _position;
	m_lifetime = 0.0f;
	
	int sound = createSoundHandle("skills/healingTouch.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);

	Entity *e = ClientEntityHandler::getEntity(casterId);
	if(e != NULL)
	{
		e->m_model->getAnimation()->Play("Spell");
	}

	// ANDERS DO TARGET IT WITH ABOVE STUFF
}

HealingTouchClientSkillEffect::~HealingTouchClientSkillEffect()
{

}

void HealingTouchClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;
}

bool HealingTouchClientSkillEffect::getActive()
{
	return false;
}