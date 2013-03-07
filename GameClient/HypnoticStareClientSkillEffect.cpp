#include "HypnoticStareClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "HypnoticStareEffect.h"

HypnoticStareClientSkillEffect::HypnoticStareClientSkillEffect(unsigned int _masterId, unsigned int _casterId, float _duration)
{
	m_casterId = _casterId;
	m_masterId = _masterId;
	m_timer = _duration;

	Entity *e = ClientEntityHandler::getEntity(_masterId);
	if(e != NULL)
	{
		this->m_oldTexture = e->m_model->getTextureIndex();
		this->m_oldGlow = e->m_model->getGlowIndex();
		e->m_model->setGlowIndex("glowIntensity");
		e->m_model->setTextureIndex("color4");
		m_active = true;
	}
	else
		m_active = false;

	// Play sound
	Entity* caster = ClientEntityHandler::getEntity(_casterId);
	int sound = createSoundHandle("skills/hypnotic_stare_start.wav", false, true, caster->m_startPos);
	playSound(sound);
	deactivateSound(sound);
}

HypnoticStareClientSkillEffect::~HypnoticStareClientSkillEffect()
{
	Entity *e = ClientEntityHandler::getEntity(m_masterId);
	if(e)
	{
		e->m_model->setTextureIndex(this->m_oldTexture);
		e->m_model->setGlowIndex(this->m_oldGlow);
	}
}

void HypnoticStareClientSkillEffect::update(float _dt)
{
	if(m_active)
	{
		m_timer = max(m_timer-_dt, 0.0f);
		if(m_timer == 0.0f)
		{
			// Play sound
			Entity* caster = ClientEntityHandler::getEntity(m_casterId);
			int sound = createSoundHandle("skills/hypnotic_stare_end.wav", false, true, caster->m_startPos);
			playSound(sound);
			deactivateSound(sound);

			m_active = false;
		}
	}
}

bool HypnoticStareClientSkillEffect::getActive()
{
	return m_active;
}