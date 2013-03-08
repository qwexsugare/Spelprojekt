#pragma once

#include "Graphics.h"
#include "ServerEntity.h"
#include "ModelIdHolder.h"
#include "Enemy.h"

struct Entity
{
	unsigned int m_id;
	unsigned int m_health;
	Model* m_model;
	FLOAT3 m_direction;
	ServerEntity::Type m_type;
	int m_subtype;
	FLOAT3 m_startPos;
	FLOAT3 m_endPos;
	float movementSpeed;
	PointLight *m_lanternLight;
	unsigned int m_weapon;

	Entity()
	{
		this->m_model = NULL;
	}

	Entity(Model* _model, unsigned int _id, ServerEntity::Type _type, int _subtype)
	{
		m_subtype = _subtype;
		m_type = _type;
		if(m_type == ServerEntity::EnemyType && m_subtype == Enemy::SHADE)
		{
			_model->setAlpha(0.75f);
		}

		this->m_model = _model;
		this->m_id = _id;
		this->m_direction = FLOAT3(0.0f, 0.0f, 0.0f);
		this->m_weapon = ModelIdHolder::NO_WEAPON;
		m_startPos=this->m_model->getPosition();
		m_endPos=this->m_model->getPosition();
		this->movementSpeed=1;
		m_health=100;

		if(this->m_model->getLeftHand() != NULL)
		{
			this->m_lanternLight = g_graphicsEngine->createPointLight(this->m_model->getPosition() + FLOAT3(0.0f, 1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false, FLOAT3(0.0f, 1.0f, 0.0f));
			this->m_model->setShadow(true);
		}
		else
		{
			this->m_lanternLight = NULL;
		}
	}

	void update(float dt)
	{
		float xdir=0;
		float zdir=0;
		
		this->m_type;
		if((this->m_model->getPosition() - this->m_endPos).length() > (this->m_direction * dt).length())
		{
			xdir=(m_endPos.x - this->m_model->getPosition().x)/(m_endPos - this->m_model->getPosition()).length()*movementSpeed;
			zdir=(m_endPos.z - this->m_model->getPosition().z)/(m_endPos - this->m_model->getPosition()).length()*movementSpeed;
			float d = atan2(-xdir, -zdir);
			FLOAT3 rot=FLOAT3(d,0.0f,0.0f);
			this->m_model->setRotation(rot);
			this->m_direction.x=xdir;
			this->m_direction.z=zdir;
			this->m_model->setPosition(this->m_model->getPosition()+this->m_direction * dt);
		}
		else
		{
			//xdir=0;
			//zdir=0;
			//this->m_direction.x=xdir;
			//this->m_direction.z=zdir;
			//this->m_model->setPosition(m_endPos);
		}

		if(this->m_lanternLight != NULL)
		{
			this->m_lanternLight->setPosition(this->m_model->getLeftHandPosition(), FLOAT3(0.0f, 1.0f, 0.0f));
		}
	
		
		
	/*
		if((m_endPos - m_startPos).length() > 0)
		{
			this->m_direction.x=(m_endPos.x - this->m_model->getPosition().x)/(m_endPos - this->m_model->getPosition()).length()*movementSpeed;
			this->m_direction.z=(m_endPos.z - this->m_model->getPosition().z)/(m_endPos - this->m_model->getPosition()).length()*movementSpeed;	
			float d = atan2(-this->m_direction.x, -this->m_direction.z);
			FLOAT3 rot=FLOAT3(d,0.0f,0.0f);
			this->m_model->setRotation(rot);

			if((this->m_model->getPosition() - this->m_endPos).length() > (this->m_direction * dt).length())
			{
				this->m_model->setPosition(this->m_model->getPosition()+this->m_direction * dt);
			}
			else
			{
				this->m_model->setPosition(this->m_endPos);
			}
		}
		*/
	}
};