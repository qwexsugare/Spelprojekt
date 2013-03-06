#include "MeleeAOEClientSkillEffect.h"
#include "SoundWrapper.h"
#include "MyAlgorithms.h"
#include "SpeechManager.h"
#include "Enemy.h"

float MeleeAOEClientSkillEffect::timeToNextDamageSound = 0.0f;

MeleeAOEClientSkillEffect::MeleeAOEClientSkillEffect(unsigned int _masterId, unsigned int _targetId, PLAYER_INFO _playerInfo)
{
	this->m_lifetime = 1.0f;
	Entity* master = ClientEntityHandler::getEntity(_masterId);
	
	if(master != NULL)
	{
		master->m_model->getAnimation()->PlayLoop("2Hattack");

		Entity* target = ClientEntityHandler::getEntity(_targetId);
		if(target)
		{
			if(master->m_type == ServerEntity::HeroType)
			{
				// Play impact sound
				int impactSound;
				switch(random(0, 2))
				{
				case 0:
					impactSound = createSoundHandle("attacks/twoHandedAttack_0.wav", false, true, target->m_startPos);
					break;
				case 1:
					impactSound = createSoundHandle("attacks/twoHandedAttack_1.wav", false, true, target->m_startPos);
					break;
				case 2:
					impactSound = createSoundHandle("attacks/twoHandedAttack_2.wav", false, true, target->m_startPos);
					break;
				}

				playSound(impactSound);
				deactivateSound(impactSound);
			}

			// Play damage sound.
			int sound;
			switch(target->m_type)
			{
			case ServerEntity::HeroType:
				switch(_playerInfo.heroType)
				{
				case Hero::RED_KNIGHT:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("red_knight/RedKnight_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("red_knight/RedKnight_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("red_knight/RedKnight_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				case Hero::ENGINEER:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("engineer/Engineer_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("engineer/Engineer_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("engineer/Engineer_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				case Hero::THE_MENTALIST:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("mentalist/Mentalist_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("mentalist/Mentalist_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("mentalist/Mentalist_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				case Hero::OFFICER:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("officer/Officer_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("officer/Officer_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("officer/Officer_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				case Hero::DOCTOR:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("doctor/Doctor_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("doctor/Doctor_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("doctor/Doctor_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				}
				break;

			case ServerEntity::EnemyType:
				switch(target->m_subtype)
				{
				case Enemy::IMP:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("enemy/Monster_Imp_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("enemy/Monster_Imp_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("enemy/Monster_Imp_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				case Enemy::SHADE:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("enemy/Monster_Shade_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("enemy/Monster_Shade_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("enemy/Monster_Shade_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				case Enemy::FROST_DEMON:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("enemy/Monster_Frost_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("enemy/Monster_Frost_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("enemy/Monster_Frost_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				case Enemy::SPITTING_DEMON:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("enemy/Monster_Spitting_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("enemy/Monster_Spitting_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("enemy/Monster_Spitting_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				case Enemy::HELLFIRE_STEED:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("enemy/Beast_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("enemy/Beast_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("enemy/Beast_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				case Enemy::SOUL_EATER_STEED:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("enemy/Beast_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("enemy/Beast_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("enemy/Beast_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				case Enemy::THUNDERSTEED:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("enemy/Beast_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("enemy/Beast_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("enemy/Beast_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				case Enemy::BRUTE_STEED:
					switch(random(0, 2))
					{
					case 0:
						sound = createSoundHandle("enemy/Beast_Damage_0.wav", false, true, target->m_startPos);
						break;
					case 1:
						sound = createSoundHandle("enemy/Beast_Damage_1.wav", false, true, target->m_startPos);
						break;
					case 2:
						sound = createSoundHandle("enemy/Beast_Damage_2.wav", false, true, target->m_startPos);
						break;
					}
					break;
				}
				break;
			}

			SpeechManager::speak(_targetId, sound);
			deactivateSound(sound);
		}
	}
}

MeleeAOEClientSkillEffect::~MeleeAOEClientSkillEffect()
{

}

void MeleeAOEClientSkillEffect::decreaseTimeBetweenDamageSounds(float _dt)
{
	MeleeAOEClientSkillEffect::timeToNextDamageSound = max(MeleeAOEClientSkillEffect::timeToNextDamageSound-_dt, 0.0f);
}

void MeleeAOEClientSkillEffect::update(float dt)
{
	this->m_lifetime -= dt;
}

bool MeleeAOEClientSkillEffect::getActive()
{
	if(this->m_lifetime <= 0.0f)
	{
		return false;
	}
	else
	{
		return true;
	}
}