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
public:
	DeviceHandler(HWND _hWnd, bool _windowed);
	~DeviceHandler();

	ID3D10Device* getDevice()const;
	HRESULT present()const;

	D3DXVECTOR2 getScreenSize();

	void setInputLayout(ID3D10InputLayout *inputLayout);
};