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
		D3DX10CreateShaderResourceViewFromFile(this->m_device, filename.c_str(), NULL, NULL, &resource, NULL);

		// Add the new texture to the texture vector
		this->m_textures.insert(this->m_textures.begin(), pair<string, ID3D10ShaderResourceView*>(filename, resource));
	}
	
	ID3D10ShaderResourceView* result = this->m_textures[filename];

	return result;
}

TexturePack* TextureHolder::getBoneTexture()
{	
	ID3D10Texture1D* boneTexture = NULL;

	ID3D10ShaderResourceView* resource = NULL;

	HRESULT hr = S_OK;
	D3D10_TEXTURE1D_DESC t1dd;
	ZeroMemory(&t1dd, sizeof(t1dd));
	t1dd.Width			= 4 * MAX_BONES;
	t1dd.ArraySize		= 1;
	t1dd.Format			= DXGI_FORMAT_R32G32B32A32_FLOAT;
	t1dd.MipLevels		= 1;
	t1dd.BindFlags		= D3D10_BIND_SHADER_RESOURCE;
	t1dd.Usage			= D3D10_USAGE_DYNAMIC;
	t1dd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	t1dd.MiscFlags		= 0;

	hr = m_device->CreateTexture1D(&t1dd, NULL, &boneTexture);
	if(FAILED(hr))
		MessageBox(NULL, "Failed to create BoneTexture", "TextureHolder.cpp", 0);

	D3D10_SHADER_RESOURCE_VIEW_DESC bsrvd;
	ZeroMemory(&bsrvd, sizeof(bsrvd));
	bsrvd.Format				= t1dd.Format;
	bsrvd.Texture2D.MipLevels	= t1dd.MipLevels;
	bsrvd.ViewDimension			= D3D10_SRV_DIMENSION_TEXTURE1D;
	
	hr = m_device->CreateShaderResourceView(boneTexture, &bsrvd, &resource);
	if(FAILED(hr))
		MessageBox(NULL, "Failed to create BoneResourceView", "TextureHolder.cpp", 0);
	

	
	TexturePack* result = new TexturePack();
	result->resourceView = resource;
	result->texture = boneTexture;

	return result;
}