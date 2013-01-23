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

Mesh* MeshImporter::LoadFishes(ID3D10Device* device, TextureHolder* textureHolder, AnimationHolder* animationHolder, string filename)
{
	Mesh* mesh = NULL;
	string folder = "./models/";
	string  filepath = folder + filename;
	vector<string> fileList;
	char* folderPath = (char*)filepath.c_str();
	WIN32_FIND_DATA fData;
	HANDLE handle;

	char cBuffer[MAX_PATH];
	sprintf_s(cBuffer, sizeof(cBuffer), "%s\\*", folderPath);
	handle = FindFirstFile(cBuffer, &fData);
	if(handle != INVALID_HANDLE_VALUE)
	{
		while(true)
		{
			if(FindNextFile(handle, &fData))
			{
				fileList.push_back(fData.cFileName);
			}
			else
			{
				if(GetLastError() == ERROR_NO_MORE_FILES)
					break;
			}
		}
	}
	else
	{
		#ifdef _DEBUG
				string msg = "Model " + folder + filename + " not found.";
				MessageBox(NULL, (LPCSTR)msg.c_str(), "ERROR!" , 0);
		#endif
	}
	FishFile fishFile;
	ReadFish(&fishFile, textureHolder, folder + filename + "/" + filename + ".BFish", folder + filename + "/");	
	Animation ani;
	for(int i = 1; i < fileList.size(); i++)
	{
		//Find animation files
		size_t f = fileList[i].find(".BFishA");
		if (f != string::npos)
		{
			string animationName;
			for(int c = 0; c < f; c++)
				animationName += fileList[i][c];

			AnimationFile fishAnimation;
			ReadFishAnimation(&fishAnimation, folder + filename + "/" +  animationName + ".BFishA", fishFile.fFileInfo.numSkeleton);
			ani.addAnimation(animationName, fishAnimation);
		}
	}
	
	mesh = CreateMesh(device, &fishFile, ani.getNumAnimations() > 0, textureHolder, folderPath);

	animationHolder->addAnimation(filename, ani);

	return mesh;
}

void MeshImporter::ReadFish(FishFile* fishFile, TextureHolder* textureHolder, string filepath, string folderPath)
{
	char* memblock = NULL;

	ifstream rb;
	rb.open(filepath, ios::in | ios::binary | ios::ate);
	if(!rb.is_open())
		MessageBox(NULL, filepath.c_str(), "File Not Found", 0);		
	ifstream::pos_type size;
	size = rb.tellg();
	memblock = new char[size];
	rb.seekg(0, ios::beg);

	rb.read((char*)memblock, size);
	
	rb.close();

	MapFishFile(fishFile, memblock);
	if(memblock)
		delete memblock;
}

Mesh* MeshImporter::CreateMesh(ID3D10Device *device, FishFile* fishFile, bool isAnimated, TextureHolder* textureHolder, string folderPath)
{
	Mesh* mesh = NULL;

	mesh = new Mesh();

	mesh->subMeshes.resize(fishFile->FMeshes.size());

	for(int m = 0; m < fishFile->FMeshes.size(); m++)
	{
		vector<Vertex> verts;
		verts.resize(fishFile->FMeshes[m].numVertices);

		
		vector<AnimationVertex> animationVerts;
		animationVerts.resize(fishFile->FMeshes[m].numVertices);
		if(isAnimated)
		{
			for(int v = 0 ; v < fishFile->FMeshes[m].numVertices; v++)
			{
				animationVerts[v].pos.x = fishFile->FMeshes[m].vertices[v].position.x;
				animationVerts[v].pos.y = fishFile->FMeshes[m].vertices[v].position.y;
				animationVerts[v].pos.z = fishFile->FMeshes[m].vertices[v].position.z;
			
				animationVerts[v].normal.x = fishFile->FMeshes[m].vertices[v].normal.x;
				animationVerts[v].normal.y = fishFile->FMeshes[m].vertices[v].normal.y;
				animationVerts[v].normal.z = fishFile->FMeshes[m].vertices[v].normal.z;

				animationVerts[v].texCoord.x = fishFile->FMeshes[m].vertices[v].uv.u;
				animationVerts[v].texCoord.y = fishFile->FMeshes[m].vertices[v].uv.v;

				animationVerts[v].weight.x = fishFile->FMeshes[m].vertices[v].weights[0];
				animationVerts[v].weight.y = fishFile->FMeshes[m].vertices[v].weights[1];
				animationVerts[v].weight.z = fishFile->FMeshes[m].vertices[v].weights[2];
				animationVerts[v].weight.w = fishFile->FMeshes[m].vertices[v].weights[3];

		/*		float fisk =  fishFile->FMeshes[m].vertices[v].weights[0] + fishFile->FMeshes[m].vertices[v].weights[1] + fishFile->FMeshes[m].vertices[v].weights[2] + fishFile->FMeshes[m].vertices[v].weights[3];
				if(fisk < 0.7f)
					int hi = 0;*/
				animationVerts[v].bone.x = fishFile->FMeshes[m].vertices[v].boneIndex[0];
				animationVerts[v].bone.y = fishFile->FMeshes[m].vertices[v].boneIndex[1];
				animationVerts[v].bone.z = fishFile->FMeshes[m].vertices[v].boneIndex[2];
				animationVerts[v].bone.w = fishFile->FMeshes[m].vertices[v].boneIndex[3];
			}
		}
		else
		{
			for(int v = 0 ; v < fishFile->FMeshes[m].numVertices; v++)
			{
				verts[v].pos.x = fishFile->FMeshes[m].vertices[v].position.x;
				verts[v].pos.y = fishFile->FMeshes[m].vertices[v].position.y;
				verts[v].pos.z = fishFile->FMeshes[m].vertices[v].position.z;
			
				verts[v].normal.x = fishFile->FMeshes[m].vertices[v].normal.x;
				verts[v].normal.y = fishFile->FMeshes[m].vertices[v].normal.y;
				verts[v].normal.z = fishFile->FMeshes[m].vertices[v].normal.z;

				verts[v].texCoord.x = fishFile->FMeshes[m].vertices[v].uv.u;
				verts[v].texCoord.y = fishFile->FMeshes[m].vertices[v].uv.v;
			}
		}

		ID3D10Buffer* buffer = NULL;
		D3D10_BUFFER_DESC bd;
		bd.Usage = D3D10_USAGE_DEFAULT;
		
		if(isAnimated)
			bd.ByteWidth = sizeof( AnimationVertex ) * fishFile->FMeshes[m].numVertices;
		else
			bd.ByteWidth = sizeof( Vertex ) * fishFile->FMeshes[m].numVertices;

		bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D10_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		if(isAnimated)
			sd.pSysMem = &animationVerts[m];
		else
			sd.pSysMem = &verts[m];
	

		HRESULT hr = device->CreateBuffer( &bd, &sd, &buffer);

		mesh->subMeshes[m] = new SubMesh(buffer, fishFile->FMeshes[m].numVertices);
		mesh->subMeshes[m]->materialId = fishFile->FMeshes[m].materialIndex;
	}

	for(int m = 0; m < fishFile->FMeshes.size(); m++)
	{
		for(int t = 0; t < fishFile->fMaterials.size(); t++)
		{
			if(fishFile->FMeshes[m].materialIndex == t)
			{
				string tName;
				for(int c = 0; c < fishFile->fMaterials[m].textures[t].pathSize; c++)
					tName += fishFile->fMaterials[m].textures[t].path[c];
				mesh->subMeshes[m]->diffuse = textureHolder->getTexture(string(folderPath + "/" + tName));
			}
		}
	}

	XMFLOAT3 cen(fishFile->boundingVol.pos.x, fishFile->boundingVol.pos.y, fishFile->boundingVol.pos.z);

	XMFLOAT3 ext(fishFile->boundingVol.size.x, fishFile->boundingVol.size.y, fishFile->boundingVol.size.z);

	XMFLOAT4 quat(0, 0, 0, 1);

	switch(fishFile->boundingVol.type)
	{
		case 0:
			mesh->m_bs = new BoundingSphere(cen, ext.x);
			break;
		case 1:
			mesh->m_obb = new BoundingOrientedBox(cen, ext, quat);
			break;
	}

	mesh->numSkeletons = fishFile->fFileInfo.numSkeleton;

	mesh->isAnimatied = isAnimated;

	return mesh;
}

void MeshImporter::ReadFishAnimation(AnimationFile* animationFile, string filepath, int numSkeletons)
{
	char* memblock = NULL;

	ifstream rb;
	rb.open(filepath, ios::in | ios::binary | ios::ate);
	ifstream::pos_type size;
	size = rb.tellg();
	memblock = new char[size];
	rb.seekg(0, ios::beg);

	rb.read((char*)memblock, size);
	
	rb.close();

	MapAnimationFile(animationFile, memblock, numSkeletons);
	if(memblock)
		delete memblock;
}

void MeshImporter::MapFishFile(FishFile* fishFile, char* memblock)
{
	//Map Random Header
	fishFile->fFileInfo = *(FFileInfo*)memblock;
	memblock += sizeof(FFileInfo);
	//Map boundingVol
	fishFile->boundingVol = *(FBoundingVolume*)memblock;
	memblock += sizeof(FBoundingVolume);
	//Map Materials
	fishFile->fMaterials.resize(fishFile->fFileInfo.numMaterials);
	for(int m = 0; m < fishFile->fFileInfo.numMaterials; m++)
	{
		fishFile->fMaterials[m].numTextures = *(int*)memblock;
		memblock += sizeof(int);
		fishFile->fMaterials[m].textures.resize(fishFile->fMaterials[m].numTextures);
		for(int t = 0; t < fishFile->fMaterials[m].numTextures; t++)
		{
			fishFile->fMaterials[m].textures[t] = *(FTexture*)memblock;
			memblock += sizeof(FTexture);
		}
	}
	//Map Meshes
	fishFile->FMeshes.resize(fishFile->fFileInfo.numGeometry);
	for(int g = 0; g < fishFile->fFileInfo.numGeometry; g++)
	{
		fishFile->FMeshes[g].skeletonId = *(int*)memblock;
		memblock += sizeof(int);
		fishFile->FMeshes[g].numInfluences = *(int*)memblock;
		memblock += sizeof(int);
		fishFile->FMeshes[g].numVertices = *(int*)memblock;
		memblock += sizeof(int);
		fishFile->FMeshes[g].materialIndex = *(int*)memblock;
		memblock += sizeof(int);

		fishFile->FMeshes[g].vertices.resize(fishFile->FMeshes[g].numVertices);
		for(int v = 0; v < fishFile->FMeshes[g].numVertices; v++)
		{
			fishFile->FMeshes[g].vertices[v].position = *(FFloat3*)memblock;
			memblock += sizeof(FFloat3);
			fishFile->FMeshes[g].vertices[v].normal = *(FFloat3*)memblock;
			memblock += sizeof(FFloat3);
			fishFile->FMeshes[g].vertices[v].tangent = *(FFloat3*)memblock;
			memblock += sizeof(FFloat3);
			fishFile->FMeshes[g].vertices[v].uv = *(FFloat2*)memblock;
			memblock += sizeof(FFloat2);

			//Write Influences
			fishFile->FMeshes[g].vertices[v].weights.resize(fishFile->FMeshes[g].numInfluences);
			fishFile->FMeshes[g].vertices[v].boneIndex.resize(fishFile->FMeshes[g].numInfluences);
			for(int i = 0; i < fishFile->FMeshes[g].numInfluences; i++)
			{
				fishFile->FMeshes[g].vertices[v].weights[i] = *(float*)memblock;
				memblock += sizeof(float);
				fishFile->FMeshes[g].vertices[v].boneIndex[i] = *(int*)memblock;
				memblock += sizeof(int);
			}
		}
	}
}

void MeshImporter::MapAnimationFile(AnimationFile* animationFile, char* memblock, int numSkeletons)
{
	//Map number of keys
	animationFile->numKeys = *(int*)memblock;
	memblock += sizeof(int);
	
	animationFile->skeletons.resize(numSkeletons);
	for(int s = 0; s < numSkeletons; s++)
	{
		animationFile->skeletons[s].keys.resize(animationFile->numKeys);
		for(int k = 0; k < animationFile->numKeys; k++)
		{
			//Map time
			animationFile->skeletons[s].keys[k].time = *(float*)memblock;
			memblock += sizeof(float);
			//Map numJoints
			animationFile->skeletons[s].keys[k].numJoints = *(int*)memblock;
			memblock += sizeof(int);
			animationFile->skeletons[s].keys[k].joints.resize(animationFile->skeletons[s].keys[k].numJoints);
			//Map joints
			for(int j = 0; j < animationFile->skeletons[s].keys[k].numJoints; j++)
			{
				animationFile->skeletons[s].keys[k].joints[j] = *(FJoint*)memblock;
				memblock += sizeof(FJoint);
			}
		}
	}
}