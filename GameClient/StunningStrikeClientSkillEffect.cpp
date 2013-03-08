#include "StunningStrikeClientSkillEffect.h"
#include "SoundWrapper.h"
#include "StunningStrikeEffect.h"
#include "Graphics.h"

StunningStrikeClientSkillEffect::StunningStrikeClientSkillEffect(unsigned int _masterId, FLOAT3 _position)
{
	m_position = _position;
	m_lifetime = 0.0f;

	Entity *e = ClientEntityHandler::getEntity(_masterId);

	if(e != NULL)
	{
		if(e->m_weapon == ModelIdHolder::AOE)
		{
			e->m_model->getAnimation()->Play("StunningStrike2Hand");
		}
		else
		{
			e->m_model->getAnimation()->Play("StunningStrike");
		}
	}

	// Play sound
	int sound = createSoundHandle("skills/StunningStrike.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);
}

StunningStrikeClientSkillEffect::~StunningStrikeClientSkillEffect()
{

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