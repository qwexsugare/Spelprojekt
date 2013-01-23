#include "SpotLight.h"

SpotLight::SpotLight()
{

}

SpotLight::SpotLight(FLOAT3 _position, FLOAT3 _direction, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls, FLOAT2 _angle, float _range)
{
	this->m_position = _position;
	this->m_direction = _direction;
	this->m_la = _la;
	this->m_ld = _ld;
	this->m_ls = _ls;
	this->m_angle = _angle;
	this->m_range = _range;
}

FLOAT3 SpotLight::getPosition()
{
	return this->m_position;
}

FLOAT3 SpotLight::getDirection()
{
	return this->m_direction;
}

FLOAT3 SpotLight::getAmbientColor()
{
	return this->m_la;
}

FLOAT3 SpotLight::getDiffuseColor()
{
	return this->m_ld;
}

FLOAT3 SpotLight::getSpecularColor()
{
	return this->m_ls;
}

FLOAT2 SpotLight::getAngle()
{
	return this->m_angle;
}

float SpotLight::getRange()
{
	return this->m_range;
}
	
void SpotLight::setPosition(FLOAT3 _position)
{
	this->m_position = _position;
}

void SpotLight::setDirection(FLOAT3 _direction)
{
	this->m_direction = _direction;
}

void SpotLight::setAmbientColor(FLOAT3 _la)
{
	this->m_la = _la;
}

void SpotLight::setDiffuseColor(FLOAT3 _ld)
{
	this->m_ld = _ld;
}

void SpotLight::setSpecularColor(FLOAT3 _ls)
{
	this->m_ls = _ls;
}

void SpotLight::setAngle(FLOAT2 _angle)
{
	this->m_angle = _angle;
}

void SpotLight::setRange(float _range)
{
	this->m_range = _range;
}