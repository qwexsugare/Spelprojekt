#include "EnigmaticPresenceClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"

EnigmaticPresenceClientSkillEffect::EnigmaticPresenceClientSkillEffect(unsigned int _masterId)
{
	m_masterId = _masterId;
	FLOAT3 pos = ClientEntityHandler::getEntity(_masterId)->m_model->getPosition();
	pos.y = 0.01f;
	m_model = g_graphicsEngine->createModel("Pentagram", pos);
	m_model->neutralize();
	m_model->setAlpha(0.75f);
	m_model->setShadow(false);
}

EnigmaticPresenceClientSkillEffect::~EnigmaticPresenceClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_model);
}

void EnigmaticPresenceClientSkillEffect::update(float _dt)
{
	FLOAT3 pos = ClientEntityHandler::getEntity(m_masterId)->m_model->getPosition();
	pos.y = 0.01f;
	m_model->setPosition(pos);
	m_model->rotate(_dt/3.0f, 0.0f, 0.0f);
}

bool EnigmaticPresenceClientSkillEffect::getActive()
{
	return true;
}