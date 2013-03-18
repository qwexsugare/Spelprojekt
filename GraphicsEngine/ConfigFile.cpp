#include "ConfigFile.h"
#include <fstream>

const float ConfigFile::DEFAULT_SOUND_EFFECTS_VOLUME = 1.0f;
const float ConfigFile::DEFAULT_MUSIC_VOLUME = 1.0f;
const string ConfigFile::DEFAULT_PLAYER_NAME = "Player";

ConfigFile::ConfigFile()
{
	this->m_windowed = DEFAULT_WINDOWED;
	this->m_screenSize = INT2(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
	this->m_musicVolume = DEFAULT_MUSIC_VOLUME;
	this->m_soundVolume = DEFAULT_SOUND_EFFECTS_VOLUME;
	this->m_playerName = DEFAULT_PLAYER_NAME;
}

ConfigFile::~ConfigFile()
{

}

string ConfigFile::getPlayerName()const
{
	return m_playerName;
}

INT2 ConfigFile::getScreenSize()const
{
	return this->m_screenSize;
}

bool ConfigFile::getWindowed()const
{
	return this->m_windowed;
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
				int x, y;
				sscanf(buf, "resolution %d %d", &x, &y);
				this->m_screenSize.x = x;
				this->m_screenSize.y = y;
			}
			else if(strcmp(key, "music_volume") == 0)
			{
				sscanf(buf, "music_volume %f", &this->m_musicVolume);
			}
			else if(strcmp(key, "sound_volume") == 0)
			{
				sscanf(buf, "sound_volume %f", &this->m_soundVolume);
			}
			else if(strcmp(key, "player_name") == 0)
			{
				char RoalndBuf[1024];
				sscanf(buf, "player_name %s", &RoalndBuf);
				m_playerName = string(RoalndBuf);
			}
		}
	}

	stream.close();
}

void ConfigFile::save()
{
	ofstream stream;
	stream.open("config.ini");
	
	stream << "resolution " << m_screenSize.x << " " << m_screenSize.y << endl
		<< "windowed " << m_windowed << endl
		<< "music_volume " << m_musicVolume << endl
		<< "sound_volume " << m_soundVolume << endl
		<< "player_name " << m_playerName;
}

void ConfigFile::setPlayerName(string _name)
{
	m_playerName = _name;
}