#include "WallClientSkillEffect.h"
#include "SoundWrapper.h"

WallClientSkillEffect::WallClientSkillEffect(unsigned int _masterId, FLOAT3 _position)
{
	Entity *master = ClientEntityHandler::getEntity(_masterId);
	m_masterId = _masterId;

	if(master != NULL)
	{
		master->m_model->getAnimation()->Play("Spell");
		this->m_weapon = master->m_model->getRightHand();
		master->m_model->SetRightHand(NULL);
	}

	// Play sound
	int sound = createSoundHandle("skills/wallStartGroundShake.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);
}

WallClientSkillEffect::~WallClientSkillEffect()
{
	Entity *master = ClientEntityHandler::getEntity(m_masterId);
	if(master != NULL)
	{
		master->m_model->SetRightHand(m_weapon);
	}
}

void WallClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;
}

bool WallClientSkillEffect::getActive()
{
	if(m_lifetime >= 2)
		return false;
	else
		return true;
}