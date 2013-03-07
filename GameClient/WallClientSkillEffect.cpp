#include "WallClientSkillEffect.h"
#include "SoundWrapper.h"

WallClientSkillEffect::WallClientSkillEffect(unsigned int _masterId, FLOAT3 _position)
{
	Entity *master = ClientEntityHandler::getEntity(_masterId);

	if(master != NULL)
	{
		master->m_model->getAnimation()->Play("Spell");
	}

	// Play sound
	int sound = createSoundHandle("skills/wallStartGroundShake.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);
}

WallClientSkillEffect::~WallClientSkillEffect()
{

}

void WallClientSkillEffect::update(float _dt)
{

}

bool WallClientSkillEffect::getActive()
{
	return false;
}