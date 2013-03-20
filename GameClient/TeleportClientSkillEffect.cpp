#include "TeleportClientSkillEffect.h"
#include "SoundWrapper.h"

TeleportClientSkillEffect::TeleportClientSkillEffect(unsigned int _casterId, const FLOAT3& _position)
{
	int sound = createSoundHandle("skills/teleport.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);

	this->m_casterId = _casterId;
	this->m_position = _position;
}

TeleportClientSkillEffect::~TeleportClientSkillEffect()
{

}

bool TeleportClientSkillEffect::getActive()
{
	return false;
}

void TeleportClientSkillEffect::update(float _dt)
{

}