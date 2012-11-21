// MÖG

#pragma once

#include "stdafx.h"

class ConfigFile
{
private:
	bool m_windowed;
	D3DXVECTOR2 m_screenSize;
public:
	static const int DEFAULT_SCREEN_WIDTH = 1920;
	static const int DEFAULT_SCREEN_HEIGHT = 1080;
	static const bool DEFAULT_WINDOWED = false;

	ConfigFile();
	~ConfigFile();
};