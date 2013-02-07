#include "CloudOfDarknessEffect.h"
#include "EntityHandler.h"
#include "Graphics.h"

CloudOfDarknessEffect::CloudOfDarknessEffect(FLOAT3 _position, int _damage)
{
	m_damage = _damage;
	m_position = _position;

	this->m_obb = NULL;
	Model *m = g_graphicsEngine->createModel("CloudOfDarkness", this->m_position);
	this->m_bs = new BoundingSphere(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), m->getBs()->Radius*0.5f);
	g_graphicsEngine->removeModel(m);
	m_visible = false;
	m_timer = 0.0f;
	m_type = OtherType;

	vector<ServerEntity*> enemies = EntityHandler::getAllEnemies();

	for(int i = 0; i < enemies.size(); i++)
	{
		ServerEntity* enemy = enemies[i];
		if(enemy->getObb())
		{
			if(enemy->getObb()->Intersects(*m_bs))
			{
				this->dealDamage((enemies)[i], this->m_damage, false);
			}
		}
		else if(enemy->getBs())
		{
			if(enemy->getBs()->Intersects(*m_bs))
			{
				this->dealDamage((enemies)[i], this->m_damage, false);
			}
		}
	}
}

CloudOfDarknessEffect::~CloudOfDarknessEffect()
{

}

void CloudOfDarknessEffect::update(float _dt)
{
	m_timer += _dt;

	if(m_timer > LIFETIME)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}