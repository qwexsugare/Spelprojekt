#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "stdafx.h"
#include "DataStructures.h"

class PointLight
{
private:
	FLOAT3 m_position;
	FLOAT3 m_la;
	FLOAT3 m_ld;
	FLOAT3 m_ls;
public:
	PointLight();
	PointLight(FLOAT3 _position, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls);

	DECLDIR FLOAT3 getPosition();
	DECLDIR FLOAT3 getAmbientColor();
	DECLDIR FLOAT3 getDiffuseColor();
	DECLDIR FLOAT3 getSpecularColor();

	DECLDIR void setPosition(FLOAT3 _position);
	DECLDIR void setAmbientColor(FLOAT3 _la);
	DECLDIR void setDiffuseColor(FLOAT3 _ld);
	DECLDIR void setSpecularColor(FLOAT3 _ls);
};

#endif