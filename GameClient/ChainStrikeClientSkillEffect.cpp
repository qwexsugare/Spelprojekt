#include "ChainStrikeClientSkillEffect.h"
#include "SoundWrapper.h"
#include "ChainStrikeEffect.h"
#include "Graphics.h"

ChainStrikeClientSkillEffect::ChainStrikeClientSkillEffect(unsigned int _masterId, FLOAT3 _position, bool _playAnimation)
{
	m_graphicalEffects[0] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.1f, _position.z), "color2");
	m_graphicalEffects[1] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.2f, _position.z), "color1");
	m_graphicalEffects[2] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.3f, _position.z), "color");
	m_graphicalEffects[0]->setScale(0.5f, 0.5f, 0.5f);
	m_graphicalEffects[2]->setScale(0.5f, 0.5f, 0.5f);
	m_graphicalEffects[1]->setScale(0.5f, 0.5f, 0.5f);
	m_graphicalEffects[0]->setAlpha(0.999f);
	m_graphicalEffects[1]->setAlpha(0.999f);
	m_graphicalEffects[2]->setAlpha(0.999f);

	m_lifetime = 0.0f;
	m_sound = createSoundHandle("TurretBuildup.wav", false, true, _position);
	playSound(m_sound);

	if(_playAnimation)
	{
		Entity *e = ClientEntityHandler::getEntity(_masterId);
		if(e != NULL && e->m_type == ServerEntity::HeroType)
		{
			e->m_model->getAnimation()->Play("ChainLight");
		}
	}
}

ChainStrikeClientSkillEffect::~ChainStrikeClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_graphicalEffects[0]);
	g_graphicsEngine->removeModel(m_graphicalEffects[1]);
	g_graphicsEngine->removeModel(m_graphicalEffects[2]);
	deactivateSound(m_sound);
}

void ChainStrikeClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;
}

bool ChainStrikeClientSkillEffect::getActive()
{
	if(m_lifetime >= ChainStrikeEffect::TIME_BETWEEN_JUMPS)
		return false;
	else
		return true;
}