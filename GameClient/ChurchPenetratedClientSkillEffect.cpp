#include "ChurchPenetratedClientSkillEffect.h"
#include "SoundWrapper.h"

ChurchPenetratedClientSkillEffect::ChurchPenetratedClientSkillEffect(unsigned int _id, FLOAT3 _position)
{
	timer = 0.0f;
	D3DXVECTOR4 newPos = D3DXVECTOR4(_position.x, _position.y, _position.z, 1);
	pe = g_graphicsEngine->createParticleEngine("ChurchPen",newPos,D3DXQUATERNION(0, 0, 0, 1),D3DXVECTOR2(1, 1));
	this->id = _id;
}

ChurchPenetratedClientSkillEffect::~ChurchPenetratedClientSkillEffect()
{
	g_graphicsEngine->removeParticleEngine(pe);
}

void ChurchPenetratedClientSkillEffect::update(float _dt)
{
	timer+=_dt;

	Entity *e = ClientEntityHandler::getEntity(this->id);

	if(e != NULL)
	{
		this->pe->setPosition(e->m_model->getPosition().toD3DXVector());
	}
}

bool ChurchPenetratedClientSkillEffect::getActive()
{
	if(timer >= 2.0f)
	{
		return false;
	}
	else
	{
		return true;
	}
}