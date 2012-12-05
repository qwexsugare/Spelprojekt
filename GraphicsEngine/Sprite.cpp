#include "Sprite.h"

Sprite::Sprite(DeviceHandler *_deviceHandler, FLOAT2 position, FLOAT2 size,ID3D10ShaderResourceView *_texture)
{
	this->m_deviceHandler = _deviceHandler;
	this->m_texture = _texture;
	this->m_nrOfVertices = 6;

	//Convert the position and size to projection space
	position.x = (position.x / this->m_deviceHandler->getScreenSize().x) * 2 - 1;
	position.y = (position.y / this->m_deviceHandler->getScreenSize().y) * 2 - 1;

	size.x = (size.x / this->m_deviceHandler->getScreenSize().x) * 2;
	size.y = (size.y / this->m_deviceHandler->getScreenSize().y) * 2;

	//Create the modelmatrix
	D3DXMatrixTranslation(&this->m_modelMatrix, position.x, position.y, 0.0f);

	//Create the vertex buffer
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( Vertex ) * 6;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT hr = this->m_deviceHandler->getDevice()->CreateBuffer( &bd, 0, &this->m_buffer);

	if(FAILED(hr))
	{
		MessageBox( 0, "Unable to create Vertex Buffer", "VB Error", 0 );
	}

	//Load vertices
	D3DXVECTOR2 pos = D3DXVECTOR2(-size.x / 2, -size.y / 2);

	Vertex *vertexData = NULL;

	this->m_buffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));

	//vertexData[2].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	//vertexData[2].texCoord = D3DXVECTOR2(0.0f, 0.0f);

	//vertexData[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y, 0.0f);
	//vertexData[1].texCoord = D3DXVECTOR2(1.0f, 0.0f);

	//vertexData[0].pos = D3DXVECTOR3(pos.x, pos.y + size.y, 0.0f);
	//vertexData[0].texCoord = D3DXVECTOR2(0.0f, 1.0f);

	//vertexData[5].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);
	//vertexData[5].texCoord = D3DXVECTOR2(1.0f, 1.0f);

	//vertexData[4].pos = D3DXVECTOR3(pos.x, pos.y + size.y, 0.0f);
	//vertexData[4].texCoord = D3DXVECTOR2(0.0f, 1.0f);

	//vertexData[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y, 0.0f);
	//vertexData[3].texCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertexData[0].pos = D3DXVECTOR3(pos.x, pos.y + size.y, 0.0f);
	vertexData[0].texCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertexData[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);
	vertexData[1].texCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertexData[2].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	vertexData[2].texCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertexData[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y, 0.0f);
	vertexData[3].texCoord = D3DXVECTOR2(1.0f, 1.0f);

	vertexData[4].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	vertexData[4].texCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertexData[5].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);
	vertexData[5].texCoord = D3DXVECTOR2(1.0f, 0.0f);
	
	this->m_buffer->Unmap();
}

Sprite::~Sprite()
{

}

void Sprite::setPosition(FLOAT2 position)
{
	//Convert the position to projection space
	position.x = (position.x / this->m_deviceHandler->getScreenSize().x) * 2 - 1;
	position.y = (position.y / this->m_deviceHandler->getScreenSize().y) * 2 - 1;

	this->m_modelMatrix._41 = position.x;
	this->m_modelMatrix._42 = position.y;
}

void Sprite::setSize(FLOAT2 size)
{
	//Convert the size to projection space
	size.x = (size.x / this->m_deviceHandler->getScreenSize().x) * 2;
	size.y = (size.y / this->m_deviceHandler->getScreenSize().y) * 2;

	//Load vertices
	D3DXVECTOR2 pos = D3DXVECTOR2(-size.x / 2, -size.y / 2);

	Vertex *vertexData = NULL;

	this->m_buffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));

	vertexData[0].pos = D3DXVECTOR3(pos.x, pos.y + size.y, 0.0f);
	vertexData[0].texCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertexData[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);
	vertexData[1].texCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertexData[2].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	vertexData[2].texCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertexData[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y, 0.0f);
	vertexData[3].texCoord = D3DXVECTOR2(1.0f, 1.0f);

	vertexData[4].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	vertexData[4].texCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertexData[5].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);
	vertexData[5].texCoord = D3DXVECTOR2(1.0f, 0.0f);
	
	this->m_buffer->Unmap();
}

void Sprite::setRotation(float rotation)
{
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationZ(&rotationMatrix, rotation);

	this->m_modelMatrix._11 = rotationMatrix._11;
	this->m_modelMatrix._12 = rotationMatrix._12;
	this->m_modelMatrix._21 = rotationMatrix._21;
	this->m_modelMatrix._22 = rotationMatrix._22;

	//D3DXMatrixMultiply(&this->m_modelMatrix, &rotationMatrix, &this->m_modelMatrix);
}

ID3D10Buffer *Sprite::getBuffer()
{
	return this->m_buffer;
}

int Sprite::getNrOfVertices()
{
	return this->m_nrOfVertices;
}

ID3D10ShaderResourceView *Sprite::getTexture()
{
	return this->m_texture;
}

D3DXMATRIX Sprite::getModelMatrix()
{
	return this->m_modelMatrix;
}