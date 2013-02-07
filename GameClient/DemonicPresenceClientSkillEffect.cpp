#include "DemonicPresenceClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"

DemonicPresenceClientSkillEffect::DemonicPresenceClientSkillEffect(unsigned int _masterId)
{
	m_masterId = _masterId;
	FLOAT3 pos = ClientEntityHandler::getEntity(_masterId)->m_model->getPosition();
	pos.y = 0.01f;
	m_model = g_graphicsEngine->createModel("Pentagram", pos);
}

DemonicPresenceClientSkillEffect::~DemonicPresenceClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_model);
}

void DemonicPresenceClientSkillEffect::update(float _dt)
{
	FLOAT3 pos = ClientEntityHandler::getEntity(m_masterId)->m_model->getPosition();
	pos.y = 0.01f;
	m_model->setPosition(pos);
}

bool DemonicPresenceClientSkillEffect::getActive()
{
	return true;
}