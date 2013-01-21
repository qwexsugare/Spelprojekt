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
	float m_radius;
public:
	PointLight();
	PointLight(FLOAT3 _position, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls, float _radius);

	DECLDIR FLOAT3 getPosition();
	DECLDIR FLOAT3 getAmbientColor();
	DECLDIR FLOAT3 getDiffuseColor();
	DECLDIR FLOAT3 getSpecularColor();
	DECLDIR float getRadius();

	DECLDIR void setPosition(FLOAT3 _position);
	DECLDIR void setAmbientColor(FLOAT3 _la);
	DECLDIR void setDiffuseColor(FLOAT3 _ld);
	DECLDIR void setSpecularColor(FLOAT3 _ls);
	DECLDIR void setRadius(float _radius);
};

#endif