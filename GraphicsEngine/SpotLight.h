#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "stdafx.h"
#include "DataStructures.h"
#include "DepthStencil.h"

class SpotLight
{
private:
	FLOAT3 m_position;
	FLOAT3 m_direction;
	FLOAT3 m_la;
	FLOAT3 m_ld;
	FLOAT3 m_ls;
	FLOAT2 m_angle;
	float m_range;
	
	D3DXVECTOR3 m_dxDirection;
	D3DXVECTOR3 m_up;
	D3DXMATRIX m_wvp;
	DepthStencil* m_shadowMap;
public:
	SpotLight();
	SpotLight(ID3D10Device* _device, FLOAT3 _position, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls, FLOAT2 _angle, float range);
	~SpotLight();

	void clearShadowMap(ID3D10Device* _device);
	ID3D10ShaderResourceView* getResource()const { return m_shadowMap->getShaderResource(); }
	void setShadowMapAsRenderTarget(ID3D10Device* _device);

	DECLDIR FLOAT3 getPosition();
	DECLDIR FLOAT3 getDirection();
	DECLDIR FLOAT3 getAmbientColor();
	DECLDIR FLOAT3 getDiffuseColor();
	DECLDIR FLOAT3 getSpecularColor();
	DECLDIR FLOAT2 getAngle();
	DECLDIR float getRange();
	D3DXMATRIX getWvp()const { return m_wvp; }
	DECLDIR void rotate(float _rad);
	DECLDIR void setPosition(FLOAT3 _position);
	DECLDIR void setDirection(FLOAT3 _direction);
	DECLDIR void setAmbientColor(FLOAT3 _la);
	DECLDIR void setDiffuseColor(FLOAT3 _ld);
	DECLDIR void setSpecularColor(FLOAT3 _ls);
	DECLDIR void setAngle(FLOAT2 _angle);
	DECLDIR void setRange(float range);
};

#endif
