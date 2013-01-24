#include "CloudOfDarknessEffect.h"
#include "EntityHandler.h"
#include "SoundWrapper.h"

CloudOfDarknessEffect::CloudOfDarknessEffect(FLOAT3 _position, int _damage)
{
	m_damage = _damage;
	m_position = _position;

	this->m_obb = new BoundingOrientedBox();
	m_modelId = 0;
	m_timer = 0.0f;
	m_type = OtherType;
	m_sound = createSoundHandle("collision.wav", false);
	playSound(m_sound);

	vector<ServerEntity*>* enemies = EntityHandler::getAllEnemies();

	for(int i = 0; i < enemies->size(); i++)
	{
		if(((*enemies)[i]->getPosition()-m_position).length() <= AOE)
		{
			this->dealDamage((*enemies)[i], this->m_damage, false);
		}
	}

	delete enemies;
}

CloudOfDarknessEffect::~CloudOfDarknessEffect()
{
	deactivateSound(m_sound);
}

void CloudOfDarknessEffect::update(float _dt)
{
	m_timer += _dt;

	if(m_timer > LIFETIME)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}