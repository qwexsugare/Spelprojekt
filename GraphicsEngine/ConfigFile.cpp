#include "ConfigFile.h"
#include <fstream>

ConfigFile::ConfigFile()
{
	this->m_windowed = DEFAULT_WINDOWED;
	this->m_screenSize = new D3DXVECTOR2(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
}

ConfigFile::~ConfigFile()
{
	delete this->m_screenSize;
}

void ConfigFile::load()
{
	// Open and read config file
	ifstream stream;
	stream.open("config.ini");
	if(stream.is_open())
	{
		while(!stream.eof())
		{
			char buf[1024];
			char key[100];
			stream.getline(buf, 1024);
			sscanf(buf, "%s", key);
			if(strcmp(key, "windowed") == 0)
			{
				int temp;
				sscanf(buf, "windowed %d", &temp);
				this->m_windowed = temp;
			}
			else if(strcmp(key, "resolution") == 0)
			{
				sscanf(buf, "resolution %d %d", &this->m_screenSize->x, &this->m_screenSize->y);
			}
		}
	}

	stream.close();
}