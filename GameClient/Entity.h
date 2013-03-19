#pragma once

#include "Graphics.h"
#include "ServerEntity.h"
#include "ModelIdHolder.h"
#include "Enemy.h"

struct Entity
{
	unsigned int m_id;
	int m_health;
	Model* m_model;
	FLOAT3 m_direction;
	ServerEntity::Type m_type;
	int m_subtype;
	FLOAT3 m_startPos;
	FLOAT3 m_endPos;
	float movementSpeed;
	PointLight *m_lanternLight;
	unsigned int m_weapon;
	int m_poisonStacks;
	int m_maxHealth;
	float m_mentalDamage;
	float m_physicalDamage;
	float m_mentalResistance;
	float m_physicalResistance;

	Sprite *m_healthBack;
	Sprite *m_healthFront;

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
		m_health=1000;
		m_poisonStacks = 0;

		if(this->m_type == ServerEntity::EnemyType)
		{
			this->m_model->setColor(D3DXVECTOR4(1, 0, 0, 0.4f));
		}
		else
		{
			this->m_model->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
		}

		if(this->m_type == ServerEntity::HeroType || this->m_type == ServerEntity::EnemyType || m_type == ServerEntity::TowerType)
		{
			FLOAT2 screenPos = this->m_model->getScreenPos(g_graphicsEngine->getCamera()->getViewProjectionMatrix());
			this->m_healthBack = g_graphicsEngine->createSprite("menu_textures/Damage.png", screenPos, FLOAT2(75.0f, 5.0f) / FLOAT2(g_graphicsEngine->getScreenSize().x, g_graphicsEngine->getScreenSize().y), 2);
			this->m_healthFront = g_graphicsEngine->createSprite("menu_textures/Health.png", screenPos, FLOAT2(75.0f, 5.0f) / FLOAT2(g_graphicsEngine->getScreenSize().x, g_graphicsEngine->getScreenSize().y), 2);
		}
		else
		{
			this->m_healthBack = NULL;
			this->m_healthFront = NULL;
		}
		
		if(this->m_model->getRightHand() != NULL)
		{
			this->m_lanternLight = g_graphicsEngine->createPointLight(this->m_model->getPosition() + FLOAT3(0.0f, 1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false, FLOAT3(0.0f, 1.0f, 0.0f));
			this->m_model->setShadow(true);
		}
		else
		{
			this->m_lanternLight = NULL;
		}
	}

	~Entity()
	{
		if(this->m_healthBack != NULL)
		{
			g_graphicsEngine->removeSprite(this->m_healthBack);
			g_graphicsEngine->removeSprite(this->m_healthFront);
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
	
		if((this->m_type == ServerEntity::HeroType || this->m_type == ServerEntity::EnemyType || m_type == ServerEntity::TowerType) && this->m_healthBack->getVisible() == true)
		{		
			//Update the healthbar position
			FLOAT2 screenPos = this->m_model->getScreenPos(g_graphicsEngine->getCamera()->getViewProjectionMatrix());
			float offsetX = (this->m_healthFront->getSize().x - ((float)this->m_health / (float)this->m_maxHealth) * this->m_healthBack->getSize().x) / 2;
			this->m_healthBack->setPosition(screenPos);
			this->m_healthFront->setPosition(FLOAT2(screenPos.x - offsetX, screenPos.y));

			if(this->m_health > 0.0f)
			{
				float width = ((float)this->m_health / (float)this->m_maxHealth) * this->m_healthBack->getSize().x;
				this->m_healthFront->setSize(FLOAT2(width, this->m_healthBack->getSize().y));
			}
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

	void setHealth(float health)
	{
		this->m_health = health;
	}

	void healthVisible(bool _visible)
	{
		this->m_healthBack->setVisible(_visible);
		this->m_healthFront->setVisible(_visible);
	}
};