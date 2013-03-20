#include "HealingTouchClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"

HealingTouchClientSkillEffect::HealingTouchClientSkillEffect(FLOAT3 _position, unsigned int casterId, unsigned int _targetId)
{
	m_position = _position;
	m_lifetime = 0.0f;
	m_casterId = casterId;
	
	int sound = createSoundHandle("skills/healingTouch.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);

	Entity *e = ClientEntityHandler::getEntity(casterId);
	if(e != NULL)
	{
		e->m_model->getAnimation()->Play("Spell");
		this->m_weapon = e->m_model->getRightHand();
		e->m_model->SetRightHand(NULL);
	}

	// ANDERS DO TARGET IT WITH ABOVE STUFF
}

HealingTouchClientSkillEffect::~HealingTouchClientSkillEffect()
{
	Entity *e = ClientEntityHandler::getEntity(m_casterId);
	if(e != NULL)
	{
		e->m_model->SetRightHand(this->m_weapon);
	}
}

void HealingTouchClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;
}

bool HealingTouchClientSkillEffect::getActive()
{
	if(m_lifetime >= 2)
		return false;
	else
		return true;
}