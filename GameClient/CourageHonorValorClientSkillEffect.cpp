#include "CourageHonorValorClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "Hero.h"
#include "SpeechManager.h"

CourageHonorValorClientSkillEffect::CourageHonorValorClientSkillEffect(unsigned int _masterId, unsigned int _redKnightId)
{
	m_masterId = _masterId;
	Entity *e = ClientEntityHandler::getEntity(_masterId);
	if(e != NULL)
	{
		FLOAT3 pos = e->m_model->getPosition();
		pos.y = 0.01f;
		m_model = g_graphicsEngine->createModel("Pentagram", pos);
		m_model->setAlpha(0.75f);
		m_model->setShadow(false);

		int sound = createSoundHandle("skills/RedKnight_COURAGE.wav", false, true, pos);
		SpeechManager::speak(_redKnightId, sound);
		deactivateSound(sound);
	}
	m_soundTimer = 3.0f;
	m_hasSpoken = false;
}

CourageHonorValorClientSkillEffect::~CourageHonorValorClientSkillEffect()
{
	Entity *e = ClientEntityHandler::getEntity(m_masterId);
	if(e)
		g_graphicsEngine->removeModel(m_model);
}

void CourageHonorValorClientSkillEffect::update(float _dt)
{
	Entity *e = ClientEntityHandler::getEntity(m_masterId);

	if(e != NULL)
	{
		FLOAT3 pos = e->m_model->getPosition();
		pos.y = 0.01f;
		m_model->setPosition(pos);
		m_model->rotate(_dt/3.0f, 0.0f, 0.0f);

		if(e->m_subtype != Hero::RED_KNIGHT && !m_hasSpoken)
		{
			m_soundTimer = max(m_soundTimer-_dt, 0.0f);
			if(m_soundTimer == 0.0f)
			{
				int sound;
				switch(e->m_subtype)
				{
				case Hero::ENGINEER:
					sound = createSoundHandle("skills/Engineer_COURAGE_REACTION.wav", false, true, pos);
					break;
				case Hero::DOCTOR:
					sound = createSoundHandle("skills/Doctor_COURAGE_REACTION.wav", false, true, pos);
					break;
				case Hero::THE_MENTALIST:
					sound = createSoundHandle("skills/Mentalist_COURAGE_REACTION.wav", false, true, pos);
					break;
				case Hero::OFFICER:
					sound = createSoundHandle("skills/Officer_COURAGE_REACTION.wav", false, true, pos);
					break;
				}
				SpeechManager::speak(m_masterId, sound);
				deactivateSound(sound);

				m_hasSpoken = true;
			}
		}
	}
}

bool CourageHonorValorClientSkillEffect::getActive()
{
	return true;
}