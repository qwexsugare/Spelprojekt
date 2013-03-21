#include "DeathPulseTurretClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "Enemy.h"
#include "MyAlgorithms.h"
#include "SpeechManager.h"

DeathPulseTurretClientSkillEffect::DeathPulseTurretClientSkillEffect(unsigned int _masterId, unsigned int _turretId)
{
	Entity* target = ClientEntityHandler::getEntity(_masterId);
	Entity* turret = ClientEntityHandler::getEntity(_turretId);

	m_masterId = _masterId;
	m_turretId = _turretId;
	FLOAT3 pos(0, 0, 0);
	if(target)
		pos	= target->m_model->getPosition();
	//m_model = g_graphicsEngine->createModel("Bench", pos);
	//m_model->setAlpha(0.999f);
	m_timer = 0.0f;
	m_active = true;

	m_partOne = NULL;
	m_partTwo = NULL;
	
	if(target)
	{
		m_partOne = g_graphicsEngine->createParticleEngine("DeathPulsOne", D3DXVECTOR4(0, 0, 0, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
	}
	if(turret)
	{
		FLOAT3 tPos = turret->m_model->getPosition();;
		m_partTwo = g_graphicsEngine->createParticleEngine("DeathPulsOne", D3DXVECTOR4(tPos.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(0.7f, 0.7f));
	}
	
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
	case Enemy::BOSS:
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
	g_graphicsEngine->removeParticleEngine(m_partOne);
	g_graphicsEngine->removeParticleEngine(m_partTwo);
}

void DeathPulseTurretClientSkillEffect::update(float _dt)
{
	if(m_active)
	{
		m_timer += _dt;
		if(m_timer > DeathPulseTurretClientSkillEffect::DURATION)
			m_active = false;
		if(m_timer > DeathPulseTurretClientSkillEffect::DURATION-1)
		{
			if(m_partOne)
				m_partOne->setAlive(false);
			if(m_partTwo)
				m_partTwo->setAlive(false);
		}
		else
		{
			Entity* master = ClientEntityHandler::getEntity(m_masterId);
			if(master)
			{
				FLOAT3 pos = ClientEntityHandler::getEntity(m_masterId)->m_model->getPosition();
				if(m_partOne)
					m_partOne->setPosition(pos.toD3DXVector());
				//m_model->setPosition(pos);
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