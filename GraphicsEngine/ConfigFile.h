#pragma once

#include "stdafx.h"
#include "DataStructures.h"

class DECLDIR ConfigFile
{
private:
	bool m_windowed;
	INT2 m_screenSize;
	float m_musicVolume;
	float m_soundVolume;
	string m_playerName;
public:
	static const int DEFAULT_SCREEN_WIDTH = 1920;
	static const int DEFAULT_SCREEN_HEIGHT = 1080;
	static const float DEFAULT_SOUND_EFFECTS_VOLUME;
	static const float DEFAULT_MUSIC_VOLUME;
	static const bool DEFAULT_WINDOWED = false;
	static const string DEFAULT_PLAYER_NAME;

	ConfigFile();
	~ConfigFile();

	bool getWindowed()const;
	INT2 getScreenSize()const;
	float getMusicVolume()const { return this->m_musicVolume; }
	string getPlayerName()const;
	float getSoundVolume()const { return this->m_soundVolume; }
	void setMusicVolume(float _val) { m_musicVolume = _val; }
	void setPlayerName(string _name);
	void setSoundVolume(float _val) { m_soundVolume = _val; }
	void setScreenSize(INT2	_size) { m_screenSize = _size; }
	void load();
	void save();
};