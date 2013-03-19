#include "ChainStrikeClientSkillEffect.h"
#include "SoundWrapper.h"
#include "ChainStrikeEffect.h"
#include "Graphics.h"

#include <sstream>
ChainStrikeClientSkillEffect::ChainStrikeClientSkillEffect(unsigned int _lastTarget, unsigned int _target, FLOAT3 _position)
{
	m_superPos = _position;
	m_lifetime = 0.0f;

	this->m_lastTarget = _lastTarget;
	this->m_target = _target;
	this->m_percentToTarget = 0;

	pe[0] = g_graphicsEngine->createParticleEngine("test", D3DXVECTOR4(0, 0, 0, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(2, 2));
	pe[1] = g_graphicsEngine->createParticleEngine("test2", D3DXVECTOR4(0, 0, 0, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(2, 2));
	pe[2] = g_graphicsEngine->createParticleEngine("test3", D3DXVECTOR4(0, 0, 0, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(2, 2));

	int sound = createSoundHandle("skills/chain_strike.wav", false, true, _position, 0.5f);
	playSound(sound);
	deactivateSound(sound);

	Entity *e = ClientEntityHandler::getEntity(_lastTarget);
	if(e != NULL && e->m_type == ServerEntity::HeroType)
	{
		e->m_model->getAnimation()->Play("ChainLight");

		stringstream ss;
		ss << "Dude its a hero that casted chani strike." << endl;
		OutputDebugString(ss.str().c_str());
	}
	if(_lastTarget == _target)
	{
		stringstream ss;
		ss << "Super ultra fail id: " << _target << endl;
		OutputDebugString(ss.str().c_str());
	}
	m_orig = D3DXVECTOR3(0, 0, 0);
	m_eOrig = NULL;
	m_eOrig = ClientEntityHandler::getEntity(m_lastTarget);
	if(m_eOrig)
		m_orig = D3DXVECTOR3(m_eOrig->m_model->getPosition().x, m_eOrig->m_model->getPosition().y, m_eOrig->m_model->getPosition().z);
}

ChainStrikeClientSkillEffect::~ChainStrikeClientSkillEffect()
{
	g_graphicsEngine->removeChainEffect(m_chainEffect);
	g_graphicsEngine->removeParticleEngine(pe[0]);
	g_graphicsEngine->removeParticleEngine(pe[1]);
	g_graphicsEngine->removeParticleEngine(pe[2]);
}

void ChainStrikeClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;

	m_eTarget = ClientEntityHandler::getEntity(m_target);
	
	FLOAT3 myVec = FLOAT3(0, 0, 0);
	if(m_eTarget)
		myVec = m_eTarget->m_model->getPosition() - FLOAT3(m_orig.x, m_orig.y, m_orig.z);

	D3DXVECTOR3 distanceToTarget = D3DXVECTOR3(myVec.x, myVec.y, myVec.z);

	float onePercent = 1.0f/(ChainStrikeEffect::TIME_BETWEEN_JUMPS);
	m_percentToTarget += onePercent * _dt;


	if(m_eOrig)
		//m_chainEffect->setOrig(D3DXVECTOR3(m_eOrig->m_model->getPosition().x, m_eOrig->m_model->getPosition().y, m_eOrig->m_model->getPosition().z));
		//m_chainEffect->setOrig(D3DXVECTOR3(m_superPos.x, m_superPos.y + 0.2f,m_superPos.z));
		pe[0]->setPosition(m_orig + (distanceToTarget*m_percentToTarget));
		pe[1]->setPosition(m_orig + (distanceToTarget*m_percentToTarget));
		pe[2]->setPosition(m_orig + (distanceToTarget*m_percentToTarget));
	//else
		//m_lifetime = ChainStrikeEffect::TIME_BETWEEN_JUMPS;
	//if(m_eTarget)
		//m_chainEffect->setTarget(D3DXVECTOR3(m_eTarget->m_model->getPosition().x, m_eTarget->m_model->getPosition().y + 0.2f, m_eTarget->m_model->getPosition().z));
		//m_chainEffect->setTarget(D3DXVECTOR3(m_superPos.x, m_superPos.y, m_superPos.z));
		//pe[1]->setPosition(D3DXVECTOR3(m_superPos.x, m_superPos.y, m_superPos.z));


	

	//m_chainEffect->setCamPos(g_graphicsEngine->getCamera()->getPos());
	//m_chainEffect->setViewProj(g_graphicsEngine->getCamera()->getViewProjectionMatrix());
}

bool ChainStrikeClientSkillEffect::getActive()
{
	if(m_lifetime >= ChainStrikeEffect::TIME_BETWEEN_JUMPS)
		return false;
	else
		return true;
}