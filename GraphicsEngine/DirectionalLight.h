#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "stdafx.h"
#include "DataStructures.h"

class DirectionalLight
{
private:
	FLOAT3 m_direction;
	FLOAT3 m_la;
	FLOAT3 m_ld;
	FLOAT3 m_ls;
public:
	DirectionalLight();
	DirectionalLight(FLOAT3 _direction, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls);

	DECLDIR FLOAT3 getDirection();
	DECLDIR FLOAT3 getAmbientColor();
	DECLDIR FLOAT3 getDiffuseColor();
	DECLDIR FLOAT3 getSpecularColor();

	DECLDIR void setDirection(FLOAT3 _direction);
	DECLDIR void setAmbientColor(FLOAT3 _la);
	DECLDIR void setDiffuseColor(FLOAT3 _ld);
	DECLDIR void setSpecularColor(FLOAT3 _ls);
};

#endif