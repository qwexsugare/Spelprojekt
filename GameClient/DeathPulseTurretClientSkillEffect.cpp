#include "DeathPulseTurretClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "Enemy.h"
#include "MyAlgorithms.h"
#include "SpeechManager.h"

DeathPulseTurretClientSkillEffect::DeathPulseTurretClientSkillEffect(unsigned int _masterId)
{
	Entity* target = ClientEntityHandler::getEntity(_masterId);

	m_masterId = _masterId;
	FLOAT3 pos = target->m_model->getPosition();
	m_model = g_graphicsEngine->createModel("Bench", pos);
	m_model->setAlpha(0.999f);
	m_soundVolume = 0.25f;
	m_sound = createSoundHandle("turrets/deathTowerAttack.wav", false, true, pos, m_soundVolume);
	playSound(m_sound);
	m_timer = 0.0f;
	m_active = true;
	
	// Play damage sound.
	int sound;
	switch(target->m_subtype)
	{
	case Enemy::IMP:
		switch(random(0, 2))
		{
		case 0:
			sound = createSoundHandle("enemy/Monster_Imp_Damage_0.wav", false, true, target->m_model->getPosition());
			break;
		case 1:
			sound = createSoundHandle("enemy/Monster_Imp_Damage_1.wav", false, true, target->m_model->getPosition());
			break;
		case 2:
			sound = createSoundHandle("enemy/Monster_Imp_Damage_2.wav", false, true, target->m_model->getPosition());
			break;
		}
		break;
	case Enemy::SHADE:
		switch(random(0, 2))
		{
		case 0:
			sound = createSoundHandle("enemy/Monster_Shade_Damage_0.wav", false, true, target->m_model->getPosition());
			break;
		case 1:
			sound = createSoundHandle("enemy/Monster_Shade_Damage_1.wav", false, true, target->m_model->getPosition());
			break;
		case 2:
			sound = createSoundHandle("enemy/Monster_Shade_Damage_2.wav", false, true, target->m_model->getPosition());
			break;
		}
		break;
	case Enemy::FROST_DEMON:
		switch(random(0, 2))
		{
		case 0:
			sound = createSoundHandle("enemy/Monster_Frost_Damage_0.wav", false, true, target->m_model->getPosition());
			break;
		case 1:
			sound = createSoundHandle("enemy/Monster_Frost_Damage_1.wav", false, true, target->m_model->getPosition());
			break;
		case 2:
			sound = createSoundHandle("enemy/Monster_Frost_Damage_2.wav", false, true, target->m_model->getPosition());
			break;
		}
		break;
	case Enemy::SPITTING_DEMON:
		switch(random(0, 2))
		{
		case 0:
			sound = createSoundHandle("enemy/Monster_Spitting_Damage_0.wav", false, true, target->m_model->getPosition());
			break;
		case 1:
			sound = createSoundHandle("enemy/Monster_Spitting_Damage_1.wav", false, true, target->m_model->getPosition());
			break;
		case 2:
			sound = createSoundHandle("enemy/Monster_Spitting_Damage_2.wav", false, true, target->m_model->getPosition());
			break;
		}
		break;
	case Enemy::HELLFIRE_STEED:
		switch(random(0, 2))
		{
		case 0:
			sound = createSoundHandle("enemy/Beast_Damage_0.wav", false, true, target->m_model->getPosition());
			break;
		case 1:
			sound = createSoundHandle("enemy/Beast_Damage_1.wav", false, true, target->m_model->getPosition());
			break;
		case 2:
			sound = createSoundHandle("enemy/Beast_Damage_2.wav", false, true, target->m_model->getPosition());
			break;
		}
		break;
	case Enemy::SOUL_EATER_STEED:
		switch(random(0, 2))
		{
		case 0:
			sound = createSoundHandle("enemy/Beast_Damage_0.wav", false, true, target->m_model->getPosition());
			break;
		case 1:
			sound = createSoundHandle("enemy/Beast_Damage_1.wav", false, true, target->m_model->getPosition());
			break;
		case 2:
			sound = createSoundHandle("enemy/Beast_Damage_2.wav", false, true, target->m_model->getPosition());
			break;
		}
		break;
	case Enemy::THUNDERSTEED:
		switch(random(0, 2))
		{
		case 0:
			sound = createSoundHandle("enemy/Beast_Damage_0.wav", false, true, target->m_model->getPosition());
			break;
		case 1:
			sound = createSoundHandle("enemy/Beast_Damage_1.wav", false, true, target->m_model->getPosition());
			break;
		case 2:
			sound = createSoundHandle("enemy/Beast_Damage_2.wav", false, true, target->m_model->getPosition());
			break;
		}
		break;
	case Enemy::BRUTE_STEED:
		switch(random(0, 2))
		{
		case 0:
			sound = createSoundHandle("enemy/Beast_Damage_0.wav", false, true, target->m_model->getPosition());
			break;
		case 1:
			sound = createSoundHandle("enemy/Beast_Damage_1.wav", false, true, target->m_model->getPosition());
			break;
		case 2:
			sound = createSoundHandle("enemy/Beast_Damage_2.wav", false, true, target->m_model->getPosition());
			break;
		}
		break;
	}

	SpeechManager::speak(_masterId, sound); // The unit must be killed on the client before on the server for this sound solution to actually work.
	deactivateSound(sound);
}

DeathPulseTurretClientSkillEffect::~DeathPulseTurretClientSkillEffect()
{
	g_graphicsEngine->removeModel(m_model);
	deactivateSound(m_sound);
}

void DeathPulseTurretClientSkillEffect::update(float _dt)
{
	if(m_active)
	{
		m_timer += _dt;
		if(m_timer > DeathPulseTurretClientSkillEffect::DURATION)
			m_active = false;
		else
		{
			Entity* master = ClientEntityHandler::getEntity(m_masterId);
			if(master)
			{
				FLOAT3 pos = ClientEntityHandler::getEntity(m_masterId)->m_model->getPosition();
				m_model->setPosition(pos);

				// Fade out sound
				if(m_timer > DeathPulseTurretClientSkillEffect::DURATION/2.0f)
				{
					m_soundVolume = max(m_soundVolume-_dt, 0.0f);
					setSoundVolume(m_sound, m_soundVolume);
				}
			}
			else
				m_active = false;
		}
	}
}

bool DeathPulseTurretClientSkillEffect::getActive()
{
	return m_active;
}