#include "Sprite.h"

Sprite::Sprite(ID3D10Device *device, D3DXVECTOR2 position, D3DXVECTOR2 size,ID3D10ShaderResourceView *_texture)
{
	this->m_texture = _texture;
	this->m_nrOfVertices = 6;

	D3DXMatrixIdentity(&this->m_modelMatrix);

	//Create the vertex buffer
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( Vertex ) * 6;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT hr = device->CreateBuffer( &bd, 0, &this->m_buffer);

	if(FAILED(hr))
	{
		MessageBox( 0, "Unable to create Vertex Buffer", "VB Error", 0 );
	}

	//Load vertices
	Vertex *vertexData = NULL;

	this->m_buffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));

	vertexData[2].pos = D3DXVECTOR3(position.x, position.y, 0.0f);
	vertexData[2].texCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertexData[1].pos = D3DXVECTOR3(position.x + size.x, position.y, 0.0f);
	vertexData[1].texCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertexData[0].pos = D3DXVECTOR3(position.x, position.y + size.y, 0.0f);
	vertexData[0].texCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertexData[5].pos = D3DXVECTOR3(position.x + size.x, position.y + size.y, 0.0f);
	vertexData[5].texCoord = D3DXVECTOR2(1.0f, 1.0f);

	vertexData[4].pos = D3DXVECTOR3(position.x, position.y + size.y, 0.0f);
	vertexData[4].texCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertexData[3].pos = D3DXVECTOR3(position.x + size.x, position.y, 0.0f);
	vertexData[3].texCoord = D3DXVECTOR2(1.0f, 0.0f);
	
	this->m_buffer->Unmap();
}

Sprite::~Sprite()
{

}

void Sprite::setPosition(D3DXVECTOR2 position)
{

}

void Sprite::setSize(D3DXVECTOR2 size)
{

}

void Sprite::setRotation(float rotation)
{

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