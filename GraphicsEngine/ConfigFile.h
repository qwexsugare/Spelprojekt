// MÖG

#pragma once

#include "stdafx.h"

class DECLDIR ConfigFile
{
private:
	bool m_windowed;
	D3DXVECTOR2* m_screenSize;
public:
	static const int DEFAULT_SCREEN_WIDTH = 1920;
	static const int DEFAULT_SCREEN_HEIGHT = 1080;
	static const bool DEFAULT_WINDOWED = false;

	ConfigFile();
	~ConfigFile();

	bool getWindowed()const { return this->m_windowed; }
	const D3DXVECTOR2* getScreenSize()const { return this->m_screenSize; }
	void load();
};