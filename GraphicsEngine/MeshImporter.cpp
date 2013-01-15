//*****************
//	- 12-12-12 - Anders -
//	- Added vector: subMeshes
//	- Include SubMesh.h
//	- 16-12-12 - Anders och Alve -
//	- Added LoadFishMesh()
//	- Added ReadMaterials()
//*****************

#include "MeshImporter.h"

fstream MeshImporter::m_fStream;

Mesh* MeshImporter::loadOBJMesh(ID3D10Device *_device, TextureHolder *textureHolder, string _filename)
{
	Mesh* result = NULL;
	string filepath = "./models/";

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
	stream.open(filepath+_filename+".obj");
	std::string temp = filepath+_filename+".obj";
	if(stream.is_open())
		OutputDebugStringA("Funkar");
	else
		OutputDebugStringA("Funkar inte");
	
	
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
		else if(strcmp(key, "mtllib") == 0) // Material file.
		{
			char tempMtllib[100];
			sscanf(buf, "mtllib %s", tempMtllib);
			mtllib = string(tempMtllib);
		}
		else if(strcmp(key, "usemtl") == 0) // Use material.
		{
			char tempMtl[100];
			sscanf(buf, "usemtl %s", tempMtl);
			currentMaterial = string(tempMtl);
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
	
	vector<string> newMaterials;
	struct MATERIAL
	{
		ID3D10ShaderResourceView* texture;
		string name;
	};
	vector<MATERIAL> materials;
	ID3D10ShaderResourceView* texture = NULL;
	
	// Open and read the mtl file.
	stream.open(filepath+mtllib);
	while(!stream.eof())
	{
		char buf[1024];
		char key[100];
		stream.getline(buf, 1024);
		sscanf(buf, "%s", key);
		if(strcmp(key, "newmtl") == 0) // New material.
		{
			char newMaterial[100];
			sscanf(buf, "newmtl %s", newMaterial);
			newMaterials.push_back(string(newMaterial));

			// Check if a complete new material has been defined.
			if((int)newMaterials.size() > 1)
			{
				MATERIAL mat;
				mat.name = newMaterials[(int)newMaterials.size()-2];
				mat.texture = texture;
				materials.push_back(mat);
				texture = NULL;
			}
		}
		else if(strcmp(key, "map_Kd") == 0) // Texture map.
		{
			char textureFilename[100];
			sscanf(buf, "map_Kd %s", textureFilename);
			texture = textureHolder->getTexture(string(filepath+textureFilename));
		}
	}
	stream.close();
	// Add one last complete new material.
	MATERIAL matlol;
	matlol.name = newMaterials[(int)newMaterials.size()-2];
	matlol.texture = materials[(int)newMaterials.size()-2].texture;
	materials.push_back(matlol);
	
	result = new Mesh(buffer, faceVertexPos1.size()*3);
	result->m_texture = matlol.texture;

	return result;
}

Mesh* MeshImporter::LoadFishMesh(ID3D10Device* device, TextureHolder* textureHolder, string filename)
{
	Mesh* mesh = NULL;
	string filepath = "./models/";
	string line;
	char in;
	UINT numSkeletons = 0;
	UINT numMaterials = 0;
	UINT numGeometry = 0;

	m_fStream.open(filepath + filename + ".fish", ios_base::in);
	
	m_fStream.get(in);
	while(!m_fStream.eof())
	{
		switch( in )
		{
			case 's':
				m_fStream >> numSkeletons;
				getline(m_fStream, line);
				for(UINT i = 0; i < numSkeletons; i++)
					getline(m_fStream, line); //Store Skeleton
				break;
			case 'm':
				m_fStream >> numMaterials;
				getline(m_fStream, line);
				for(UINT i = 0; i < numMaterials; i++)
					mesh->materials.push_back(ReadMaterial(textureHolder));
				break;
			case 'g':
				m_fStream >> numGeometry;
				mesh->subMeshes.resize(numGeometry);
				getline(m_fStream, line);
				for(UINT i = 0; i < numGeometry; i++)
					ReadGeometry(mesh, i, device);
				break;
			case'\n':
				break;
			default:
				getline(m_fStream, line);
				//filestream.get(in);
				break;
		}
		m_fStream.get(in);
	}
	
	//For Fun
	mesh->buffer = mesh->subMeshes[0].buffer;
	mesh->m_texture = mesh->materials[mesh->subMeshes[0].materialId].textures[0];

	m_fStream.close();
	return mesh;
}

Material MeshImporter::ReadMaterial(TextureHolder* textureHolder)
{
	Material material;
	UINT numTextures = 0;
	char in;
	string path, type, line;
	ID3D10ShaderResourceView* resource;
	
	if(m_fStream.is_open())
	{
		m_fStream >> numTextures;
		for(int t = 0; t < numTextures; t++)
		{
			m_fStream >> path >> type;
			getline(m_fStream, line);
			resource = textureHolder->getTexture(path);
			material.textures.insert(material.textures.end(), pair<string,ID3D10ShaderResourceView*>(type, resource));
		}
	}
	return material;
}
void MeshImporter::ReadGeometry(Mesh* mesh, int meshId, ID3D10Device* device)
{
	string in;
	vector<Vertex> verts;
	D3DXVECTOR3 tangent;
	D3DXVECTOR4 weights;
	D3DXVECTOR4 boneIndex;

	m_fStream >> in;
	m_fStream >> mesh->subMeshes[meshId].skeletonId;
	m_fStream >> in;
	m_fStream >> mesh->subMeshes[meshId].numInfluences;
	m_fStream >> in;
	m_fStream >> mesh->subMeshes[meshId].numVerts;
	m_fStream >> in;
	m_fStream >> mesh->subMeshes[meshId].materialId;
	getline(m_fStream, in);
	for(int v = 0; v < mesh->subMeshes[meshId].numVerts; v++)
	{
		Vertex myVert;
		m_fStream >> in;
		m_fStream >> myVert.pos.x >> myVert.pos.y, myVert.pos.z;
		m_fStream >> in;
		m_fStream >> myVert.normal.x >> myVert.normal.y, myVert.normal.z;
		m_fStream >> in;
		m_fStream >> tangent.x >> tangent.y, tangent.z;
		m_fStream >> in;
		m_fStream >> myVert.texCoord.x >> myVert.texCoord.y;
		for(int i = 0; i < mesh->subMeshes[meshId].numInfluences; i++)
		{
			m_fStream >> boneIndex[i] >> weights[i];
		}
	}

	ID3D10Buffer* buffer;
	D3D10_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( Vertex ) * verts.size();
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D10_SUBRESOURCE_DATA sd;
	sd.pSysMem = &verts[0];

	HRESULT hr = device->CreateBuffer( &bd, &sd, &buffer);
	if(FAILED(hr))
		hr;
	mesh->subMeshes[meshId].buffer = buffer;
}