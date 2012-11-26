#include "DeviceHandler.h"

DeviceHandler::DeviceHandler(HWND _hWnd)
{
	RECT rc;
	GetClientRect(_hWnd, &rc);
	this->m_screenSize.x = (float)(rc.right - rc.left);
	this->m_screenSize.y = (float)(rc.bottom - rc.top);

	this->m_device = NULL;
	this->m_swapChain = NULL;

	this->m_driverType = D3D10_DRIVER_TYPE_NULL;
	
	HRESULT hr;

	UINT createDeviceFlags = 0;
	#ifdef _DEBUG
		createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
	#endif

	D3D10_DRIVER_TYPE driverTypes[] = 
	{
		D3D10_DRIVER_TYPE_HARDWARE,
		D3D10_DRIVER_TYPE_REFERENCE,
	};

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = (int)this->m_screenSize.x;
	sd.BufferDesc.Height = (int)this->m_screenSize.y;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);
	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		this->m_driverType = driverTypes[driverTypeIndex];
		hr = D3D10CreateDeviceAndSwapChain( NULL, this->m_driverType, NULL, createDeviceFlags, D3D10_SDK_VERSION, &sd, &this->m_swapChain, &this->m_device );

		if(SUCCEEDED(hr))
		{
			break;
		}
	}

	this->m_device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	this->m_renderTarget = this->createRenderTargetView();
	this->m_depthStencilView = this->createDepthStencilView(this->m_screenSize);
}

DeviceHandler::~DeviceHandler()
{
	if(this->m_device)
	{
		this->m_device->Release();
	}
	if(this->m_swapChain)
	{
		this->m_swapChain->Release();
	}
}

ID3D10Device* DeviceHandler::getDevice()const
{
	return this->m_device;
}


ID3D10RenderTargetView *DeviceHandler::createRenderTargetView()
{
	// Create a render target view
	ID3D10Texture2D* pBackBuffer;
	ID3D10RenderTargetView *renderTarget = NULL;
	this->m_swapChain->GetBuffer( 0, __uuidof( ID3D10Texture2D ), (LPVOID*)&pBackBuffer );
	this->m_device->CreateRenderTargetView( pBackBuffer, NULL, &renderTarget );
	pBackBuffer->Release();

	return renderTarget;
}

ID3D10DepthStencilView *DeviceHandler::createDepthStencilView(D3DXVECTOR2 size)
{
	// Create depth stencil texture
	ID3D10Texture2D* stencilBuffer;
	ID3D10DepthStencilView *depthStencil = NULL;
	D3D10_TEXTURE2D_DESC descDepth;
	descDepth.Width = size.x;
	descDepth.Height = size.y;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	this->m_device->CreateTexture2D( &descDepth, NULL, &stencilBuffer );

	// Create the depth stencil view
	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	this->m_device->CreateDepthStencilView( stencilBuffer, &descDSV, &depthStencil);

	return depthStencil;
}

HRESULT DeviceHandler::present()const
{
	if(FAILED(this->m_swapChain->Present(0, 0)))
	{
		return E_FAIL;
	}

	return S_OK;
}

D3DXVECTOR2 DeviceHandler::getScreenSize()
{
	return this->m_screenSize;
}

ID3D10RenderTargetView *DeviceHandler::getForwardRenderTarget()
{
	return this->m_renderTarget;
}

ID3D10DepthStencilView *DeviceHandler::getForwardDepthStencil()
{
	return this->m_depthStencilView;
}

void DeviceHandler::setInputLayout(ID3D10InputLayout *inputLayout)
{
	this->m_device->IASetInputLayout(inputLayout);
}