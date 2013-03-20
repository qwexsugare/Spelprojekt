#include "SimonsEvilEffect.h"
#include "EntityHandler.h"
#include "Graphics.h"
#include "Hero.h"
#include "Skill.h"

SimonsEvilEffect::SimonsEvilEffect(unsigned int _caster)
{
	m_heal = ((Hero*)EntityHandler::getServerEntity(_caster))->getWits()*5;
	m_ticks = 0;
	m_caster = _caster;
	m_damage = ((Hero*)EntityHandler::getServerEntity(_caster))->getWits()*DPS;
	
	this->m_obb = NULL;
	Model *m = g_graphicsEngine->createModel("CloudOfDarkness", this->m_position);
	this->m_bs = new BoundingSphere(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), m->getBs()->Radius);
	g_graphicsEngine->removeModel(m);
	m_visible = false;
	m_timer = 0.0f;
	m_type = OtherType;

	this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::SIMONS_EVIL, 0, m_caster, FLOAT3(0.0f, 0.0f, 0.0f)));
}

SimonsEvilEffect::~SimonsEvilEffect()
{

}

void SimonsEvilEffect::tick()
{
	vector<ServerEntity*> enemies = EntityHandler::getAllEnemies();

	for(int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i]->contains(*m_bs))
		{
			((UnitEntity*)enemies[i])->takeDamage(this->m_caster, 0, m_damage);
		}
	}
	
	vector<ServerEntity*> heroes = EntityHandler::getAllHeroes();

	for(int i = 0; i < heroes.size(); i++)
	{
		if(heroes[i]->contains(*m_bs))
		{
			((UnitEntity*)heroes[i])->heal(m_heal);
		}
	}

	m_ticks++;
}

void SimonsEvilEffect::update(float _dt)
{
	m_timer += _dt;
	
	FLOAT3 pos = EntityHandler::getServerEntity(m_caster)->getPosition();
	m_bs->Center = XMFLOAT3(pos.x, pos.y, pos.z);

	if(m_timer >= LIFETIME)
	{
		tick();
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
	else if(m_timer > m_ticks+1)
	{
		tick();
	}
}