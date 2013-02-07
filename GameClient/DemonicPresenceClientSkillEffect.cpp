#include "DemonicPresenceClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"

DemonicPresenceClientSkillEffect::DemonicPresenceClientSkillEffect(unsigned int _masterId)
{
	m_masterId = _masterId;
	m_model = g_graphicsEngine->createModel("Pentagram", ClientEntityHandler::getEntity(_masterId)->m_model->getPosition());
}

DemonicPresenceClientSkillEffect::~DemonicPresenceClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_model);
}

void DemonicPresenceClientSkillEffect::update(float _dt)
{
	m_model->setPosition(ClientEntityHandler::getEntity(m_masterId)->m_model->getPosition());
}

bool DemonicPresenceClientSkillEffect::getActive()
{
	return true;
}