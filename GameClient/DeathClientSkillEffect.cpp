#include "DeathClientSkillEffect.h"
#include "MyAlgorithms.h"
#include "SpeechManager.h"
#include "SoundWrapper.h"
#include "Hero.h"
#include "Enemy.h"

DeathClientSkillEffect::DeathClientSkillEffect(unsigned int _masterId, FLOAT3 _position)
{
	this->m_masterId = _masterId;
	this->m_lifetime = 10.0f;
	this->m_sink = false;
	this->m_model = NULL;
	this->m_lanternLight = NULL;

	Entity *e = ClientEntityHandler::getEntity(this->m_masterId);
	
	
	//g_graphicsEngine->createPointLight(_position, FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false, FLOAT3(0.0f, 1.0f, 0.0f));

	if(e != NULL)
	{
		this->m_model = g_graphicsEngine->createModel(e->m_model, false);
		this->m_model->setPosition(_position);
		this->m_model->getAnimation()->Play("death", true);
		this->m_model->SetHat(e->m_model->getHat());
		this->m_model->SetLeftHand(e->m_model->getLeftHand());
		this->m_model->SetRightHand(e->m_model->getRightHand());

		m_model->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
		if(e->m_type == ServerEntity::EnemyType)
		{
			this->m_sink = true;
			m_model->setColor(D3DXVECTOR4(1, 0, 0, 0.4f));
		}
		

		if(e->m_lanternLight != NULL)
		{
			this->m_lanternLight = g_graphicsEngine->createPointLight(this->m_model->getLeftHandPosition(), e->m_lanternLight->getAmbientColor(), e->m_lanternLight->getDiffuseColor(), e->m_lanternLight->getSpecularColor(), e->m_lanternLight->getRadius(), true, false, FLOAT3(0.0f, 1.0f, 0.0f));
			this->m_originalDiffuse = this->m_lanternLight->getDiffuseColor();
			this->m_originalSpecular = this->m_lanternLight->getSpecularColor();
		}

		// Play death sound.
		int sound;
		switch(e->m_type)
		{
		case ServerEntity::HeroType:
			switch(e->m_subtype)
			{
			case Hero::RED_KNIGHT:
				switch(random(0, 2))
				{
				case 0:
					sound = createSoundHandle("red_knight/RedKnight_Death_0.wav", false, true, e->m_startPos);
					break;
				case 1:
					sound = createSoundHandle("red_knight/RedKnight_Death_1.wav", false, true, e->m_startPos);
					break;
				case 2:
					sound = createSoundHandle("red_knight/RedKnight_Death_2.wav", false, true, e->m_startPos);
					break;
				}
				break;
			case Hero::ENGINEER:
				switch(random(0, 2))
				{
				case 0:
					sound = createSoundHandle("engineer/Engineer_Death_0.wav", false, true, e->m_startPos);
					break;
				case 1:
					sound = createSoundHandle("engineer/Engineer_Death_1.wav", false, true, e->m_startPos);
					break;
				case 2:
					sound = createSoundHandle("engineer/Engineer_Death_2.wav", false, true, e->m_startPos);
					break;
				}
				break;
			case Hero::THE_MENTALIST:
				switch(random(0, 2))
				{
				case 0:
					sound = createSoundHandle("mentalist/Mentalist_Death_0.wav", false, true, e->m_startPos);
					break;
				case 1:
					sound = createSoundHandle("mentalist/Mentalist_Death_1.wav", false, true, e->m_startPos);
					break;
				case 2:
					sound = createSoundHandle("mentalist/Mentalist_Death_2.wav", false, true, e->m_startPos);
					break;
				}
				break;
			case Hero::OFFICER:
				switch(random(0, 2))
				{
				case 0:
					sound = createSoundHandle("officer/Officer_Death_0.wav", false, true, e->m_startPos);
					break;
				case 1:
					sound = createSoundHandle("officer/Officer_Death_1.wav", false, true, e->m_startPos);
					break;
				case 2:
					sound = createSoundHandle("officer/Officer_Death_2.wav", false, true, e->m_startPos);
					break;
				}
				break;
			case Hero::DOCTOR:
				switch(random(0, 2))
				{
				case 0:
					sound = createSoundHandle("doctor/Doctor_Death_0.wav", false, true, e->m_startPos);
					break;
				case 1:
					sound = createSoundHandle("doctor/Doctor_Death_1.wav", false, true, e->m_startPos);
					break;
				case 2:
					sound = createSoundHandle("doctor/Doctor_Death_2.wav", false, true, e->m_startPos);
					break;
				}
				break;
			}
			break;

		case ServerEntity::EnemyType:
			switch(e->m_subtype)
			{
			case Enemy::IMP:
				sound = createSoundHandle("enemy/Monster_Imp_Death_0.wav", false, true, e->m_startPos);
				break;
			case Enemy::SHADE:
				sound = createSoundHandle("enemy/Monster_Shade_Death_0.wav", false, true, e->m_startPos);
				break;
			case Enemy::FROST_DEMON:
				sound = createSoundHandle("enemy/Monster_Frost_Death_0.wav", false, true, e->m_startPos);
				break;
			case Enemy::SPITTING_DEMON:
				sound = createSoundHandle("enemy/Monster_Spitting_Death_0.wav", false, true, e->m_startPos);
				break;
			case Enemy::HELLFIRE_STEED:
				sound = createSoundHandle("enemy/Beast_Dying_0.wav", false, true, e->m_startPos);
				break;
			case Enemy::SOUL_EATER_STEED:
				sound = createSoundHandle("enemy/Beast_Dying_0.wav", false, true, e->m_startPos);
				break;
			case Enemy::THUNDERSTEED:
				sound = createSoundHandle("enemy/Beast_Dying_0.wav", false, true, e->m_startPos);
				break;
			case Enemy::BRUTE_STEED:
				sound = createSoundHandle("enemy/Beast_Dying_0.wav", false, true, e->m_startPos);
				break;
			case Enemy::BOSS:
				sound = createSoundHandle("enemy/Beast_Dying_0.wav", false, true, e->m_startPos);
				break;
			}
			break;
		}

		SpeechManager::speakUltimate(_masterId, sound);
		deactivateSound(sound);
	}
}

DeathClientSkillEffect::~DeathClientSkillEffect()
{
	if(this->m_model != NULL)
	{
		g_graphicsEngine->removeModel(this->m_model);
	}
		
	if(this->m_lanternLight != NULL)
	{
		g_graphicsEngine->removePointLight(this->m_lanternLight);
	}
}

void DeathClientSkillEffect::update(float dt)
{
	this->m_lifetime = this->m_lifetime - dt;

	if(this->m_lifetime < 1.5f)
	{
		if(this->m_sink == true)
		{
			FLOAT3 pos = this->m_model->getPosition();
			pos.y = pos.y - dt;
			this->m_model->setPosition(pos);
		}
	}

	if(this->m_lanternLight != NULL)
	{
		this->m_lanternLight->setPosition(this->m_model->getLeftHandPosition(), FLOAT3(0.0f, 1.0f, 0.0f));
		this->m_lanternLight->setDiffuseColor(this->m_originalDiffuse - (this->m_originalDiffuse / 5.0f) * dt);
		this->m_lanternLight->setSpecularColor(this->m_originalSpecular - (this->m_originalSpecular / 5.0f) * dt);
	}
}

bool DeathClientSkillEffect::getActive()
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