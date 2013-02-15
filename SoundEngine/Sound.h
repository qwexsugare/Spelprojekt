#pragma once

#include "Wu.h"
#include "Framework.h"

class Sound
{
private:
	ALuint m_source;
	bool m_looped;
	bool m_active;
	float m_volume;
	bool m_music;
	bool m_3d;
	WUFLOAT3 m_pos;
public:
	Sound();
	Sound(ALuint _source, float _volume, float _finalVolume, bool _music, bool _3d, const WUFLOAT3& _pos);
	~Sound();
	
	void deactivate();
	float getVolume()const { return m_volume; }
	bool is3d()const;
	bool isActive()const { return this->m_active; }
	bool isMusic()const { return this->m_music; }
	bool isPlaying()const;
	bool isLooped()const { return this->m_looped; }
	void loop();
	void play();
	void setVolume(float _volume, float _finalVolume);
	void setVolume(float _finalVolume);
	void stop();
	void update3dVolume(const WUFLOAT3& _listenerPos);
};