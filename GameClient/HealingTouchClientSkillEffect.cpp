#include "HealingTouchClientSkillEffect.h"
#include "SoundWrapper.h"
#include "Graphics.h"

HealingTouchClientSkillEffect::HealingTouchClientSkillEffect(FLOAT3 _position, unsigned int casterId, unsigned int _targetId)
{
	m_position = _position;
	m_lifetime = 0.0f;
	m_casterId = casterId;
	m_targetId = _targetId;
	
	int sound = createSoundHandle("skills/healingTouch.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);

	Entity *e = ClientEntityHandler::getEntity(casterId);
	if(e != NULL)
	{
		e->m_model->getAnimation()->Play("Spell");
		this->m_weapon = e->m_model->getRightHand();
		e->m_model->SetRightHand(NULL);
	}

	Entity *t = ClientEntityHandler::getEntity(_targetId);
	if(t != NULL)
	{
		m_heal = g_graphicsEngine->createParticleEngine("Heal", D3DXVECTOR4(0, 0, 0, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
	}
}

HealingTouchClientSkillEffect::~HealingTouchClientSkillEffect()
{
	Entity *t = ClientEntityHandler::getEntity(m_targetId);
	if(t != NULL)
	{
		g_graphicsEngine->removeParticleEngine(m_heal);
	}
}

void HealingTouchClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;

	Entity *t = ClientEntityHandler::getEntity(m_targetId);
	if(m_heal != NULL && t != NULL)
	{
		if(m_lifetime >= 2)
		{
			m_heal->setAlive(false);	
			Entity *e = ClientEntityHandler::getEntity(m_casterId);
			if(e != NULL)
			{
				e->m_model->SetRightHand(this->m_weapon);
			}
		}
		m_heal->setPosition(t->m_model->getPosition().toD3DXVector());
	}
}

bool HealingTouchClientSkillEffect::getActive()
{
	if(m_lifetime >= 4)
		return false;
	else
		return true;
}