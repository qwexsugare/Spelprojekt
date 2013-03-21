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
		
		D3DXVECTOR4 partPos(pos.x, pos.y, pos.z, 1);
		D3DXQUATERNION partRot(0, 0, 0, 1);
		m_aura = g_graphicsEngine->createParticleEngine("EnigmaticPresence", partPos, partRot, D3DXVECTOR2(1, 1));

		m_active = true;
	}
	else
	{
		m_active = false;
	}
}

EnigmaticPresenceClientSkillEffect::~EnigmaticPresenceClientSkillEffect()
{
	g_graphicsEngine->removeParticleEngine(m_aura);
}

void EnigmaticPresenceClientSkillEffect::update(float _dt)
{
	Entity* unit = ClientEntityHandler::getEntity(m_masterId);
	if(unit)
	{
		FLOAT3 pos = unit->m_model->getPosition();
		pos.y = 0.01f;
		m_aura->setPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
	}
	else
		m_active = false;
}

bool EnigmaticPresenceClientSkillEffect::getActive()
{
	return m_active;
}