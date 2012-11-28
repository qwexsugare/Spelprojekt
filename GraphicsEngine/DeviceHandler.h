#pragma once

#include "stdafx.h"
#include "DataStructures.h"
#include "Mesh.h"
#include "VertexStructs.h"

class DeviceHandler
{
private:
	D3D10_DRIVER_TYPE m_driverType;
	ID3D10Device* m_device;
	IDXGISwapChain*	m_swapChain;
	HWND m_hWnd;
	INT2 m_screenSize;
	D3D10_VIEWPORT m_viewport;

	ID3D10Buffer *m_currentBuffer;

	void setupViewPort(D3D10_VIEWPORT *viewPort, UINT width, UINT height, float minDepth = 0.0f, float maxDepth = 1.0f, int topLeftX = 0, int topLeftY = 0);
public:
	DeviceHandler(HWND _hWnd, bool _windowed, INT2 _screenSize);
	~DeviceHandler();

	ID3DX10Font* createFont();
	ID3D10Texture2D* getBackBuffer();
	D3D10_VIEWPORT getViewport();
	ID3D10Device* getDevice()const;
	HRESULT present()const;

	INT2 getScreenSize();

	void setInputLayout(ID3D10InputLayout *inputLayout);
	void setVertexBuffer(ID3D10Buffer *buffer);
};