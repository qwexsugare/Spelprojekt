#include "EnigmaticPresenceClientSkillEffect.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"

EnigmaticPresenceClientSkillEffect::EnigmaticPresenceClientSkillEffect(unsigned int _masterId)
{
	m_masterId = _masterId;

	Entity* unit = ClientEntityHandler::getEntity(m_masterId);
	if(unit)
	{
		FLOAT3 pos = unit->m_model->getPosition();
		pos.y = 0.01f;
		m_model = g_graphicsEngine->createModel("Pentagram", pos);
		m_model->neutralize();
		m_model->setAlpha(0.75f);
		m_model->setShadow(false);

		m_active = true;
	}
	else
	{
		m_model = NULL;
		m_active = false;
	}
}

EnigmaticPresenceClientSkillEffect::~EnigmaticPresenceClientSkillEffect()
{
	if(m_model)
		g_graphicsEngine->removeModel(m_model);
}

void EnigmaticPresenceClientSkillEffect::update(float _dt)
{
	Entity* unit = ClientEntityHandler::getEntity(m_masterId);
	if(unit)
	{
		FLOAT3 pos = unit->m_model->getPosition();
		pos.y = 0.01f;
		m_model->setPosition(pos);
		m_model->rotate(_dt/3.0f, 0.0f, 0.0f);
	}
	else
		m_active = false;
}

bool EnigmaticPresenceClientSkillEffect::getActive()
{
	return m_active;
}