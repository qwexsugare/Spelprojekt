#include "Road.h"
#include "VertexStructs.h"

Road::Road()
{
	m_vertexBuffer = NULL;
}

Road::Road(ID3D10Device* _device, ID3D10ShaderResourceView* _texture, D3DXVECTOR3 _pos, float _rot)
{
	m_texture = _texture;
	// Order important
	D3DXMatrixIdentity(&m_modelMatrix);
	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationY(&rotMatrix, _rot * (D3DX_PI/180.0f));
	D3DXMatrixMultiply(&m_modelMatrix, &m_modelMatrix, &rotMatrix);
	m_modelMatrix._41 = _pos.x;
	m_modelMatrix._42 = _pos.y;
	m_modelMatrix._43 = _pos.z;
	// EOF order important
	m_nrOfVertices = 4;

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * 4;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT hr = _device->CreateBuffer( &bd, 0, &this->m_vertexBuffer );
	if(FAILED(hr))
		MessageBox( 0, "Unable to create Road Vertex Buffer", "VB Error", 0 );
	
	Vertex *vertexData = NULL;
	this->m_vertexBuffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));
	
	vertexData[0].pos = D3DXVECTOR3(-SIZE/2.0, _pos.y, -SIZE/2.0);
	vertexData[0].texCoord = D3DXVECTOR2(0.0f, 0.0f);
	vertexData[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	vertexData[1].pos = D3DXVECTOR3(SIZE/2.0, _pos.y, -SIZE/2.0);
	vertexData[1].texCoord = D3DXVECTOR2(1.0f, 0.0f);
	vertexData[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	vertexData[2].pos = D3DXVECTOR3(-SIZE/2.0, _pos.y, SIZE/2.0);
	vertexData[2].texCoord = D3DXVECTOR2(0.0f, 1.0f);
	vertexData[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	vertexData[3].pos = D3DXVECTOR3(SIZE/2.0, _pos.y, SIZE/2.0);
	vertexData[3].texCoord = D3DXVECTOR2(1.0f, 1.0f);
	vertexData[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	this->m_vertexBuffer->Unmap();

	this->m_obb = new BoundingOrientedBox(XMFLOAT3(_pos.x, _pos.y, _pos.z), XMFLOAT3(SIZE/2, 0.5f, SIZE/2), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

Road::~Road()
{
	if(m_vertexBuffer)
		m_vertexBuffer->Release();

	delete this->m_obb;
}

D3DXVECTOR2 Road::getPosition2D()
{
	return D3DXVECTOR2(this->m_modelMatrix._41, this->m_modelMatrix._43);
}