#include "TargetAcquiredClientSkillEffect.h"
#include "SoundWrapper.h"
#include "ClientEntityHandler.h"

TargetAcquiredClientSkillEffect::TargetAcquiredClientSkillEffect(unsigned int _masterId, FLOAT3 position)
{
	this->m_model = g_graphicsEngine->createModel("CloudOfDarkness", position);	//Temporär, ska ersättas med partikeleffekt
	this->m_lifetime = 5.0f;

	Entity* e = ClientEntityHandler::getEntity(_masterId);
	if(e)
	{
		int sound = createSoundHandle("skills/target_acquired_permission_to_fire.wav", false, true, e->m_startPos);
		playSound(sound);
		deactivateSound(sound);
	}
}

TargetAcquiredClientSkillEffect::~TargetAcquiredClientSkillEffect()
{
	g_graphicsEngine->removeModel(this->m_model);
}

void TargetAcquiredClientSkillEffect::update(float _dt)
{
	this->m_lifetime = this->m_lifetime - _dt;
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