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
	this->m_particleTail = NULL;
	this->m_deathTime = 1;

	Entity* master = ClientEntityHandler::getEntity(_masterId);
	Entity* target = ClientEntityHandler::getEntity(_targetId);
	if(master != NULL && target != NULL)
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
	}
	if(this->m_particleSystem)
	{
		g_graphicsEngine->removeParticleEngine(this->m_particleSystem);
	}
	if(this->m_particleTail)
	{
		g_graphicsEngine->removeParticleEngine(this->m_particleTail);
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
				FLOAT3 dist = target->m_model->getPosition()-master->m_model->getRightHandPosition();
				FLOAT3 movement = dist/dist.length();
				this->m_pos = master->m_model->getRightHandPosition() + movement;
				this->m_pos.y = 0.5f;

				if(master->m_type == ServerEntity::HeroType)
				{				
					this->m_graphicalEffect = g_graphicsEngine->createModel("Arrow", this->m_pos);
					this->m_graphicalEffect->setAlpha(0.0f);
					this->m_graphicalEffect->move(movement * 0.1f);
					this->m_graphicalEffect->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));

					this->m_particleSystem = g_graphicsEngine->createParticleEngine("Bullet", D3DXVECTOR4(m_graphicalEffect->getPosition().toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1.0f, 1.0f));
				}
				else if(master->m_type == ServerEntity::EnemyType)
				{
					D3DXVECTOR3 newPos = master->m_model->getRightHandPosition().toD3DXVector();
					switch(master->m_subtype)
					{
					case Enemy::SPITTING_DEMON:
						this->m_particleSystem = g_graphicsEngine->createParticleEngine("DeamonSpit", D3DXVECTOR4(this->m_pos.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1.0f, 1.0f));
						break;
					case Enemy::FROST_DEMON:
						this->m_particleSystem = g_graphicsEngine->createParticleEngine("Frost", D3DXVECTOR4(this->m_pos.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1.0f, 1.0f));
						this->m_particleTail = g_graphicsEngine->createParticleEngine("FrostTail", D3DXVECTOR4(this->m_pos.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1.0f, 1.0f));
						break;
					case Enemy::HELLFIRE_STEED:
						this->m_particleTail = g_graphicsEngine->createParticleEngine("HellFireTail", D3DXVECTOR4(this->m_pos.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1.0f, 1.0f));
						break;
					case Enemy::THUNDERSTEED:
						this->m_particleSystem = g_graphicsEngine->createParticleEngine("test", D3DXVECTOR4(this->m_pos.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1.0f, 1.0f));
						this->m_particleTail = g_graphicsEngine->createParticleEngine("test3", D3DXVECTOR4(this->m_pos.toD3DXVector(), 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1.0f, 1.0f));
						break;
					default:
						break;
					}
				}
			}
		}
	}
	else if(target && target->m_health > 0)
	{
		FLOAT3 dist = target->m_model->getPosition()-this->m_pos;
		FLOAT3 movement = dist/dist.length()*RangedAttack::VELOCITY*_dt;
		this->m_pos = this->m_pos + movement;

		if(dist.length() > movement.length())
		{
			if(this->m_graphicalEffect)
			{
				m_graphicalEffect->move(movement);
				m_graphicalEffect->setRotation(FLOAT3(atan2(-movement.x, -movement.z), 0.0f, 0.0f));
			}

			if(this->m_particleSystem)
			{
				D3DXVECTOR3 incY(0, 0.5f, 0);
				D3DXVECTOR3 newPos = D3DXVECTOR3(this->m_particleSystem->getPosition().x,this->m_particleSystem->getPosition().y, this->m_particleSystem->getPosition().z) + movement.toD3DXVector();
				this->m_particleSystem->setPosition(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z) + incY);
			}
			if(this->m_particleTail)
			{				
				D3DXVECTOR3 incY(0, 0.5f, 0);
				D3DXVECTOR3 newPos = D3DXVECTOR3(this->m_particleTail->getPosition().x,this->m_particleTail->getPosition().y, this->m_particleTail->getPosition().z) + movement.toD3DXVector();
				this->m_particleTail->setPosition(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z) + incY);
			}
		}
		else
		{	
			if(m_particleSystem)
				m_particleSystem->setAlive(false);
			if(m_particleTail)
				m_particleTail->setAlive(false);

			m_deathTime -= _dt;
			if(m_deathTime <= 0)
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