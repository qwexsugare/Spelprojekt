#include "RenderTarget.h"

RenderTarget::RenderTarget(ID3D10Device *device, INT2 _size)
{
	this->m_size = _size;

	//Initalize the member variables

	// Create the render targets
	D3D10_TEXTURE2D_DESC renderTargetDesc;
	renderTargetDesc.Width = this->m_size.x;
	renderTargetDesc.Height = this->m_size.y;
	renderTargetDesc.MipLevels = 1;
	renderTargetDesc.ArraySize = 1;
	renderTargetDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	renderTargetDesc.SampleDesc.Count = 1;
	renderTargetDesc.SampleDesc.Quality = 0;
	renderTargetDesc.Usage = D3D10_USAGE_DEFAULT;
	renderTargetDesc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
	renderTargetDesc.CPUAccessFlags = 0;
	renderTargetDesc.MiscFlags = 0;

	device->CreateTexture2D( &renderTargetDesc, NULL, &this->m_texture);

    // Create the render target view
    D3D10_RENDER_TARGET_VIEW_DESC descRT;
    descRT.Format = renderTargetDesc.Format;
    descRT.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
    descRT.Texture2D.MipSlice = 0;

	device->CreateRenderTargetView(this->m_texture, &descRT, &this->m_renderTargetView);

	//Create shader resource view
	D3D10_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory( &srvDesc, sizeof( srvDesc ) );
    srvDesc.Format = renderTargetDesc.Format;
    srvDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    srvDesc.Texture2D.MostDetailedMip = 0;

	device->CreateShaderResourceView(this->m_texture, &srvDesc, &this->m_shaderResource);
}

RenderTarget::RenderTarget(ID3D10Device *device, ID3D10Texture2D *backBuffer)
{
	this->m_shaderResource = NULL;
	this->m_texture = backBuffer;
	device->CreateRenderTargetView( backBuffer, NULL, &this->m_renderTargetView );
	//device->CreateShaderResourceView( backBuffer, NULL, &this->m_shaderResource );
	this->m_shaderResource = NULL;
}

RenderTarget::~RenderTarget()
{
	if(this->m_shaderResource != NULL)
	{
		this->m_shaderResource->Release();
	}

	this->m_renderTargetView->Release();
	this->m_texture->Release();
}

ID3D10RenderTargetView **RenderTarget::getRenderTargetView()
{
	return &this->m_renderTargetView;
}

ID3D10Texture2D *RenderTarget::getTexture()
{
	return this->m_texture;
}

ID3D10ShaderResourceView *RenderTarget::getShaderResource()
{
	return this->m_shaderResource;
}

void RenderTarget::clear(ID3D10Device *device)
{
	const FLOAT clearColor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	device->ClearRenderTargetView(this->m_renderTargetView, clearColor); 
}