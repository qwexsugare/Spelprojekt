#pragma once

#include "stdafx.h"
#include "DataStructures.h"

class DECLDIR ConfigFile
{
private:
	bool m_windowed;
	INT2 m_screenSize;
public:
	static const int DEFAULT_SCREEN_WIDTH = 1920;
	static const int DEFAULT_SCREEN_HEIGHT = 1080;
	static const bool DEFAULT_WINDOWED = false;

	ConfigFile();
	~ConfigFile();

	bool getWindowed()const;
	INT2 getScreenSize()const;
	void load();
};