#include "ResourceHolder.h"

ResourceHolder::ResourceHolder()
{

}
	
ResourceHolder::ResourceHolder(ID3D10Device* _device)
{
	this->m_device = _device;
	this->m_textureHolder = new TextureHolder(this->m_device);
}

ResourceHolder::~ResourceHolder()
{
	map<string, Mesh*>::iterator m = this->m_meshes.begin();

	while(m != this->m_meshes.end())
	{
		delete (*m).second;
		m++;
	}

	delete this->m_textureHolder;
}

Mesh* ResourceHolder::getMesh(string filename)
{
	// Check if a texture with the requested texture filename is already loaded.
	map<string, Mesh*>::iterator searchResult = this->m_meshes.find(filename);

	if(searchResult == this->m_meshes.end())
	{
		// Load new texture.
		Mesh *m = MeshImporter::loadOBJMesh(this->m_device, this->m_textureHolder, filename);

		// Add the new texture to the texture vector
		this->m_meshes.insert(this->m_meshes.begin(), pair<string, Mesh*>(filename, m));
	}
	
	Mesh* result = this->m_meshes[filename];

	return result;
}