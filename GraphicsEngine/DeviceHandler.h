#pragma once

#include "stdafx.h"

class DeviceHandler
{
private:
	D3D10_DRIVER_TYPE m_driverType;
	ID3D10Device* m_device;
	IDXGISwapChain*	m_swapChain;
	HWND m_hWnd;
	D3DXVECTOR2 m_screenSize;
	D3D10_VIEWPORT m_viewport;

	void setupViewPort(D3D10_VIEWPORT *viewPort, UINT width, UINT height, float minDepth = 0.0f, float maxDepth = 1.0f, int topLeftX = 0, int topLeftY = 0);
public:
	DeviceHandler(HWND _hWnd, bool _windowed);
	~DeviceHandler();

	ID3D10Texture2D* getBackBuffer();
	D3D10_VIEWPORT getViewport();
	ID3D10Device* getDevice()const;
	HRESULT present()const;

	D3DXVECTOR2 getScreenSize();

	ID3D10InputLayout* createInputLayout(D3D10_PASS_DESC _passDescription);
	void setInputLayout(ID3D10InputLayout *inputLayout);
};