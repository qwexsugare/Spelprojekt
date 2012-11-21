#include "TextureHolder.h"


TextureHolder::TextureHolder(ID3D10Device *_device)
{
	this->m_device = _device;
	this->m_textures = map<string, ID3D10ShaderResourceView*>();
}

TextureHolder::~TextureHolder(void)
{

}

ID3D10ShaderResourceView* TextureHolder::getTexture(string filename)
{
	// Check if a texture with the requested texture filename is already loaded.
	map<string, ID3D10ShaderResourceView*>::iterator searchResult = this->m_textures.find(filename);

	if(searchResult == this->m_textures.end())
	{
		// Load new texture.
		ID3D10ShaderResourceView* resource = NULL;
		D3DX10_IMAGE_LOAD_INFO loadInfo;
		ZeroMemory(&loadInfo, sizeof(D3DX10_IMAGE_LOAD_INFO));
		loadInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE;
		loadInfo.Format = DXGI_FORMAT_BC1_UNORM;
		D3DX10CreateShaderResourceViewFromFile(this->m_device, filename.c_str(), &loadInfo, NULL, &resource, NULL);

		// Add the new texture to the texture vector
		this->m_textures.insert(this->m_textures.begin(), pair<string, ID3D10ShaderResourceView*>(filename, resource));
	}
	
	ID3D10ShaderResourceView* result = this->m_textures[filename];

	return result;
}