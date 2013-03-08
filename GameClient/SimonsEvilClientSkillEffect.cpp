#include "SimonsEvilClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "SimonsEvilEffect.h"

SimonsEvilClientSkillEffect::SimonsEvilClientSkillEffect(unsigned int _masterId)
{
	m_masterId = _masterId;
	Entity* master = ClientEntityHandler::getEntity(_masterId);
	if(master)
	{
		m_timer = 0.0f;

		D3DXVECTOR3 newPos = D3DXVECTOR3(master->m_startPos.x, master->m_startPos.y, master->m_startPos.z);
		this->m_particleSystem = g_graphicsEngine->createParticleEngine(D3DXVECTOR4(newPos, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1.0f, 1.0f));

		// Play sound
		int sound = createSoundHandle("skills/healing_aura.wav", false, true, master->m_startPos);
		playSound(sound);
		deactivateSound(sound);
	}
	else
	{
		m_timer = SimonsEvilEffect::LIFETIME;
		m_particleSystem = NULL;
	}
}

SimonsEvilClientSkillEffect::~SimonsEvilClientSkillEffect()
{
	if(m_particleSystem)
		g_graphicsEngine->removeParticleEngine(this->m_particleSystem);
}

void SimonsEvilClientSkillEffect::update(float _dt)
{
	m_timer += _dt;

	if(m_timer >= SimonsEvilEffect::LIFETIME)
		this->m_particleSystem->setAlive(false);
	else
	{
		FLOAT3 pos = ClientEntityHandler::getEntity(m_masterId)->m_model->getPosition();
		D3DXVECTOR3 newPos = D3DXVECTOR3(pos.x, pos.y, pos.z);
		this->m_particleSystem->setPosition(newPos);
	}
}

bool SimonsEvilClientSkillEffect::getActive()
{
	if(m_timer >= SimonsEvilEffect::LIFETIME + 2) // +2 so that poarticle effect have time to die out [AndersFusk] 
		return false;
	else
		return true;
}