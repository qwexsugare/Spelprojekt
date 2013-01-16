#include "PointLight.h"

PointLight::PointLight()
{
	this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_la = FLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	this->m_ld = FLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	this->m_ls = FLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
}

PointLight::PointLight(FLOAT3 _position, FLOAT4 _la, FLOAT4 _ld, FLOAT4 _ls)
{
	this->m_position = _position;
	this->m_la = _la;
	this->m_ld = _ld;
	this->m_ls = _ls;
}

FLOAT3 PointLight::getPosition()
{
	return this->m_position;
}

FLOAT4 PointLight::getAmbientColor()
{
	return this->m_la;
}

FLOAT4 PointLight::getDiffuseColor()
{
	return this->m_ld;
}

FLOAT4 PointLight::getSpecularColor()
{
	return this->m_ls;
}

void PointLight::setPosition(FLOAT3 _position)
{
	this->m_position = _position;
}

void PointLight::setAmbientColor(FLOAT4 _la)
{
	this->m_la = _la;
}

void PointLight::setDiffuseColor(FLOAT4 _ld)
{
	this->m_ld = _ld;
}

void PointLight::setSpecularColor(FLOAT4 _ls)
{
	this->m_ls = _ls;
}