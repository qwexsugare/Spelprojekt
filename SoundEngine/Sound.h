#pragma once

#include "Framework.h"

class Sound
{
private:
	ALuint m_source;
	bool m_looped;
	bool m_active;
	float m_volume;
	bool m_music;
public:
	Sound();
	Sound(ALuint _source, float _volume, bool _music);
	~Sound();

	void deactivate();
	bool isActive()const { return this->m_active; }
	bool isMusic()const { return this->m_music; }
	bool isPlaying()const;
	bool isLooped()const { return this->m_looped; }
	void loop();
	void play();
	void setVolume(float _volume);
	void stop();
};