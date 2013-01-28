#include "CloudOfDarknessClientSkillEffect.h"
#include "SoundWrapper.h"
#include "CloudOfDarknessEffect.h"

CloudOfDarknessClientSkillEffect::CloudOfDarknessClientSkillEffect(FLOAT3 _position)
{
	m_position = _position;

	m_sound = createSoundHandle("orb.wav", false);
	playSound(m_sound);
}

CloudOfDarknessClientSkillEffect::~CloudOfDarknessClientSkillEffect()
{
	deactivateSound(m_sound);
}

void CloudOfDarknessClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;
}

bool CloudOfDarknessClientSkillEffect::getActive()
{
	if(m_lifetime >= CloudOfDarknessEffect::LIFETIME)
		return false;
	else
		return true;
}