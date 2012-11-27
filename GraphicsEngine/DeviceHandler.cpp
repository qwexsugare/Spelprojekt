#include "DeviceHandler.h"

DeviceHandler::DeviceHandler(HWND _hWnd, bool _windowed)
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
	sd.Windowed = _windowed;

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

	this->m_device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	this->setupViewPort(&this->m_viewport, this->m_screenSize.x, this->m_screenSize.y);
	this->m_device->RSSetViewports( 1, &this->m_viewport );
}

DeviceHandler::~DeviceHandler()
{
	if(this->m_swapChain)
	{
		this->m_swapChain->SetFullscreenState(false, NULL);
		this->m_swapChain->Release();
	}
	if(this->m_device)
	{
		this->m_device->Release();
	}
}

ID3D10Device* DeviceHandler::getDevice()const
{
	return this->m_device;
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

void DeviceHandler::setInputLayout(ID3D10InputLayout *inputLayout)
{
	this->m_device->IASetInputLayout(inputLayout);
}

void DeviceHandler::setupViewPort(D3D10_VIEWPORT *_viewPort, UINT _width, UINT _height, float _minDepth, float _maxDepth, int _topLeftX, int _topLeftY)
{
	_viewPort->Width = _width;
	_viewPort->Height = _height;
	_viewPort->MinDepth = _minDepth;
	_viewPort->MaxDepth = _maxDepth;
	_viewPort->TopLeftX = _topLeftX;
	_viewPort->TopLeftY = _topLeftX;
}

D3D10_VIEWPORT DeviceHandler::getViewport()
{
	return this->m_viewport;
}

ID3D10Texture2D* DeviceHandler::getBackBuffer()
{
	ID3D10Texture2D* backBuffer;
	this->m_swapChain->GetBuffer( 0, __uuidof( ID3D10Texture2D ), (LPVOID*)&backBuffer );

	return backBuffer;
}