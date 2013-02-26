#include "FrostTurret.h"
#include "Graphics.h"

FrostTurret::FrostTurret()
{

}

FrostTurret::FrostTurret(FLOAT3 _pos)
{
	Model* temp = g_graphicsEngine->createModel("FrostTurret", _pos);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
}

FrostTurret::~FrostTurret()
{

}
