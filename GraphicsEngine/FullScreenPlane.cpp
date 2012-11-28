#include "FullScreenPlane.h"

FullScreenPlane::FullScreenPlane(ID3D10Device *device, ID3D10Texture2D *_texture)
{
	this->m_mesh = new Mesh(NULL, 6);
	this->m_texture = _texture;

	//Create the vertex buffer
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( Vertex ) * 6;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT hr = device->CreateBuffer( &bd, 0, &this->m_mesh->buffer);

	if(FAILED(hr))
	{
		MessageBox( 0, "Unable to create Vertex Buffer", "VB Error", 0 );
	}

	//Load vertices
	Vertex *vertexData = NULL;
	D3DXVECTOR2 position = D3DXVECTOR2(-1.0f, -1.0f);
	D3DXVECTOR2 size = D3DXVECTOR2(2.0f, 2.0f);

	this->m_mesh->buffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));

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
	
	this->m_mesh->buffer->Unmap();
}

FullScreenPlane::~FullScreenPlane()
{
	delete this->m_mesh;
}

Mesh *FullScreenPlane::getMesh()
{
	return this->m_mesh;
}

ID3D10Texture2D *FullScreenPlane::getTexture()
{
	return this->m_texture;
}