#include "HealingTouchClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"

HealingTouchClientSkillEffect::HealingTouchClientSkillEffect(FLOAT3 _position)
{
	m_position = _position;
	//m_graphicalEffect = g_graphicsEngine->createModel("Char1_5", _position);
	m_lifetime = 0.0f;
	m_sound = createSoundHandle("click_button.wav", false, true, _position);
	playSound(m_sound);
}

HealingTouchClientSkillEffect::~HealingTouchClientSkillEffect()
{
	//g_graphicsEngine->removeModel(m_graphicalEffect);
	deactivateSound(m_sound);
}

void HealingTouchClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;
}

bool HealingTouchClientSkillEffect::getActive()
{
	return false;
}