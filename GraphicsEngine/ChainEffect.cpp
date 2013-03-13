#include "ChainEffect.h"


ChainEffect::ChainEffect(ID3D10Device* _device)
{
	D3DXMatrixIdentity(&this->m_viewProj);
	this->m_device = m_device;
}


ChainEffect::~ChainEffect()
{
}

void ChainEffect::CreateVertexBuffer()
{
	HRESULT hr;

	D3D10_BUFFER_DESC vbd;
	vbd.Usage			= D3D10_USAGE_DEFAULT;
	vbd.ByteWidth		= sizeof(ChainVertex)*8;
	vbd.BindFlags		= D3D10_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags	= 0;
	vbd.MiscFlags		= 0;

	ChainVertex v;
	ZeroMemory(&v, sizeof(ChainVertex));
	v.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3D10_SUBRESOURCE_DATA initData;
	initData.pSysMem = &v;

	hr = m_device->CreateBuffer(&vbd, &initData, &this->m_vertexBuffer);
	if(FAILED(hr))
		MessageBox(NULL, "( ChainEffect ) Failed to create Vertex Buffer", NULL, NULL);

	//vbd.ByteWidth = sizeof(ChainVertex) * 8;
	//vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER | D3D10_BIND_STREAM_OUTPUT;

	//hr = this->m_device->CreateBuffer(&vbd, 0, &drawVB);
	//if(FAILED(hr))
	//	MessageBox(NULL, "( ParticleEngine ) Failed to create Draw Vertex Buffer", NULL, NULL);
	//hr = this->m_device->CreateBuffer(&vbd, 0, &streamOutVB);
	//if(FAILED(hr))
	//	MessageBox(NULL, "( ParticleEngine ) Failed to create StreamOut Vertex Buffer", NULL, NULL);
}


void ChainEffect::update(float _dt)
{

}

void ChainEffect::draw(ChainFXEffectFile* fxFile)
{
	//fxFile->setOrig(this->m_orig);
	//fxFile->setTarget(this->m_target);
	//fxFile->setViewProj(this->m_viewProj);
	//this->m_device->IASetInputLayout(fxFile->getInputLayout());
	//UINT stride = sizeof(ChainVertex);
	//UINT offset = 0;
	//this->m_device->IAGetVertexBuffers(0, 1, &this->m_vertexBuffer, &stride, &offset);
}

void ChainEffect::setViewProj(D3DXMATRIX _viewProj)
{
	this->m_viewProj = _viewProj;
}