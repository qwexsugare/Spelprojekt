#include "PoisonTurret.h"
#include "Graphics.h"

PoisonTurret::PoisonTurret()
{

}

PoisonTurret::PoisonTurret(FLOAT3 _pos) : Turret(_pos)
{
	this->m_modelId = 2;
	
	Model* temp = g_graphicsEngine->createModel("PoisonTurret", _pos);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
}


PoisonTurret::~PoisonTurret()
{

}
