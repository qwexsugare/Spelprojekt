#include "Sound.h"

Sound::Sound()
{

}

Sound::Sound(ALuint _source)
{
	this->m_source = _source;
	this->m_looped = false;
	this->m_active = true;
}

Sound::~Sound()
{
	alDeleteSources(1, &this->m_source);
}

void Sound::deactivate()
{
	this->m_active = false;
}

bool Sound::isPlaying()const
{
	bool result;

	ALint iState;
	alGetSourcei(this->m_source, AL_SOURCE_STATE, &iState);
	if(iState == AL_PLAYING)
		result = true;
	else
		result = false;

	return result;
}

void Sound::loop()
{
	this->m_looped = true;
	alSourcePlay(this->m_source);
}

void Sound::play()
{
	alSourcePlay(this->m_source);
}
	
void Sound::stop()
{
	this->m_looped = false;
	alSourceStop(this->m_source);
}