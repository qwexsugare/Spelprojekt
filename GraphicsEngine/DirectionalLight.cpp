#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	this->m_direction = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_la = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_ld = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_ls = FLOAT3(0.0f, 0.0f, 0.0f);
}

DirectionalLight::DirectionalLight(FLOAT3 _direction, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls)
{
	this->m_direction = _direction;
	this->m_la = _la;
	this->m_ld = _ld;
	this->m_ls = _ls;
}

FLOAT3 DirectionalLight::getDirection()
{
	return this->m_direction;
}

FLOAT3 DirectionalLight::getAmbientColor()
{
	return this->m_la;
}

FLOAT3 DirectionalLight::getDiffuseColor()
{
	return this->m_ld;
}

FLOAT3 DirectionalLight::getSpecularColor()
{
	return this->m_ls;
}

void DirectionalLight::setDirection(FLOAT3 _direction)
{
	this->m_direction = _direction;
}

void DirectionalLight::setAmbientColor(FLOAT3 _la)
{
	this->m_la = _la;
}

void DirectionalLight::setDiffuseColor(FLOAT3 _ld)
{
	this->m_ld = _ld;
}

void DirectionalLight::setSpecularColor(FLOAT3 _ls)
{
	this->m_ls = _ls;
}