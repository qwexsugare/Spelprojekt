#pragma once

#include "Framework.h"

class Sound
{
private:
	ALuint m_source;
	bool m_looped;
	bool m_active;
public:
	Sound();
	Sound(ALuint _source);
	~Sound();

	void deactivate();
	bool isActive()const { return this->m_active; }
	bool isPlaying()const;
	bool isLooped()const { return this->m_looped; }
	void loop();
	void play();
	void stop();
};