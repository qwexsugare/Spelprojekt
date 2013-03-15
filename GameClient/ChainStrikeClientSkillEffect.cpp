#include "ChainStrikeClientSkillEffect.h"
#include "SoundWrapper.h"
#include "ChainStrikeEffect.h"
#include "Graphics.h"

#include <sstream>
ChainStrikeClientSkillEffect::ChainStrikeClientSkillEffect(unsigned int _lastTarget, unsigned int _target, FLOAT3 _position)
{
	//m_graphicalEffects[0] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.1f, _position.z), "color2");
	//m_graphicalEffects[1] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.2f, _position.z), "color1");
	//m_graphicalEffects[2] = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3(_position.x, 0.3f, _position.z), "color");
	//m_graphicalEffects[0]->setScale(0.5f, 0.5f, 0.5f);
	//m_graphicalEffects[2]->setScale(0.5f, 0.5f, 0.5f);
	//m_graphicalEffects[1]->setScale(0.5f, 0.5f, 0.5f);
	//m_graphicalEffects[0]->setAlpha(0.999f);
	//m_graphicalEffects[1]->setAlpha(0.999f);
	//m_graphicalEffects[2]->setAlpha(0.999f);
	m_superPos = _position;
	m_lifetime = 0.0f;

	this->m_lastTarget = _lastTarget;
	this->m_target = _target;

	m_chainEffect = g_graphicsEngine->createChainEffect();

	int sound = createSoundHandle("skills/chain_strike.wav", false, true, _position);
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
}

ChainStrikeClientSkillEffect::~ChainStrikeClientSkillEffect()
{
	//g_graphicsEngine->removeModel(m_graphicalEffects[0]);
	//g_graphicsEngine->removeModel(m_graphicalEffects[1]);
	//g_graphicsEngine->removeModel(m_graphicalEffects[2]);
	g_graphicsEngine->removeChainEffect(m_chainEffect);
}

void ChainStrikeClientSkillEffect::update(float _dt)
{
	m_lifetime += _dt;

	m_eOrig = ClientEntityHandler::getEntity(m_lastTarget);
	m_eTarget = ClientEntityHandler::getEntity(m_target);

	if(m_eOrig)
		m_chainEffect->setOrig(D3DXVECTOR3(m_eOrig->m_model->getPosition().x, m_eOrig->m_model->getPosition().y, m_eOrig->m_model->getPosition().z));
		//m_chainEffect->setOrig(D3DXVECTOR3(m_superPos.x, m_superPos.y + 0.2f,m_superPos.z));
	//else
		//m_lifetime = ChainStrikeEffect::TIME_BETWEEN_JUMPS;
	if(m_eTarget)
		//m_chainEffect->setTarget(D3DXVECTOR3(m_eTarget->m_model->getPosition().x, m_eTarget->m_model->getPosition().y + 0.2f, m_eTarget->m_model->getPosition().z));
		m_chainEffect->setTarget(D3DXVECTOR3(m_superPos.x, m_superPos.y, m_superPos.z));
	

	m_chainEffect->setCamPos(g_graphicsEngine->getCamera()->getPos());
	m_chainEffect->setViewProj(g_graphicsEngine->getCamera()->getViewProjectionMatrix());
}

bool ChainStrikeClientSkillEffect::getActive()
{
	if(m_lifetime >= ChainStrikeEffect::TIME_BETWEEN_JUMPS)
		return false;
	else
		return true;
}