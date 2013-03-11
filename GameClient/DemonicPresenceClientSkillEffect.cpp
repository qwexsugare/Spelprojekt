#include "DemonicPresenceClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"

DemonicPresenceClientSkillEffect::DemonicPresenceClientSkillEffect(unsigned int _masterId)
{
	m_masterId = _masterId;
	Entity *e = ClientEntityHandler::getEntity(_masterId);
	e->m_model->getAnimation()->Play("DemonicPrecens");
	FLOAT3 pos = e->m_model->getPosition();
	pos.y = 0.01f;
	m_model = g_graphicsEngine->createModel("Pentagram", pos);
	m_model->neutralize();
	m_model->setAlpha(0.75f);
	m_model->setShadow(false);

	// Play sound
	int sound = createSoundHandle("skills/dpHearbeatScreamsStart.wav", false, true, pos);
	playSound(sound);
	deactivateSound(sound);
}

DemonicPresenceClientSkillEffect::~DemonicPresenceClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_model);
}

void DemonicPresenceClientSkillEffect::update(float _dt)
{
	Entity *e = ClientEntityHandler::getEntity(m_masterId);
	if(e != NULL)
	{
		FLOAT3 pos = e->m_model->getPosition();
		pos.y = 0.01f;
		m_model->setPosition(pos);
		m_model->rotate(_dt/3.0f, 0.0f, 0.0f);
	}
}

bool DemonicPresenceClientSkillEffect::getActive()
{
	return true;
}