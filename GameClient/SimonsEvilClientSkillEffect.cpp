#include "SimonsEvilClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "SimonsEvilEffect.h"

SimonsEvilClientSkillEffect::SimonsEvilClientSkillEffect(unsigned int _masterId)
{
	m_masterId = _masterId;
	FLOAT3 pos = ClientEntityHandler::getEntity(_masterId)->m_model->getPosition();
	m_model = g_graphicsEngine->createModel("redKnightPassiveAura", pos);
	m_model->setAlpha(0.999f);
	m_sound = createSoundHandle("bow.wav", false);
	playSound(m_sound);
	m_timer = 0.0f;
}

SimonsEvilClientSkillEffect::~SimonsEvilClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_model);
	deactivateSound(m_sound);
}

void SimonsEvilClientSkillEffect::update(float _dt)
{
	m_timer += _dt;

	FLOAT3 pos = ClientEntityHandler::getEntity(m_masterId)->m_model->getPosition();
	m_model->setPosition(pos);
}

bool SimonsEvilClientSkillEffect::getActive()
{
	if(m_timer >= SimonsEvilEffect::LIFETIME)
		return false;
	else
		return true;
}