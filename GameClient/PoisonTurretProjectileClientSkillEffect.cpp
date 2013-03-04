#include "PoisonTurretProjectileClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "FrostTurretProjectile.h"
#include "SpeechManager.h"
#include "MyAlgorithms.h"

PoisonTurretProjectileClientSkillEffect::PoisonTurretProjectileClientSkillEffect(FLOAT3 _position, unsigned int _targetId)
{
	m_active = true;
	m_targetId = _targetId;
	m_graphicalEffect = g_graphicsEngine->createModel("Arrow", _position);
	m_graphicalEffect->setScale(1.5f, 1.5f, 1.5f);
	m_graphicalEffect->setAlpha(0.999f);
}

PoisonTurretProjectileClientSkillEffect::~PoisonTurretProjectileClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_graphicalEffect);
}

void PoisonTurretProjectileClientSkillEffect::update(float _dt)
{
	Entity* target = ClientEntityHandler::getEntity(m_targetId);
	if(target)
	{
		FLOAT2 dist = target->m_model->getPosition2DAsFloat2()-m_graphicalEffect->getPosition2DAsFloat2();
		FLOAT2 movement = dist/dist.length()*FrostTurretProjectile::VELOCITY*_dt;

		if(dist.length() > movement.length())
		{
			m_graphicalEffect->move(FLOAT3(movement.x, 0.0f, movement.y));
			m_graphicalEffect->setRotation(FLOAT3(atan2(-movement.x, -movement.y), 0.0f, 0.0f));
		}
		else
		{
			m_active = false;

			int sound;

			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("enemy/Monster_Imp_Damage_0.wav", false, false);
				break;
			case 1:
				sound = createSoundHandle("enemy/Monster_Imp_Damage_1.wav", false, false);
				break;
			case 2:
				sound = createSoundHandle("enemy/Monster_Imp_Damage_2.wav", false, false);
				break;
			}
					
			SpeechManager::speak(m_targetId, sound); // The unit must be killed on the client before on the server for this sound solution to actually work.
			deactivateSound(sound);
		}
	}
	else
	{
		m_active = false;
	}
}

bool PoisonTurretProjectileClientSkillEffect::getActive()
{
	return m_active;
}
