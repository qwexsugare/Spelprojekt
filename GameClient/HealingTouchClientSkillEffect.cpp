#include "HealingTouchClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"

HealingTouchClientSkillEffect::HealingTouchClientSkillEffect(FLOAT3 _position)
{
	m_position = _position;
	m_lifetime = 0.0f;

	int sound = createSoundHandle("skills/healingTouch.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);
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