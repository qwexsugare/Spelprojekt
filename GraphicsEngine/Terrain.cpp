#include "Terrain.h"
#include "VertexStructs.h"

Terrain::Terrain()
{

}

Terrain::Terrain(ID3D10Device* _device, D3DXVECTOR3 v1, D3DXVECTOR3 v2, int rows, int cols, ID3D10ShaderResourceView** _textures, int _nrOfTextures, ID3D10ShaderResourceView** _blendMaps, int _nrOfBlendMaps)
{
	D3DXMatrixIdentity(&this->m_modelMatrix);

	//Set variables
	this->m_topLeft = v1;
	this->m_bottomRight = v2;
	this->m_width = max(this->m_bottomRight.x-this->m_topLeft.x, -(this->m_bottomRight.x-this->m_topLeft.x));
	this->m_height = max(this->m_topLeft.z-this->m_bottomRight.z, -(this->m_topLeft.z-this->m_bottomRight.z));
	this->m_rows = rows;
	this->m_cols = cols;
	this->m_nrOfTextures = _nrOfTextures;
	this->m_textures = _textures;
	this->m_nrOfBlendMaps = _nrOfBlendMaps;
	this->m_blendMaps = _blendMaps;
	this->m_nrOfVertices = 4;

	float widthBetweenTexCoords = 1.0f/(cols-1);
	float heightBetweenTexCoords = 1.0f/(rows-1);
	vector<Vertex> vertices;

	//Create the vertex buffer
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	//bd.ByteWidth = sizeof(Vertex) * vertices.size();
	bd.ByteWidth = sizeof(Vertex) * 4;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT hr = _device->CreateBuffer( &bd, 0, &this->m_vertexBuffer );
	if(FAILED(hr))
	{
		MessageBox( 0, "Unable to create Vertex Buffer", "VB Error", 0 );
	}
	
	// Fill the vertex buffer.
	Vertex *vertexData = NULL;
	this->m_vertexBuffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));
	
	vertexData[0].pos = v1;
	vertexData[0].texCoord = D3DXVECTOR2(0.0f, 0.0f);
	vertexData[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	vertexData[1].pos = D3DXVECTOR3(v2.x, v1.y, v1.z);
	vertexData[1].texCoord = D3DXVECTOR2(rows, 0.0f);
	vertexData[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	vertexData[2].pos = D3DXVECTOR3(v1.x, v1.y, v2.z);
	vertexData[2].texCoord = D3DXVECTOR2(0.0f, cols);
	vertexData[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	vertexData[3].pos = v2;
	vertexData[3].texCoord = D3DXVECTOR2(rows, cols);
	vertexData[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	this->m_vertexBuffer->Unmap();
}

Terrain::~Terrain()
{
	if(this->m_vertexBuffer)
		this->m_vertexBuffer->Release();
	
	delete []this->m_textures;
	delete []this->m_blendMaps;
}