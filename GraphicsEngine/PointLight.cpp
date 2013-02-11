#include "PointLight.h"

PointLight::PointLight()
{
	this->m_position = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_la = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_ld = FLOAT3(0.0f, 0.0f, 0.0f);
	this->m_ls = FLOAT3(0.0f, 0.0f, 0.0f);
}

PointLight::PointLight(ID3D10Device* _device, FLOAT3 _position, FLOAT3 _la, FLOAT3 _ld, FLOAT3 _ls, float _radius)
{
	this->m_position = _position;
	this->m_la = _la;
	this->m_ld = _ld;
	this->m_ls = _ls;
	this->m_radius = _radius;

	this->m_boundingSphere = new DirectX::BoundingSphere(DirectX::XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), this->m_radius);

	//Create shadowmaps

	for(int i = 0; i < 6; i++)
	{
		this->m_shadowMaps[i] = new DepthStencil(_device, INT2(512, 512));
	}

	this->setPosition(this->m_position);
}

PointLight::~PointLight()
{
	for(int i = 0; i < 6; i++)
	{
		delete this->m_shadowMaps[i];
	}

	delete this->m_boundingSphere;
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

DirectX::BoundingSphere* PointLight::getBs()
{
	return this->m_boundingSphere;
}

D3DXVECTOR2 PointLight::getPosition2D()
{
	return D3DXVECTOR2(this->m_position.x, this->m_position.z);
}

void PointLight::setPosition(FLOAT3 _position)
{
	this->m_position = _position;
	this->m_boundingSphere->Center = DirectX::XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z);

	D3DXMATRIX projMatrix;
	D3DXMATRIX viewMatrix;
	D3DXVECTOR3 eye = D3DXVECTOR3(m_position.x, m_position.y, m_position.z);
	D3DXVECTOR3 at;
	D3DXVECTOR3 up;

	D3DXMatrixPerspectiveFovLH(&projMatrix, D3DX_PI/2, 1.0f, 0.1f, this->m_radius);

	at = D3DXVECTOR3(0.0f, 1.0f, 0.0f) + eye;
	up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &eye, &at, &up);
	D3DXMatrixMultiply(&this->m_wvp[0], &viewMatrix, &projMatrix);

	at = D3DXVECTOR3(0.0f, -1.0f, 0.0f) + eye;
	up = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &eye, &at, &up);
	D3DXMatrixMultiply(&this->m_wvp[1], &viewMatrix, &projMatrix);

	at = D3DXVECTOR3(1.0f, 0.0f, 0.0f) + eye;
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &eye, &at, &up);
	D3DXMatrixMultiply(&this->m_wvp[2], &viewMatrix, &projMatrix);

	at = D3DXVECTOR3(-1.0f, 0.0f, 0.0f) + eye;
	up = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &eye, &at, &up);
	D3DXMatrixMultiply(&this->m_wvp[3], &viewMatrix, &projMatrix);

	at = D3DXVECTOR3(0.0f, 0.0f, 1.0f) + eye;
	up = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &eye, &at, &up);
	D3DXMatrixMultiply(&this->m_wvp[4], &viewMatrix, &projMatrix);

	at = D3DXVECTOR3(0.0f, 0.0f, -1.0f) + eye;
	up = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &eye, &at, &up);
	D3DXMatrixMultiply(&this->m_wvp[5], &viewMatrix, &projMatrix);
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

void PointLight::clearShadowMap(ID3D10Device* _device)
{
	for(int i = 0; i < 6; i++)
	{
		this->m_shadowMaps[i]->clear(_device);
	}
}

ID3D10ShaderResourceView* PointLight::getResource(int index)const
{
	return this->m_shadowMaps[index]->getShaderResource();
}

D3DXMATRIX PointLight::getMatrix(int index)
{
	return this->m_wvp[index];
}

void PointLight::setShadowMapAsRenderTarget(ID3D10Device* _device, int index)
{
	_device->OMSetRenderTargets(0, NULL, this->m_shadowMaps[index]->getDepthStencilView());
}