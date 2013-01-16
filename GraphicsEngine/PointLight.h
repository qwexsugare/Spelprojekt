#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "stdafx.h"
#include "DataStructures.h"

class PointLight
{
private:
	FLOAT3 m_position;
	FLOAT4 m_la;
	FLOAT4 m_ld;
	FLOAT4 m_ls;
public:
	PointLight();
	PointLight(FLOAT3 _position, FLOAT4 _la, FLOAT4 _ld, FLOAT4 _ls);

	DECLDIR FLOAT3 getPosition();
	DECLDIR FLOAT4 getAmbientColor();
	DECLDIR FLOAT4 getDiffuseColor();
	DECLDIR FLOAT4 getSpecularColor();

	DECLDIR void setPosition(FLOAT3 _position);
	DECLDIR void setAmbientColor(FLOAT4 _la);
	DECLDIR void setDiffuseColor(FLOAT4 _ld);
	DECLDIR void setSpecularColor(FLOAT4 _ls);
};

#endif