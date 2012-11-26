#include "MeshImporter.h"

Mesh* MeshImporter::loadOBJMesh(ID3D10Device *_device, TextureHolder *textureHolder, string _filename)
{
	Mesh* result = NULL;

	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> texCoords;
	vector<int> faceVertexPos1;
	vector<int> faceVertexPos2;
	vector<int> faceVertexPos3;
	vector<int> faceVertexTexCoord1;
	vector<int> faceVertexTexCoord2;
	vector<int> faceVertexTexCoord3;
	vector<int> faceVertexNormal1;
	vector<int> faceVertexNormal2;
	vector<int> faceVertexNormal3;
	string mtllib = "";
	string currentMaterial = "";
	vector<string> useMaterials;
	D3DXVECTOR3 minPointValues;
	D3DXVECTOR3 maxPointValues;

	// Open and read the obj file.
	ifstream stream;
	stream.open(_filename);
	while(!stream.eof())
	{
		char buf[1024];
		char key[100];
		stream.getline(buf, 1024);
		sscanf(buf, "%s", key);
		if(strcmp(key, "v") == 0) // Vertex.
		{
			float x, y, z;
			sscanf(buf, "v %f %f %f", &x, &y, &z);
			D3DXVECTOR3 position = D3DXVECTOR3(x, y, -z);
			positions.push_back(position);
		}
		else if(strcmp(key, "vt") == 0) // Texture coordinate.
		{
			float u, v;
			sscanf(buf, "vt %f %f", &u, &v);
			texCoords.push_back(D3DXVECTOR2(u, 1.0f-v));
		}
		else if(strcmp(key, "vn") == 0) // Normal.
		{
			float x, y, z;
			sscanf(buf, "vn %f %f %f", &x, &y, &z);
			normals.push_back(D3DXVECTOR3(x, y, -z));
		}
		else if(strcmp(key, "f") == 0) // Mesh.
		{
			int v1, v2, v3;
			int uv1, uv2, uv3;
			int vn1, vn2, vn3;
			sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &uv1, &vn1, &v2, &uv2, &vn2, &v3, &uv3, &vn3);
			faceVertexPos1.push_back(v1);
			faceVertexPos2.push_back(v2);
			faceVertexPos3.push_back(v3);
			faceVertexTexCoord1.push_back(uv1);
			faceVertexTexCoord2.push_back(uv2);
			faceVertexTexCoord3.push_back(uv3);
			faceVertexNormal1.push_back(vn1);
			faceVertexNormal2.push_back(vn2);
			faceVertexNormal3.push_back(vn3);
			useMaterials.push_back(currentMaterial);
		}
		else if(strcmp(key, "g") == 0) // Polygon group.
		{
			char polygonGroup[100];
			sscanf(buf, "g %s", polygonGroup);
		}
	}

	stream.close();
	
	//Create the vertex buffer
	ID3D10Buffer* buffer;
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( Vertex ) * (int)faceVertexPos1.size() * 3;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT hr = _device->CreateBuffer( &bd, 0, &buffer);

	if(FAILED(hr))
	{
		MessageBox( 0, "Unable to create Vertex Buffer", "VB Error", 0 );
	}

	//Load vertices
	Vertex *vertexData = NULL;
	buffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));

	for(int i = 0; i < (int)faceVertexPos1.size(); i++)
	{
		vertexData[i * 3].pos = positions[faceVertexPos1[i]-1];
		vertexData[i * 3].texCoord = texCoords[faceVertexTexCoord1[i]-1];
		vertexData[i * 3].normal = normals[faceVertexNormal1[i]-1];

		vertexData[i * 3 + 1].pos = positions[faceVertexPos2[i]-1];
		vertexData[i * 3 + 1].texCoord = texCoords[faceVertexTexCoord2[i]-1];
		vertexData[i * 3 + 1].normal = normals[faceVertexNormal2[i]-1];

		vertexData[i * 3 + 2].pos = positions[faceVertexPos3[i]-1];
		vertexData[i * 3 + 2].texCoord = texCoords[faceVertexTexCoord3[i]-1];
		vertexData[i * 3 + 2].normal = normals[faceVertexNormal3[i]-1];
	}
	 
	buffer->Unmap();

	result = new Mesh(buffer, 3);

	return result;
}