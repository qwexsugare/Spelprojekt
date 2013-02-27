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
	{
		this->m_oldTexture = e->m_model->getTextureIndex();
		this->m_oldGlow = e->m_model->getGlowIndex();
		e->m_model->setGlowIndex("glowIntensity");
		e->m_model->setTextureIndex("color4");
	}
}

HypnoticStareClientSkillEffect::~HypnoticStareClientSkillEffect()
{
	Entity *e = ClientEntityHandler::getEntity(m_masterId);
	if(e)
	{
		e->m_model->setTextureIndex(this->m_oldTexture);
		e->m_model->setGlowIndex(this->m_oldGlow);
	}
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