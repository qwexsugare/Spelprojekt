#include "DeathPulseTurret.h"
#include "Graphics.h"

DeathPulseTurret::DeathPulseTurret()
{

}

DeathPulseTurret::DeathPulseTurret(FLOAT3 _pos)
{
	Model* temp = g_graphicsEngine->createModel("DeathTurret", _pos);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
}

DeathPulseTurret::~DeathPulseTurret(void)
{

}
