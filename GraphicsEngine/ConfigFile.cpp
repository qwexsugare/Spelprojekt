#include "ConfigFile.h"
#include <fstream>

const float ConfigFile::DEFAULT_SOUND_EFFECTS_VOLUME = 1.0f;
const float ConfigFile::DEFAULT_MUSIC_VOLUME = 1.0f;
const float ConfigFile::DEFAULT_SPEECH_VOLUME = 1.0f;
const string ConfigFile::DEFAULT_PLAYER_NAME = "Player";

ConfigFile::ConfigFile()
{
	this->m_windowed = DEFAULT_WINDOWED;
	this->m_screenSize = INT2(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
	this->m_musicVolume = DEFAULT_MUSIC_VOLUME;
	this->m_soundVolume = DEFAULT_SOUND_EFFECTS_VOLUME;
	this->m_speechVolume = DEFAULT_SPEECH_VOLUME;
	this->m_playerName = DEFAULT_PLAYER_NAME;
	this->m_emilMode = DEFAULT_EMILMODE;
	this->m_shadowMapResolution = DEFAULT_SHADOW_MAP_RESOLUTION;
	this->m_levelMode = DEFAULT_LEVELMODE;
	this->m_diffuse = DEFAULT_DIFFUSE;
	this->m_shadowmap = DEFAULT_SHADOWMAP;
	this->m_SSAO = DEFAULT_SSAO;
	this->m_textureQuality = DEFAULT_TEXTUREQUALITY;
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

int ConfigFile::getShadowMapResolution()const
{
	return this->m_shadowMapResolution;
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
			if(strcmp(key, "texture_quality") == 0)
			{
				int temp;
				sscanf(buf, "texture_quality %d", &temp);
				this->m_textureQuality = temp;
			}
			if(strcmp(key, "ssao") == 0)
			{
				int temp;
				sscanf(buf, "ssao %d", &temp);
				this->m_SSAO = temp;
			}
			if(strcmp(key, "shadowmap") == 0)
			{
				int temp;
				sscanf(buf, "shadowmap %d", &temp);
				this->m_shadowmap = temp;
			}
			if(strcmp(key, "diffuse") == 0)
			{
				int temp;
				sscanf(buf, "diffuse %d", &temp);
				this->m_diffuse = temp;
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
			else if(strcmp(key, "speech_volume") == 0)
			{
				sscanf(buf, "speech_volume %f", &this->m_speechVolume);
			}
			if(strcmp(key, "level_mode") == 0)
			{
				int temp;
				sscanf(buf, "level_mode %d", &temp);
				this->m_levelMode = temp;
			}
			if(strcmp(key, "emil_mode") == 0)
			{
				int temp;
				sscanf(buf, "emil_mode %d", &temp);
				this->m_emilMode = temp;
			}
			else if(strcmp(key, "player_name") == 0)
			{
				/*char RoalndBuf[1024];
				sscanf(buf, "player_name %s", &RoalndBuf);
				m_playerName = string(RoalndBuf);*/

				string pn(buf);
				m_playerName = pn.substr(12, string::npos);
			}
			else if(strcmp(key, "shadow_map") == 0)
			{
				int s;
				sscanf(buf, "shadow_map %d", &s);
				this->m_shadowMapResolution = s;
			}
		}
	}

	stream.close();
}

void ConfigFile::save()
{
	ofstream stream;
	stream.open("config.ini");
	
	int windowedToFile;
	if(m_windowed)
		windowedToFile = 1;
	else
		windowedToFile = 0;

	stream << "resolution " << m_screenSize.x << " " << m_screenSize.y << endl
		<< "windowed " << windowedToFile << endl
		<< "texture_quality " << m_textureQuality << endl
		<< "ssao " << m_SSAO << endl
		<< "shadowmap " << m_shadowmap << endl
		<< "diffuse " << m_diffuse << endl
		<< "music_volume " << m_musicVolume << endl
		<< "sound_volume " << m_soundVolume << endl
		<< "player_name " << m_playerName << endl
		<< "shadow_map " << this->m_shadowMapResolution
		<< "speech_volume " << m_speechVolume << endl
		<< "level_mode " << m_levelMode << endl
		<< "emil_mode " << m_emilMode << endl;
}

void ConfigFile::setPlayerName(string _name)
{
	m_playerName = _name;
}

void ConfigFile::setWindowed(bool _windowed)
{
	m_windowed = _windowed;
}

void ConfigFile::setSSAO(bool _SSAO)
{
	m_SSAO = _SSAO;
}

void ConfigFile::setShadowMapResolution(int _shadowMapResolution)
{
	this->m_shadowMapResolution = _shadowMapResolution;
}

void ConfigFile::setShadowmap(int _shadowmap)
{
	m_shadowmap = _shadowmap;
}

void ConfigFile::setTextureQuality(int _textureQuality)
{
	m_textureQuality = _textureQuality;
}
void ConfigFile::setLevelMode(int _levelMode)
{
	m_levelMode = _levelMode;
}
void ConfigFile::setEmilMode(bool _emilMode)
{
	m_emilMode = _emilMode;
}
void ConfigFile::setDiffuseMode(bool _diffuse)
{
	m_diffuse = _diffuse;
}