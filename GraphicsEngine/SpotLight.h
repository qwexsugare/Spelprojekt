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
	float m_angle;
public:
	SpotLight();
	SpotLight(FLOAT3 _position, FLOAT3 _direction, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls, float _angle);

	DECLDIR FLOAT3 getPosition();
	DECLDIR FLOAT3 getDirection();
	DECLDIR FLOAT3 getAmbient();
	DECLDIR FLOAT3 getDiffuse();
	DECLDIR FLOAT3 getSpecular();
	DECLDIR float getAngle();
	
	DECLDIR void setPosition(FLOAT3 _position);
	DECLDIR void setDirection(FLOAT3 _direction);
	DECLDIR void setAmbient(FLOAT3 _la);
	DECLDIR void setDiffuse(FLOAT3 _ld);
	DECLDIR void setSpeculat(FLOAT3 _ls);
	DECLDIR void setAngle(float _angle);
};

#endif
