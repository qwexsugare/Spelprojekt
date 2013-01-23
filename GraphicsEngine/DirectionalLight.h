#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "stdafx.h"
#include "DataStructures.h"

class DirectionalLight
{
private:
	FLOAT3 m_direction;
	FLOAT4 m_la;
	FLOAT4 m_ld;
	FLOAT4 m_ls;
public:
	DirectionalLight();
	DirectionalLight(FLOAT3 _direction, FLOAT4 _la, FLOAT4 _ld, FLOAT4 _ls);

	DECLDIR FLOAT3 getDirection();
	DECLDIR FLOAT4 getAmbientColor();
	DECLDIR FLOAT4 getDiffuseColor();
	DECLDIR FLOAT4 getSpecularColor();

	DECLDIR void setDirection(FLOAT3 _direction);
	DECLDIR void setAmbientColor(FLOAT4 _la);
	DECLDIR void setDiffuseColor(FLOAT4 _ld);
	DECLDIR void setSpecularColor(FLOAT4 _ls);
};

#endif