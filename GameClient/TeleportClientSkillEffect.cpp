#include "TeleportClientSkillEffect.h"
#include "SoundWrapper.h"

TeleportClientSkillEffect::TeleportClientSkillEffect(const FLOAT3& _position)
{
	int sound = createSoundHandle("skills/teleport.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);
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