#include "ArrowClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"
#include "ClientEntityHandler.h"
#include "RangedAttack.h"
#include "SpeechManager.h"
#include "MyAlgorithms.h"

ArrowClientSkillEffect::ArrowClientSkillEffect(FLOAT3 _position, unsigned int _targetId, unsigned int _masterId, float _animationSpeed)
{
	m_active = true;
	m_targetId = _targetId;
	this->m_masterId = _masterId;
	this->m_aimTime = 1.0f / _animationSpeed;
	this->m_graphicalEffect = NULL;
	this->m_particleSystem = NULL;

	Entity* master = ClientEntityHandler::getEntity(_masterId);
	if(master != NULL)
	{
		master->m_model->getAnimation()->PlayLoop("RangeAttack", -1, _animationSpeed);
	}

	// Play sound
	int sound;
	switch(random(0, 2))
	{
	case 0:
		sound = createSoundHandle("attacks/rangeAttack_0", false, true, _position);
		break;
	case 1:
		sound = createSoundHandle("attacks/rangeAttack_1", false, true, _position);
		break;
	case 2:
		sound = createSoundHandle("attacks/rangeAttack_2", false, true, _position);
		break;
	}
	playSound(sound);
	deactivateSound(sound);
}

ArrowClientSkillEffect::~ArrowClientSkillEffect()
{
	if(m_graphicalEffect)
	{
		g_graphicsEngine->removeModel(m_graphicalEffect);
		g_graphicsEngine->removeParticleEngine(this->m_particleSystem);
	}
}

void ArrowClientSkillEffect::update(float _dt)
{
	Entity* target = ClientEntityHandler::getEntity(m_targetId);

	if(this->m_aimTime > 0.0f)
	{
		this->m_aimTime -= _dt;

		if(this->m_aimTime <= 0.0f)
		{
			Entity* master = ClientEntityHandler::getEntity(this->m_masterId);
			if(master != NULL && target != NULL)
			{
				m_graphicalEffect = g_graphicsEngine->createModel("Arrow", master->m_model->getRightHandPosition());
				m_graphicalEffect->setAlpha(0.999f);

				FLOAT3 dist = target->m_model->getPosition()-m_graphicalEffect->getPosition();
				FLOAT3 movement = dist/dist.length();

				this->m_graphicalEffect->move(movement * 0.1f);

				D3DXVECTOR3 newPos = master->m_model->getRightHandPosition().toD3DXVector();
				this->m_particleSystem = g_graphicsEngine->createParticleEngine("DeamonSpit", D3DXVECTOR4(newPos, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1.0f, 1.0f));
			}
		}
	}
	else if(m_graphicalEffect && target && target->m_health > 0)
	{
		D3DXVECTOR3 newPos = D3DXVECTOR3(m_graphicalEffect->getPosition().x, m_graphicalEffect->getPosition().y, m_graphicalEffect->getPosition().z);
		this->m_particleSystem->setPosition(newPos);

		FLOAT3 dist = target->m_model->getPosition()-m_graphicalEffect->getPosition();
		FLOAT3 movement = dist/dist.length()*RangedAttack::VELOCITY*_dt;

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
				deactivateSound(sound);
			}
			else if(target->m_type == UnitEntity::HeroType)
			{
				int sound;

				switch(target->m_subtype)
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
				deactivateSound(sound);
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