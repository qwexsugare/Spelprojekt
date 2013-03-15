#include "ChainEffect.h"


ChainEffect::ChainEffect(ID3D10Device* _device, TextureHolder* _textureHolder)
{
	D3DXMatrixIdentity(&this->m_viewProj);
	this->m_device = _device;
	this->m_orig = D3DXVECTOR3(0, 0, 0);
	this->m_target = D3DXVECTOR3(64, 0, 64);

	m_texture = _textureHolder->getTexture("./particles/textures/lightning.png");

	CreateVertexBuffer();
}


ChainEffect::~ChainEffect()
{
}

void ChainEffect::CreateVertexBuffer()
{
	HRESULT hr;

	D3D10_BUFFER_DESC vbd;
	vbd.Usage			= D3D10_USAGE_DEFAULT;
	vbd.ByteWidth		= sizeof(ChainVertex);
	vbd.BindFlags		= D3D10_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags	= 0;
	vbd.MiscFlags		= 0;

	ChainVertex v;
	ZeroMemory(&v, sizeof(ChainVertex));
	v.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3D10_SUBRESOURCE_DATA initData;
	initData.pSysMem = &v;

	this->m_vertexBuffer = NULL;
	hr = m_device->CreateBuffer(&vbd, &initData, &this->m_vertexBuffer);
	if(FAILED(hr))
		MessageBox(NULL, "( ChainEffect ) Failed to create Vertex Buffer", NULL, NULL);

	vbd.ByteWidth = sizeof(ChainVertex) * 8;
	vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER | D3D10_BIND_STREAM_OUTPUT;

	hr = this->m_device->CreateBuffer(&vbd, 0, &drawVB);
	if(FAILED(hr))
		MessageBox(NULL, "( ParticleEngine ) Failed to create Draw Vertex Buffer", NULL, NULL);
	hr = this->m_device->CreateBuffer(&vbd, 0, &streamOutVB);
	if(FAILED(hr))
		MessageBox(NULL, "( ParticleEngine ) Failed to create StreamOut Vertex Buffer", NULL, NULL);
}


void ChainEffect::update(float _dt)
{

}

void ChainEffect::draw(ChainFXEffectFile* _fxFile)
{
	_fxFile->setOrig(this->m_orig);
	_fxFile->setTarget(this->m_target);
	_fxFile->setViewProj(this->m_viewProj);
	_fxFile->setTexture(m_texture);

	this->m_device->IASetInputLayout(_fxFile->getInputLayout());

	UINT stride = sizeof(ChainVertex);
	UINT offset = 0;	
	
	ID3D10Buffer* bufferArray[1] = {0};
	m_device->SOSetTargets(1, bufferArray, &offset);
	
	//swap(drawVB, streamOutVB);

	m_device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
	this->m_device->IAGetVertexBuffers(0, 1, &this->m_vertexBuffer, &stride, &offset);

	D3D10_TECHNIQUE_DESC techDesc;
	_fxFile->getTechnique()->GetDesc(&techDesc);
	for(UINT p = 0; p < techDesc.Passes; p++)
	{
		_fxFile->getTechnique()->GetPassByIndex(p)->Apply(0);
		m_device->DrawAuto();
	}
}

void ChainEffect::setViewProj(D3DXMATRIX _viewProj)
{
	this->m_viewProj = _viewProj;
}

void ChainEffect::setOrig(D3DXVECTOR3 _vec)
{
	this->m_orig = _vec;
}

void ChainEffect::setTarget(D3DXVECTOR3 _vec)
{
	this->m_target = _vec;
}

void ChainEffect::setCamPos(D3DXVECTOR3 _vec)
{
	this->m_camPos = _vec;
}
