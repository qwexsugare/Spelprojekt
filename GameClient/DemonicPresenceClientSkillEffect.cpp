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
	m_model->setAlpha(0.75f);
	m_sound = createSoundHandle("collision.wav", false, true, pos);
	playSound(m_sound);
	m_model->getAnimation()->PlayLoop("attack");
}

DemonicPresenceClientSkillEffect::~DemonicPresenceClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_model);
	deactivateSound(m_sound);
}

void DemonicPresenceClientSkillEffect::update(float _dt)
{
	FLOAT3 pos = ClientEntityHandler::getEntity(m_masterId)->m_model->getPosition();
	pos.y = 0.01f;
	m_model->setPosition(pos);
	m_model->rotate(_dt/3.0f, 0.0f, 0.0f);
}

bool DemonicPresenceClientSkillEffect::getActive()
{
	return true;
}