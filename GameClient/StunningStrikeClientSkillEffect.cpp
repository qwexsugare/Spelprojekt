#include "StunningStrikeClientSkillEffect.h"
#include "SoundWrapper.h"
#include "StunningStrikeEffect.h"
#include "Graphics.h"

StunningStrikeClientSkillEffect::StunningStrikeClientSkillEffect(FLOAT3 _position)
{
	m_position = _position;
	m_graphicalEffect = g_graphicsEngine->createPointLight(_position, FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(0.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), StunningStrikeEffect::AOE);
	m_lifetime = 0.0f;
	m_sound = createSoundHandle("orb.wav", false);
	playSound(m_sound);
}

StunningStrikeClientSkillEffect::~StunningStrikeClientSkillEffect()
{
	g_graphicsEngine->removePointLight(m_graphicalEffect);
	stopSound(m_sound);
	deactivateSound(m_sound);
}

void StunningStrikeClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;
}

bool StunningStrikeClientSkillEffect::getActive()
{
	if(m_lifetime >= StunningStrikeEffect::LIFETIME)
		return false;
	else
		return true;
}