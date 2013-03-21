#include "TargetAcquiredClientSkillEffect.h"
#include "SoundWrapper.h"
#include "ClientEntityHandler.h"

TargetAcquiredClientSkillEffect::TargetAcquiredClientSkillEffect(unsigned int _masterId, FLOAT3 position)
{
	this->m_lifetime = 5.0f;

	Entity* e = ClientEntityHandler::getEntity(_masterId);
	if(e)
	{
		int sound = createSoundHandle("skills/target_acquired_permission_to_fire.wav", false, true, e->m_startPos);
		playSound(sound);
		deactivateSound(sound);
	}
	m_firePos = position;
	m_firePos.y = 10;
	m_fireTwoPos = position;
	m_fireTwoPos.y = 10;
	m_icePos = position;
	m_icePos.y = 8;
	m_lightningPos = position;
	m_lightningPos.y = 10;
	
	m_bfireOne = false;
	m_bfireTwo = false;
	m_biceOne = false;
	m_blightningOne = false;

	m_fire = NULL;
	m_fireTwo = NULL;
	m_ice = NULL;
	m_lightning = NULL;
}

TargetAcquiredClientSkillEffect::~TargetAcquiredClientSkillEffect()
{
	g_graphicsEngine->removeParticleEngine(m_fire);
	g_graphicsEngine->removeParticleEngine(m_fireTwo);
	g_graphicsEngine->removeParticleEngine(m_ice);
	g_graphicsEngine->removeParticleEngine(m_lightning);
}

void TargetAcquiredClientSkillEffect::update(float _dt)
{
	this->m_lifetime = this->m_lifetime - _dt;
	float speed = 4;

	if(this->m_lifetime <= 5 && !m_fire)
	{
		m_firePos.x += 0.5f;
		m_fire = g_graphicsEngine->createParticleEngine("HellFireTail", D3DXVECTOR4(m_firePos.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
	}
	if(this->m_lifetime <= 3.0f && !m_fireTwo)
	{
		m_fireTwo = g_graphicsEngine->createParticleEngine("HellFireTail", D3DXVECTOR4(m_fireTwoPos.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
	}
	if(this->m_lifetime <= 4.2f && !m_ice)
	{
		m_icePos.x -= 0.5f;
		m_ice = g_graphicsEngine->createParticleEngine("FrostTail", D3DXVECTOR4(m_icePos.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(2, 2));
	}
	if(this->m_lifetime <= 2.3f && !m_lightning)
	{
		m_lightningPos.x += 0.5f;
		m_lightning = g_graphicsEngine->createParticleEngine("test3", D3DXVECTOR4(m_lightningPos.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
	}


	if(m_fire)
	{
		m_firePos.y -= _dt*speed;
		m_fire->setPosition(m_firePos.toD3DXVector());
	}
	if(m_fireTwo)
	{
		m_fireTwoPos.y -= _dt*speed;
		m_fireTwo->setPosition(m_fireTwoPos.toD3DXVector());
	}
	if(m_ice)
	{
		m_icePos.y -= _dt*speed*2;
		m_ice->setPosition(m_icePos.toD3DXVector());
	}
	if(m_lightning)
	{
		m_lightningPos.y -= _dt*speed*2;
		m_lightning->setPosition(m_lightningPos.toD3DXVector());
	}
}

bool TargetAcquiredClientSkillEffect::getActive()
{
	if(this->m_lifetime > 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}