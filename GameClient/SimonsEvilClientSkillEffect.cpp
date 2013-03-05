#include "SimonsEvilClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "SimonsEvilEffect.h"

SimonsEvilClientSkillEffect::SimonsEvilClientSkillEffect(unsigned int _masterId)
{
	m_masterId = _masterId;
	FLOAT3 pos = ClientEntityHandler::getEntity(_masterId)->m_model->getPosition();
	//m_model = g_graphicsEngine->createModel("redKnightPassiveAura", pos);
	//m_model->setAlpha(0.999f);
	m_sound = createSoundHandle("bow.wav", false, true, pos);
	playSound(m_sound);
	m_timer = 0.0f;

	D3DXVECTOR3 newPos = D3DXVECTOR3(pos.x, pos.y, pos.z);
	this->m_particleSystem = g_graphicsEngine->createParticleEngine(D3DXVECTOR4(newPos, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1.0f, 1.0f));
}

SimonsEvilClientSkillEffect::~SimonsEvilClientSkillEffect()
{
	//g_graphicsEngine->removeModel(m_model);
	g_graphicsEngine->removeParticleEngine(this->m_particleSystem);
	deactivateSound(m_sound);
}

void SimonsEvilClientSkillEffect::update(float _dt)
{
	m_timer += _dt;

	FLOAT3 pos = ClientEntityHandler::getEntity(m_masterId)->m_model->getPosition();
	//m_model->setPosition(pos);
	D3DXVECTOR3 newPos = D3DXVECTOR3(pos.x, pos.y, pos.z);
	this->m_particleSystem->setPosition(newPos);

	if(m_timer >= SimonsEvilEffect::LIFETIME)
		this->m_particleSystem->setAlive(false);
}

bool SimonsEvilClientSkillEffect::getActive()
{
	if(m_timer >= SimonsEvilEffect::LIFETIME + 2)
		return false;
	else
		return true;
}