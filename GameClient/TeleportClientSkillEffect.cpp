#include "TeleportClientSkillEffect.h"
#include "SoundWrapper.h"
#include "ClientEntityHandler.h"

TeleportClientSkillEffect::TeleportClientSkillEffect(unsigned int _casterId, const FLOAT3& _position)
{
	int sound = createSoundHandle("skills/teleport.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);
	m_lifeTime = 0;

	this->m_casterId = _casterId;
	this->m_position = _position;

	m_origTele = NULL;
	m_targetTele = NULL;

	Entity* e = ClientEntityHandler::getEntity(_casterId);
	if(e != NULL)
		m_origTele = g_graphicsEngine->createParticleEngine("Teleport", D3DXVECTOR4(e->m_model->getPosition().toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));

	m_targetTele = g_graphicsEngine->createParticleEngine("Teleport", D3DXVECTOR4(m_position.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
}

TeleportClientSkillEffect::~TeleportClientSkillEffect()
{
	if(m_origTele)
		g_graphicsEngine->removeParticleEngine(m_origTele);
	if(m_targetTele)
		g_graphicsEngine->removeParticleEngine(m_targetTele);
}


void TeleportClientSkillEffect::update(float _dt)
{
	m_lifeTime += _dt;
	if(m_lifeTime >= 1.0)
	{
		if(m_origTele)
			m_origTele->setAlive(false);
		if(m_targetTele)
			m_targetTele->setAlive(false);
	}
}

bool TeleportClientSkillEffect::getActive()
{
	if(m_lifeTime >= 2.0)
		return false;
	else
		return true;
}