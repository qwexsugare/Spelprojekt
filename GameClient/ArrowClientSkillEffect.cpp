#include "ArrowClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "Arrow.h"
#include "SpeechManager.h"
#include "MyAlgorithms.h"

ArrowClientSkillEffect::ArrowClientSkillEffect(FLOAT3 _position, unsigned int _targetId, unsigned int _masterId)
{
	m_active = true;
	m_targetId = _targetId;
	m_graphicalEffect = g_graphicsEngine->createModel("Arrow", _position);
	m_graphicalEffect->setAlpha(0.999f);
	m_sound = createSoundHandle("click_button.wav", false, true, _position);
	playSound(m_sound);

	Entity* master = ClientEntityHandler::getEntity(_masterId);

	if(master != NULL)
	{
		master->m_model->getAnimation()->Play("rangeAttack");
	}
}

ArrowClientSkillEffect::ArrowClientSkillEffect(FLOAT3 _position, unsigned int _targetId, Hero::HERO_TYPE _heroType)
{
	m_active = true;
	m_heroType = _heroType;
	m_targetId = _targetId;
	m_graphicalEffect = g_graphicsEngine->createModel("Arrow", _position);
	m_graphicalEffect->setAlpha(0.999f);
	m_sound = createSoundHandle("click_button.wav", false, true, _position);
	playSound(m_sound);
}

ArrowClientSkillEffect::~ArrowClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_graphicalEffect);
	deactivateSound(m_sound);
}

void ArrowClientSkillEffect::update(float _dt)
{
	Entity* target = ClientEntityHandler::getEntity(m_targetId);
	if(target)
	{
		FLOAT3 dist = target->m_model->getPosition()-m_graphicalEffect->getPosition();
		FLOAT3 movement = dist/dist.length()*Arrow::VELOCITY*_dt;

		if(dist.length() > movement.length())
		{
			m_graphicalEffect->move(movement);
			m_graphicalEffect->setRotation(FLOAT3(atan2(-movement.x, -movement.z), 0.0f, 0.0f));
		}
		else
		{
			m_active = false;
			if(target->m_type == UnitEntity::EnemyType)
			{
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
			}
			else
			{
				int sound;

				switch(m_heroType)
				{
				case Hero::RED_KNIGHT:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("red_knight/RedKnight_Damage_0.wav", false, false);
						break;
					case 1:
						sound = createSoundHandle("red_knight/RedKnight_Damage_1.wav", false, false);
						break;
					case 2:
						sound = createSoundHandle("red_knight/RedKnight_Damage_2.wav", false, false);
						break;
					}
					break;
				case Hero::ENGINEER:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("engineer/Engineer_Damage_0.wav", false, false);
						break;
					case 1:
						sound = createSoundHandle("engineer/Engineer_Damage_1.wav", false, false);
						break;
					case 2:
						sound = createSoundHandle("engineer/Engineer_Damage_2.wav", false, false);
						break;
					}
					break;
				case Hero::THE_MENTALIST:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("mentalist/Mentalist_Damage_0.wav", false, false);
						break;
					case 1:
						sound = createSoundHandle("mentalist/Mentalist_Damage_1.wav", false, false);
						break;
					case 2:
						sound = createSoundHandle("mentalist/Mentalist_Damage_2.wav", false, false);
						break;
					}
					break;
				case Hero::OFFICER:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("officer/Officer_Damage_0.wav", false, false);
						break;
					case 1:
						sound = createSoundHandle("officer/Officer_Damage_1.wav", false, false);
						break;
					case 2:
						sound = createSoundHandle("officer/Officer_Damage_2.wav", false, false);
						break;
					}
					break;
				case Hero::DOCTOR:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("doctor/Doctor_Damage_0.wav", false, false);
						break;
					case 1:
						sound = createSoundHandle("doctor/Doctor_Damage_1.wav", false, false);
						break;
					case 2:
						sound = createSoundHandle("doctor/Doctor_Damage_2.wav", false, false);
						break;
					}
					break;
				}

				SpeechManager::speak(m_targetId, sound); // The unit must be killed on the client before on the server for this sound solution to actually work.
			}
		}
	}
	else
	{
		m_active = false;
	}
}

bool ArrowClientSkillEffect::getActive()
{
	return m_active;
}