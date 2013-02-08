#include "SimonsEvilClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"

SimonsEvilClientSkillEffect::SimonsEvilClientSkillEffect(unsigned int _masterId)
{
	m_masterId = _masterId;
	FLOAT3 pos = ClientEntityHandler::getEntity(_masterId)->m_model->getPosition();
	m_model = g_graphicsEngine->createModel("redKnightPassiveAura", pos);
	m_sound = createSoundHandle("bow.wav", false);
	playSound(m_sound);
}

SimonsEvilClientSkillEffect::~SimonsEvilClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_model);
	deactivateSound(m_sound);
}

void SimonsEvilClientSkillEffect::update(float _dt)
{
	FLOAT3 pos = ClientEntityHandler::getEntity(m_masterId)->m_model->getPosition();
	m_model->setPosition(pos);
}

bool SimonsEvilClientSkillEffect::getActive()
{
	return true;
}