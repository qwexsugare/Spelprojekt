#include "Terrain.h"
#include "VertexStructs.h"

Terrain::Terrain()
{

}

Terrain::Terrain(ID3D10Device* _device, D3DXVECTOR3 v1, D3DXVECTOR3 v2, int rows, int cols, vector<ID3D10ShaderResourceView*> _textures, vector<ID3D10ShaderResourceView*> _blendMaps)
{
	D3DXMatrixIdentity(&this->m_modelMatrix);

	//Set variables
	this->m_topLeft = v1;
	this->m_bottomRight = v2;
	this->m_width = this->m_bottomRight.x-this->m_topLeft.x;
	this->m_height = this->m_topLeft.z-this->m_bottomRight.z;
	this->m_rows = rows;
	this->m_cols = cols;
	this->m_widthBetweenVertices = this->m_width/(this->m_cols-1);
	this->m_heightBetweenVertices = this->m_height/(this->m_rows-1);
	this->m_textures = _textures;
	this->m_blendMaps = _blendMaps;

	float widthBetweenTexCoords = 1.0f/(cols-1);
	float heightBetweenTexCoords = 1.0f/(rows-1);
	vector<Vertex> vertices;

	//Create the vertices
	//int col = 0;
	//int row = 0;
	//const int VERTICES_PER_TILE = 4;
	//for(row = 0; row < rows-1; row++)
	//{
	//	if(row%2 == 1)
	//	{
	//		col = 0;
	//		vertices.push_back(Vertex(
	//			D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*row),
	//			//D3DXVECTOR2(0.0f, fmod((float)((row+VERTICES_PER_TILE-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), 1.0f)),
	//			D3DXVECTOR2((float)col/cols, (float)row/rows),
	//			D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//		vertices.push_back(Vertex(
	//			D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*(row+1)),
	//			//D3DXVECTOR2(0.0f, (float)((row+1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1)),
	//			D3DXVECTOR2((float)col/cols, (float)(row+1)/rows),
	//			D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//		col++;
	//		for(col; col < cols; col++)
	//		{
	//			// Check if we need to draw extra vertices for an ending tile.
	//			if(col%(VERTICES_PER_TILE-1) == 0)
	//			{
	//				vertices.push_back(Vertex(
	//					D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*row),
	//					//D3DXVECTOR2(1.0f, fmod((float)((row+VERTICES_PER_TILE-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), 1.0f)),
	//					D3DXVECTOR2((float)col/cols, (float)row/rows),
	//					D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//				vertices.push_back(Vertex(
	//					D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*(row+1)),
	//					//D3DXVECTOR2(1.0f, (float)((row+1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1)),
	//					D3DXVECTOR2((float)col/cols, (float)(row+1)/rows),
	//					D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//			}
	//				
	//			vertices.push_back(Vertex(
	//				D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*row),
	//				//D3DXVECTOR2((float)(col%(VERTICES_PER_TILE-1))/(VERTICES_PER_TILE-1), fmod((float)((row+VERTICES_PER_TILE-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), 1.0f)),
	//				D3DXVECTOR2((float)col/cols, (float)row/rows),
	//				D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//			vertices.push_back(Vertex(
	//				D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*(row+1)),
	//				//D3DXVECTOR2((float)(col%(VERTICES_PER_TILE-1))/(VERTICES_PER_TILE-1), (float)((row+1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1)),
	//				D3DXVECTOR2((float)col/cols, (float)(row+1)/rows),
	//				D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//		}
	//	}
	//	else
	//	{
	//		col = cols-1;
	//		vertices.push_back(Vertex(
	//			D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*(row+1)),
	//			//D3DXVECTOR2((float)((col-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), (float)((row+1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1)),
	//			D3DXVECTOR2((float)col/cols, (float)(row+1)/rows),
	//			D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//		vertices.push_back(Vertex(
	//			D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*row),
	//			//D3DXVECTOR2((float)((col-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), fmod((float)((row+VERTICES_PER_TILE-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), 1.0f)),
	//			D3DXVECTOR2((float)col/cols, (float)row/rows),
	//			D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//		col--;
	//		for(col; col >= 0; col--)
	//		{
	//			// Check if we need to draw extra vertices for an ending tile.
	//			if(col%(VERTICES_PER_TILE-1) == 0)
	//			{
	//				vertices.push_back(Vertex(
	//					D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*(row+1)),
	//					//D3DXVECTOR2(0.0f, (float)((row+1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1)),
	//					D3DXVECTOR2((float)col/cols, (float)(row+1)/rows),
	//					D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//				vertices.push_back(Vertex(
	//					D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*row),
	//					//D3DXVECTOR2(0.0f, fmod((float)((row+VERTICES_PER_TILE-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), 1.0f)),
	//					D3DXVECTOR2((float)col/cols, (float)row/rows),
	//					D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//			}
	//				
	//			vertices.push_back(Vertex(
	//				D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*(row+1)),
	//				//D3DXVECTOR2((float)((col-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), (float)((row+1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1)),
	//				D3DXVECTOR2((float)col/cols, (float)(row+1)/rows),
	//				D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//			vertices.push_back(Vertex(
	//				D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*row),
	//				//D3DXVECTOR2((float)((col-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), fmod((float)((row+VERTICES_PER_TILE-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), 1.0f)),
	//				D3DXVECTOR2((float)col/cols, (float)row/rows),
	//				D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//		}
	//		
	//		col++;
	//		vertices.push_back(Vertex(
	//			D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*row),
	//			//D3DXVECTOR2((float)((col-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), fmod((float)((row+VERTICES_PER_TILE-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), 1.0f)),
	//			D3DXVECTOR2((float)col/cols, (float)row/rows),
	//			D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//		vertices.push_back(Vertex(
	//			D3DXVECTOR3(v1.x+this->m_widthBetweenVertices*col, 0.0f, v1.z-this->m_heightBetweenVertices*(row+1)),
	//			//D3DXVECTOR2((float)((col-1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1), (float)((row+1)%(VERTICES_PER_TILE-1)+1)/(VERTICES_PER_TILE-1)),
	//			D3DXVECTOR2((float)col/cols, (float)(row+1)/rows),
	//			D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	//	}
	//}
	//this->m_nrOfVertices = vertices.size();

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
	//for(int i = 0; i < vertices.size(); i++)
	//{
	//	vertexData[i].pos = vertices[i].pos;
	//	//vertexData[i].alphaCoord = vertices[i].alphaCoord;
	//	vertexData[i].normal = vertices[i].normal;
	//	vertexData[i].texCoord = vertices[i].texCoord;
	//}

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
}

void Terrain::render(ID3D10EffectTechnique* tech, ID3D10EffectTechnique* _tech2, ID3D10Effect* effect, int pass, ID3D10InputLayout* _particleLayout)
{
	/*// Set vertex buffer.
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	this->device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	this->device->IASetInputLayout(this->vertexLayout);
	this->device->IASetVertexBuffers( 0, 1, &this->vertexBuffer, &stride, &offset );

	// Set shader variables.
	effect->GetVariableByName("nrOfTextures")->AsScalar()->SetInt((int)this->m_textures.size());
	ID3D10ShaderResourceView** textures = new ID3D10ShaderResourceView*[(int)this->m_textures.size()];
	for(int i = 0; i < (int)this->m_textures.size(); i++)
	{
		textures[i] = this->m_textures[i];
	}
	ID3D10ShaderResourceView** alphaMaps = new ID3D10ShaderResourceView*[(int)this->m_alphaMaps.size()];
	for(int i = 0; i < (int)this->m_alphaMaps.size(); i++)
	{
		alphaMaps[i] = this->m_alphaMaps[i];
	}
	effect->GetVariableByName("multiTextures")->AsShaderResource()->SetResourceArray(textures, 0, (int)this->m_textures.size());
	effect->GetVariableByName("alphaMaps")->AsShaderResource()->SetResourceArray(alphaMaps, 0, (int)this->m_alphaMaps.size());
	effect->GetVariableByName("ambientColor")->AsVector()->SetFloatVector(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	effect->GetVariableByName("specularColor")->AsVector()->SetFloatVector(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	effect->GetVariableByName("specularPower")->AsScalar()->SetFloat(20.0f);
		
	// Render
	tech->GetPassByIndex( pass )->Apply(0);
	this->device->Draw(this->m_nrOfVertices, 0);*/
}