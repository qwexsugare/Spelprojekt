#include "SpotLight.h"

SpotLight::SpotLight()
{

}

SpotLight::SpotLight(FLOAT3 _position, FLOAT3 _direction, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls, float _angle)
{
	this->m_position = _position;
	this->m_direction = _direction;
	this->m_la = _la;
	this->m_ld = _ld;
	this->m_ls = _ls;
	this->m_angle = _angle;
}

FLOAT3 SpotLight::getPosition()
{
	return this->m_position;
}

FLOAT3 SpotLight::getDirection()
{
	return this->m_direction;
}

FLOAT3 SpotLight::getAmbient()
{
	return this->m_la;
}

FLOAT3 SpotLight::getDiffuse()
{
	return this->m_ld;
}

FLOAT3 SpotLight::getSpecular()
{
	return this->m_ls;
}

float SpotLight::getAngle()
{
	return this->m_angle;
}
	
void SpotLight::setPosition(FLOAT3 _position)
{
	this->m_position = _position;
}

void SpotLight::setDirection(FLOAT3 _direction)
{
	this->m_direction = _direction;
}

void SpotLight::setAmbient(FLOAT3 _la)
{
	this->m_la = _la;
}

void SpotLight::setDiffuse(FLOAT3 _ld)
{
	this->m_ld = _ld;
}

void SpotLight::setSpeculat(FLOAT3 _ls)
{
	this->m_ls = _ls;
}

void SpotLight::setAngle(float _angle)
{
	this->m_angle = _angle;
}