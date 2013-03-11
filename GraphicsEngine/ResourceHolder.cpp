#include "ResourceHolder.h"

ResourceHolder::ResourceHolder()
{

}
	
ResourceHolder::ResourceHolder(ID3D10Device* _device)
{
	this->m_device = _device;
	this->m_textureHolder = new TextureHolder(this->m_device);
	this->m_animationHolder = new AnimationHolder();
}

ResourceHolder::~ResourceHolder()
{
	map<string, Mesh*>::iterator m = this->m_meshes.begin();

	while(m != this->m_meshes.end())
	{
		delete (*m).second;
		m++;
	}	
	map<string, ParticleEffect*>::iterator p = this->m_particleEffects.begin();

	while(p != this->m_particleEffects.end())
	{
		delete (*p).second;
		p++;
	}
	int lol = 0;
	delete this->m_textureHolder;
	delete this->m_animationHolder;
}

Mesh* ResourceHolder::getMesh(string filename)
{
	// Check if a texture with the requested texture filename is already loaded.
	map<string, Mesh*>::iterator searchResult = this->m_meshes.find(filename);

	if(searchResult == this->m_meshes.end())
	{
		// Load new texture.
		Mesh *m = MeshImporter::LoadFishes(this->m_device, this->m_textureHolder, this->m_animationHolder, filename);

		// Add the new texture to the texture vector
		this->m_meshes.insert(this->m_meshes.begin(), pair<string, Mesh*>(filename, m));
	}
	
	Mesh* result = this->m_meshes[filename];
	return result;
}

ParticleEffect* ResourceHolder::getParticleEffect(string _filename)
{
	map<string, ParticleEffect*>::iterator searchResult = this->m_particleEffects.find(_filename);

	if(searchResult == this->m_particleEffects.end())
	{
		ParticleEffect* p = ParticleEffectImporter::loadParticleEffect(_filename);
		this->m_particleEffects.insert(pair<string, ParticleEffect*>(_filename, p));
	}
	ParticleEffect* pe = this->m_particleEffects[_filename];
	return pe;
}

TextureHolder *ResourceHolder::getTextureHolder()
{
	return this->m_textureHolder;
}

AnimationHolder *ResourceHolder::getAnimationHolder()
{
	return this->m_animationHolder;
}

Animation ResourceHolder::getAnimation(string name)
{
	return this->m_animationHolder->getAnimation(name);
}

string ResourceHolder::getFilename(Mesh *_mesh)
{
	// Check if a texture with the requested texture filename is already loaded.
	map<string, Mesh*>::iterator searchResult = this->m_meshes.begin();
	string result = "";

	while(searchResult != this->m_meshes.end())
	{
		if(searchResult->second == _mesh)
		{
			result = searchResult->first;
		}

		searchResult++;
	}

	return result;
}