#include "ConfigFile.h"
#include <fstream>

ConfigFile::ConfigFile()
{
	bool windowedIsSet = false;
	bool resolutionIsSet = false;
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
				windowedIsSet = true;
			}
			else if(strcmp(key, "resolution") == 0)
			{
				sscanf(buf, "resolution %d %d", &this->m_screenSize.x, &this->m_screenSize.y);
				resolutionIsSet = true;
			}
		}
	}

	// If the file didnt open, use default values
	if(!windowedIsSet)
		this->m_windowed = DEFAULT_WINDOWED;
	if(!resolutionIsSet)
	{
		this->m_screenSize.x = DEFAULT_SCREEN_WIDTH;
		this->m_screenSize.y = DEFAULT_SCREEN_HEIGHT;
	}

	stream.close();
}

ConfigFile::~ConfigFile()
{

}