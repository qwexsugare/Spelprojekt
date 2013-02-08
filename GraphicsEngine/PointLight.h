#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "stdafx.h"
#include "DataStructures.h"
#include "DepthStencil.h"
#include <DirectXMath.h>
#include <DirectXCollision.h>

class PointLight
{
private:
	FLOAT3 m_position;
	FLOAT3 m_la;
	FLOAT3 m_ld;
	FLOAT3 m_ls;
	float m_radius;

	DirectX::BoundingSphere* m_boundingSphere;

	D3DXMATRIX m_wvp[6];
	DepthStencil* m_shadowMaps[6];
public:
	PointLight();
	PointLight(ID3D10Device* _device, FLOAT3 _position, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls, float _radius);
	~PointLight();

	DECLDIR FLOAT3 getPosition();
	DECLDIR FLOAT3 getAmbientColor();
	DECLDIR FLOAT3 getDiffuseColor();
	DECLDIR FLOAT3 getSpecularColor();
	DECLDIR float getRadius();

	DirectX::BoundingSphere* getBs();
	D3DXVECTOR2 getPosition2D();

	void clearShadowMap(ID3D10Device* _device);
	ID3D10ShaderResourceView* getResource(int index)const;
	D3DXMATRIX getMatrix(int index);
	void setShadowMapAsRenderTarget(ID3D10Device* _device, int index);

	DECLDIR void setPosition(FLOAT3 _position);
	DECLDIR void setAmbientColor(FLOAT3 _la);
	DECLDIR void setDiffuseColor(FLOAT3 _ld);
	DECLDIR void setSpecularColor(FLOAT3 _ls);
	DECLDIR void setRadius(float _radius);
};

#endif