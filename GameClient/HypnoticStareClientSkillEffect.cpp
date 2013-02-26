#include "HypnoticStareClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "HypnoticStareEffect.h"

HypnoticStareClientSkillEffect::HypnoticStareClientSkillEffect(unsigned int _masterId, float _duration)
{
	m_masterId = _masterId;
	m_timer = _duration;

	Entity *e = ClientEntityHandler::getEntity(_masterId);
	if(e != NULL)
		e->m_model->setGlowIndex("glowIntensity1");
}

HypnoticStareClientSkillEffect::~HypnoticStareClientSkillEffect()
{
	Entity *e = ClientEntityHandler::getEntity(m_masterId);
	if(e)
		e->m_model->setGlowIndex("glowIntensity");
}

void HypnoticStareClientSkillEffect::update(float _dt)
{
	m_timer = max(m_timer-_dt, 0.0f);
}

bool HypnoticStareClientSkillEffect::getActive()
{
	if(m_timer == 0.0f)
		return false;
	else
		return true;
}