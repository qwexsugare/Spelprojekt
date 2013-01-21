#include "PointLight.h"

PointLight::PointLight()
{
	this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_la = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_ld = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_ls = FLOAT3(0.0f, 0.0f, 0.0f);
}

PointLight::PointLight(FLOAT3 _position, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls, float _radius)
{
	this->m_position = _position;
	this->m_la = _la;
	this->m_ld = _ld;
	this->m_ls = _ls;
	this->m_radius = _radius;
}

FLOAT3 PointLight::getPosition()
{
	return this->m_position;
}

FLOAT3 PointLight::getAmbientColor()
{
	return this->m_la;
}

FLOAT3 PointLight::getDiffuseColor()
{
	return this->m_ld;
}

FLOAT3 PointLight::getSpecularColor()
{
	return this->m_ls;
}

float PointLight::getRadius()
{
	return this->m_radius;
}

void PointLight::setPosition(FLOAT3 _position)
{
	this->m_position = _position;
}

void PointLight::setAmbientColor(FLOAT3 _la)
{
	this->m_la = _la;
}

void PointLight::setDiffuseColor(FLOAT3 _ld)
{
	this->m_ld = _ld;
}

void PointLight::setSpecularColor(FLOAT3 _ls)
{
	this->m_ls = _ls;
}

void PointLight::setRadius(float _radius)
{
	this->m_radius;
}