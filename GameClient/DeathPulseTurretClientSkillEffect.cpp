#include "DeathPulseTurretClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"

DeathPulseTurretClientSkillEffect::DeathPulseTurretClientSkillEffect(unsigned int _masterId)
{
	m_masterId = _masterId;
	FLOAT3 pos = ClientEntityHandler::getEntity(_masterId)->m_model->getPosition();
	m_model = g_graphicsEngine->createModel("Bench", pos);
	m_model->setAlpha(0.999f);
	m_sound = createSoundHandle("bow.wav", false, true, pos);
	playSound(m_sound);
	m_timer = 0.0f;
	m_active = true;
}

DeathPulseTurretClientSkillEffect::~DeathPulseTurretClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_model);
	deactivateSound(m_sound);
}

void DeathPulseTurretClientSkillEffect::update(float _dt)
{
	if(m_active)
	{
		m_timer += _dt;
		if(m_timer > DeathPulseTurretClientSkillEffect::DURATION)
			m_active = false;
		else
		{
			Entity* master = ClientEntityHandler::getEntity(m_masterId);
			if(master)
			{
				FLOAT3 pos = ClientEntityHandler::getEntity(m_masterId)->m_model->getPosition();
				m_model->setPosition(pos);
			}
			else
				m_active = false;
		}
	}
}

bool DeathPulseTurretClientSkillEffect::getActive()
{
	return m_active;
}