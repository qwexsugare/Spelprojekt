#include "CloudOfDarknessClientSkillEffect.h"
#include "SoundWrapper.h"
#include "CloudOfDarknessEffect.h"
#include "Graphics.h"

CloudOfDarknessClientSkillEffect::CloudOfDarknessClientSkillEffect(unsigned int _masterId, FLOAT3 _position)
{
	m_position = _position;
	//m_graphicalEffects[0] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.1f, _position.z), "color2");
	//m_graphicalEffects[1] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.2f, _position.z), "color1");
	//m_graphicalEffects[2] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.3f, _position.z), "color");
	//m_graphicalEffects[0]->setScale(0.5f, 0.5f, 0.5f);
	//m_graphicalEffects[2]->setScale(0.5f, 0.5f, 0.5f);
	//m_graphicalEffects[1]->setScale(0.5f, 0.5f, 0.5f);
	//m_graphicalEffects[0]->setAlpha(0.999f);
	//m_graphicalEffects[1]->setAlpha(0.999f);
	//m_graphicalEffects[2]->setAlpha(0.999f);
	//m_graphicalEffects[0]->neutralize();
	//m_graphicalEffects[1]->neutralize();
	//m_graphicalEffects[2]->neutralize();
	m_lifetime = 0.0f;

	m_cloud = g_graphicsEngine->createParticleEngine("CloudOfDarkness", D3DXVECTOR4(_position.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));

	int sound = createSoundHandle("skills/codWindStartEnd.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);
	m_masterId = _masterId;

	Entity *e = ClientEntityHandler::getEntity(_masterId);
	if(e != NULL)
	{
		e->m_model->getAnimation()->Play("Spell");
		m_weapon = e->m_model->getRightHand();
		e->m_model->SetRightHand(NULL);
	}
}

CloudOfDarknessClientSkillEffect::~CloudOfDarknessClientSkillEffect()
{
	g_graphicsEngine->removeParticleEngine(m_cloud);
}

void CloudOfDarknessClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;
	
	if(m_lifetime >= 2)
	{
		Entity *e = ClientEntityHandler::getEntity(m_masterId);
		if(e != NULL)
		{
			e->m_model->SetRightHand(m_weapon);
		}
	}
	if(m_lifetime >= CloudOfDarknessEffect::LIFETIME)
		m_cloud->setAlive(false);
}

bool CloudOfDarknessClientSkillEffect::getActive()
{
	if(m_lifetime >= CloudOfDarknessEffect::LIFETIME + 3)
		return false;
	else
		return true;
}