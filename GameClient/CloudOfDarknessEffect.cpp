#include "CloudOfDarknessEffect.h"
#include "EntityHandler.h"
#include "SoundWrapper.h"

CloudOfDarknessEffect::CloudOfDarknessEffect(FLOAT3 _position)
{
	this->m_type = OtherType;
	this->m_obb = new BoundingOrientedBox();
	m_modelId = 0;
	m_sound = createSoundHandle("collision.wav", false);
	loopSound(m_sound);
}

CloudOfDarknessEffect::~CloudOfDarknessEffect()
{
	deactivateSound(m_sound);
}

void CloudOfDarknessEffect::update(float _dt)
{

}