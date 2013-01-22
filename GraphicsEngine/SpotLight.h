#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "stdafx.h"
#include "DataStructures.h"

class SpotLight
{
private:
	FLOAT3 m_position;
	FLOAT3 m_direction;
	FLOAT3 m_la;
	FLOAT3 m_ld;
	FLOAT3 m_ls;
	FLOAT2 m_angle;
public:
	SpotLight();
	SpotLight(FLOAT3 _position, FLOAT3 _direction, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls, FLOAT2 _angle);

	DECLDIR FLOAT3 getPosition();
	DECLDIR FLOAT3 getDirection();
	DECLDIR FLOAT3 getAmbientColor();
	DECLDIR FLOAT3 getDiffuseColor();
	DECLDIR FLOAT3 getSpecularColor();
	DECLDIR FLOAT2 getAngle();
	
	DECLDIR void setPosition(FLOAT3 _position);
	DECLDIR void setDirection(FLOAT3 _direction);
	DECLDIR void setAmbientColor(FLOAT3 _la);
	DECLDIR void setDiffuseColor(FLOAT3 _ld);
	DECLDIR void setSpecularColor(FLOAT3 _ls);
	DECLDIR void setAngle(FLOAT2 _angle);
};

#endif
