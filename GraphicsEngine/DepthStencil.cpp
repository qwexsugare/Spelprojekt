#include "DepthStencil.h"

DepthStencil::DepthStencil(ID3D10Device *device, INT2 _size, bool stencil)
{
	this->m_size = _size;

	if(stencil == true)
	{
		this->createDepthStencil(device);
	}
	else
	{
		this->createShadowMap(device);
	}
}

DepthStencil::~DepthStencil()
{
	if(this->m_shaderResource)
	{
		this->m_shaderResource->Release();
	}
	this->m_depthStencilView->Release();
	this->m_texture->Release();
}

void DepthStencil::createDepthStencil(ID3D10Device *device)
{
	//Create the depth stencil texture
	D3D10_TEXTURE2D_DESC shadowDescDepth;
	shadowDescDepth.Width = this->m_size.x;
	shadowDescDepth.Height = this->m_size.y;
	shadowDescDepth.MipLevels = 1;
	shadowDescDepth.ArraySize = 1;
	shadowDescDepth.Format = DXGI_FORMAT_R24G8_TYPELESS;
	shadowDescDepth.SampleDesc.Count = 1;
	shadowDescDepth.SampleDesc.Quality = 0;
	shadowDescDepth.Usage = D3D10_USAGE_DEFAULT;
	shadowDescDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL | D3D10_BIND_SHADER_RESOURCE;
	shadowDescDepth.CPUAccessFlags = 0;
	shadowDescDepth.MiscFlags = 0;

	if( FAILED(device->CreateTexture2D( &shadowDescDepth, NULL, &this->m_texture )))
	{
		MessageBox( 0, "Unable to create Depth Stencil Texture.", "Error", 0 );
	}

	D3D10_DEPTH_STENCIL_DESC dsDesc;
	
	// Create depth stencil state
	ID3D10DepthStencilState* pDSState;
	device->CreateDepthStencilState(&dsDesc, &pDSState);
	device->OMSetDepthStencilState(pDSState, 1);

	//Create the depth stencil view from the texture
	D3D10_DEPTH_STENCIL_VIEW_DESC shadowDescDSV;
	shadowDescDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	shadowDescDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	shadowDescDSV.Texture2D.MipSlice = 0;

	if(FAILED(device->CreateDepthStencilView(this->m_texture, &shadowDescDSV, &this->m_depthStencilView )))
	{
		MessageBox( 0, "Unable to create Depth Stencil View.", "Error", 0 );
	}

	//Create the shader-resource view from the texture
	D3D10_SHADER_RESOURCE_VIEW_DESC srDesc;
	srDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MostDetailedMip = 0;
	srDesc.Texture2D.MipLevels = 1;

	HRESULT hr = device->CreateShaderResourceView(this->m_texture, &srDesc, &this->m_shaderResource);

	if(FAILED(hr))
	{
		MessageBox( 0, "Unable to create Depth Stencil Shader Resource.", "Error", 0 );
	}
}

void DepthStencil::createShadowMap(ID3D10Device *device)
{
	//Create the depth stencil texture
	D3D10_TEXTURE2D_DESC shadowDescDepth;
	shadowDescDepth.Width = this->m_size.x;
	shadowDescDepth.Height = this->m_size.y;
	shadowDescDepth.MipLevels = 1;
	shadowDescDepth.ArraySize = 1;
	shadowDescDepth.Format = DXGI_FORMAT_R32_TYPELESS;
	shadowDescDepth.SampleDesc.Count = 1;
	shadowDescDepth.SampleDesc.Quality = 0;
	shadowDescDepth.Usage = D3D10_USAGE_DEFAULT;
	shadowDescDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL | D3D10_BIND_SHADER_RESOURCE;
	shadowDescDepth.CPUAccessFlags = 0;
	shadowDescDepth.MiscFlags = 0;

	if( FAILED(device->CreateTexture2D( &shadowDescDepth, NULL, &this->m_texture )))
	{
		MessageBox( 0, "Unable to create Depth Stencil Texture.", "Error", 0 );
	}

	D3D10_DEPTH_STENCIL_DESC dsDesc;

	//Create the depth stencil view from the texture
	D3D10_DEPTH_STENCIL_VIEW_DESC shadowDescDSV;
	shadowDescDSV.Format = DXGI_FORMAT_D32_FLOAT;
	shadowDescDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	shadowDescDSV.Texture2D.MipSlice = 0;

	if(FAILED(device->CreateDepthStencilView(this->m_texture, &shadowDescDSV, &this->m_depthStencilView )))
	{
		MessageBox( 0, "Unable to create Depth Stencil View.", "Error", 0 );
	}

	//Create the shader-resource view from the texture
	D3D10_SHADER_RESOURCE_VIEW_DESC srDesc;
	srDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MostDetailedMip = 0;
	srDesc.Texture2D.MipLevels = 1;

	if(FAILED(device->CreateShaderResourceView(this->m_texture, &srDesc, &this->m_shaderResource)))
	{
		MessageBox( 0, "Unable to create Depth Stencil Shader Resource.", "Error", 0 );
	}
}

ID3D10DepthStencilView *DepthStencil::getDepthStencilView()
{
	return this->m_depthStencilView;
}

ID3D10Texture2D *DepthStencil::getTexture()
{
	return this->m_texture;
}

ID3D10ShaderResourceView *DepthStencil::getShaderResource()
{
	return this->m_shaderResource;
}

void DepthStencil::clear(ID3D10Device* _device)
{
	_device->ClearDepthStencilView(this->m_depthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
}