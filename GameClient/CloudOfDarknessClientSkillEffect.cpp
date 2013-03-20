#include "CloudOfDarknessClientSkillEffect.h"
#include "SoundWrapper.h"
#include "CloudOfDarknessEffect.h"
#include "Graphics.h"

CloudOfDarknessClientSkillEffect::CloudOfDarknessClientSkillEffect(unsigned int _masterId, FLOAT3 _position)
{
	m_position = _position;
	m_graphicalEffects[0] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.1f, _position.z), "color2");
	m_graphicalEffects[1] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.2f, _position.z), "color1");
	m_graphicalEffects[2] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.3f, _position.z), "color");
	m_graphicalEffects[0]->setScale(0.5f, 0.5f, 0.5f);
	m_graphicalEffects[2]->setScale(0.5f, 0.5f, 0.5f);
	m_graphicalEffects[1]->setScale(0.5f, 0.5f, 0.5f);
	m_graphicalEffects[0]->setAlpha(0.999f);
	m_graphicalEffects[1]->setAlpha(0.999f);
	m_graphicalEffects[2]->setAlpha(0.999f);
	m_graphicalEffects[0]->neutralize();
	m_graphicalEffects[1]->neutralize();
	m_graphicalEffects[2]->neutralize();
	m_lifetime = 0.0f;

	int sound = createSoundHandle("skills/codWindStartEnd.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);
	m_masterId = _masterId;

	Entity *e = ClientEntityHandler::getEntity(_masterId);
	if(e != NULL)
	{
		e->m_model->getAnimation()->Play("Spell");
		//hest = e->m_model->getRightHand();
		//e->m_model->SetRightHand(NULL);
	}
}

CloudOfDarknessClientSkillEffect::~CloudOfDarknessClientSkillEffect()
{
	//g_graphicsEngine->removePointLight(this->m_light);
	g_graphicsEngine->removeModel(m_graphicalEffects[0]);
	g_graphicsEngine->removeModel(m_graphicalEffects[1]);
	g_graphicsEngine->removeModel(m_graphicalEffects[2]);

	//Entity *e = ClientEntityHandler::getEntity(m_masterId);
	//if(e != NULL)
	//{
	//	e->m_model->SetRightHand(m_weapon);
	//}
}

void CloudOfDarknessClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;
	
	m_graphicalEffects[0]->rotate(-_dt, 0.0f, 0.0f);
	m_graphicalEffects[1]->rotate(_dt, 0.0f, 0.0f);
	m_graphicalEffects[2]->rotate(-_dt, 0.0f, 0.0f);
	m_graphicalEffects[0]->setAlpha(m_graphicalEffects[0]->getAlpha()-(_dt/double(CloudOfDarknessEffect::LIFETIME)));
	m_graphicalEffects[1]->setAlpha(m_graphicalEffects[1]->getAlpha()-(_dt/double(CloudOfDarknessEffect::LIFETIME)));
	m_graphicalEffects[2]->setAlpha(m_graphicalEffects[2]->getAlpha()-(_dt/double(CloudOfDarknessEffect::LIFETIME)));
}

bool CloudOfDarknessClientSkillEffect::getActive()
{
	if(m_lifetime >= CloudOfDarknessEffect::LIFETIME)
		return false;
	else
		return true;
}