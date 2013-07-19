#include "CloudOfDarknessEffect.h"
#include "EntityHandler.h"
#include "Graphics.h"
#include "Skill.h"

CloudOfDarknessEffect::CloudOfDarknessEffect(FLOAT3 _position, int _damage, unsigned int _masterId)
{
	m_damage = _damage/LIFETIME; // /LIFETIME is a cheat so that the programmer defining the damage doesnt need to think about dividing it into per second
	m_position = _position;

	this->m_obb = NULL;
	Model *m = g_graphicsEngine->createModel("CloudOfDarkness", this->m_position);
	this->m_bs = new BoundingSphere(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), m->getBs()->Radius*0.5f);
	g_graphicsEngine->removeModel(m);
	m_visible = false;
	m_timer = 0.0f;
	m_type = OtherType;

	this->m_messageQueue->pushOutgoingMessage(new CreateActionPositionMessage(Skill::CLOUD_OF_DARKNESS, _masterId, _position));
}

CloudOfDarknessEffect::~CloudOfDarknessEffect()
{

}

void CloudOfDarknessEffect::tick()
{
	vector<ServerEntity*> enemies = EntityHandler::getEntitiesByType(Type::EnemyType);
	for(int i = 0; i < enemies.size(); i++)
	{
		ServerEntity* enemy = enemies[i];
		if(enemy->intersects(*m_bs))
		{
			enemy->takeDamage(this->getId(), m_damage*0.5f, 0);
		}
	}
}

void CloudOfDarknessEffect::update(float _dt)
{
	m_timer += _dt;

	if(m_timer < LIFETIME)
	{
		m_ticker += _dt;
		if(m_ticker >= 0.5f)
		{
			tick();
			m_ticker-=0.5f;
		}
	}
	else
	{
		tick();

		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}