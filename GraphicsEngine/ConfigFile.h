#pragma once

#include "stdafx.h"
#include "DataStructures.h"

class DECLDIR ConfigFile
{
private:
	bool m_windowed;
	bool m_SSAO;
	bool m_diffuse;
	bool m_emilMode;
	int m_levelMode;
	int m_shadowmap;
	int m_textureQuality;
	INT2 m_screenSize;
	float m_musicVolume;
	float m_soundVolume;
	float m_speechVolume;
	string m_playerName;
	int m_shadowMapResolution;
public:
	static const int DEFAULT_SCREEN_WIDTH = 1920;
	static const int DEFAULT_SCREEN_HEIGHT = 1080;
	static const float DEFAULT_SOUND_EFFECTS_VOLUME;
	static const float DEFAULT_MUSIC_VOLUME;
	static const float DEFAULT_SPEECH_VOLUME;
	static const bool DEFAULT_WINDOWED = false;
	static const bool DEFAULT_SSAO = false;
	static const bool DEFAULT_DIFFUSE = false;
	static const bool DEFAULT_EMILMODE = 0;
	static const int DEFAULT_LEVELMODE = 1;
	static const int DEFAULT_TEXTUREQUALITY = 2;
	static const int DEFAULT_SHADOWMAP = 2;
	static const string DEFAULT_PLAYER_NAME;
	static const int DEFAULT_SHADOW_MAP_RESOLUTION = 512;

	ConfigFile();
	~ConfigFile();

	bool getWindowed()const;
	INT2 getScreenSize()const;
	float getMusicVolume()const { return this->m_musicVolume; }
	string getPlayerName()const;
	float getSoundVolume()const { return this->m_soundVolume; }
	float getSpeechVolume()const { return this->m_speechVolume; }
	int getShadowMapResolution()const;
	bool getSSAO()const {return this->m_SSAO;}
	bool getDiffuseMode()const {return this->m_diffuse;}
	bool getEmilMode()const {return this->m_emilMode;}
	int getLevelMode()const {return this->m_levelMode;}
	int getTextureQuality()const {return this->m_textureQuality;}
	int getShadowmap()const {return this->m_shadowmap;}
	void setMusicVolume(float _val) { m_musicVolume = _val; }
	void setPlayerName(string _name);
	void setSoundVolume(float _val) { m_soundVolume = _val; }
	void setSpeechVolume(float _val) { m_speechVolume = _val; }
	void setScreenSize(INT2	_size) { m_screenSize = _size; }
	void setWindowed(bool _windowed);
	void setSSAO(bool _SSAO);
	void setShadowMapResolution(int _shadowMapResolution);
	void setShadowmap(int _shadowmap);
	void setTextureQuality(int _textureQuality);
	void setLevelMode(int _levelMode);
	void setEmilMode(bool _emilMode);
	void setDiffuseMode(bool _diffuse);
	void load();
	void save();
};