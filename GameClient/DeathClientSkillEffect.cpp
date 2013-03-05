#include "DeathClientSkillEffect.h"

DeathClientSkillEffect::DeathClientSkillEffect(unsigned int _masterId, FLOAT3 _position)
{
	this->m_masterId = _masterId;
	this->m_lifetime = 5.0f;
	this->m_sink = false;
	this->m_model = NULL;
	this->m_lanternLight = NULL;

	Entity *e = ClientEntityHandler::getEntity(this->m_masterId);

	if(e->m_type == ServerEntity::EnemyType)
	{
		this->m_sink = true;
	}

	//g_graphicsEngine->createPointLight(_position, FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false, FLOAT3(0.0f, 1.0f, 0.0f));

	if(e != NULL)
	{
		this->m_model = g_graphicsEngine->createModel(e->m_model, false);
		this->m_model->setPosition(_position);
		this->m_model->getAnimation()->Play("death", true);
		this->m_model->SetHat(e->m_model->getHat());
		this->m_model->SetLeftHand(e->m_model->getLeftHand());
		this->m_model->SetRightHand(e->m_model->getRightHand());

		if(e->m_lanternLight != NULL)
		{
			this->m_lanternLight = g_graphicsEngine->createPointLight(this->m_model->getLeftHandPosition(), e->m_lanternLight->getAmbientColor(), e->m_lanternLight->getDiffuseColor(), e->m_lanternLight->getSpecularColor(), e->m_lanternLight->getRadius(), true, false, FLOAT3(0.0f, 1.0f, 0.0f));
			this->m_originalDiffuse = this->m_lanternLight->getDiffuseColor();
			this->m_originalSpecular = this->m_lanternLight->getSpecularColor();
		}
	}
}

DeathClientSkillEffect::~DeathClientSkillEffect()
{

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
		g_graphicsEngine->removeModel(this->m_model);
		
		if(this->m_lanternLight != NULL)
		{
			g_graphicsEngine->removePointLight(this->m_lanternLight);
		}

		return false;
	}
	else
	{
		return true;
	}
}