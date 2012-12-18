#include "SoundEngine.h"

SoundEngine::SoundEngine()
{
	// Initialize Framework
	ALFWInit();
	if (!ALFWInitOpenAL())
	{
		ALFWShutdown();
	}
}

SoundEngine::~SoundEngine()
{
	for(map<string, ALuint>::iterator i = m_buffers.begin(); i != m_buffers.end(); i++)
		alDeleteBuffers(1, &i->second);
	for(map<int, ALuint>::iterator i = m_sources.begin(); i != m_sources.end(); i++)
		alDeleteSources(1, &i->second);
}

int SoundEngine::createSoundHandle(string _filename)
{
	int soundHandle;

	ALuint buffer = this->getWavBuffer(_filename);
	ALuint source;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);

	this->m_sources.insert(pair<int, ALuint>(soundHandle, source));

	return soundHandle;
}

ALuint SoundEngine::getWavBuffer(string _filename)
{
	ALuint result;

	bool found = false;
	for(map<string, ALuint>::iterator i = m_buffers.begin(); i != this->m_buffers.end(); i++)
	{
		if(i->first == _filename)
		{
			found = true;

			result = i->second;
		}
	}

	if(!found)
	{
		ALuint buffer;
		alGenBuffers(1, &buffer);
		ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(_filename.c_str()), buffer);
		this->m_buffers.insert(pair<string, ALuint>(_filename, buffer));

		result = buffer;
	}

	return result;
}

void SoundEngine::inactivate(int _handle)
{

}

bool SoundEngine::isPlaying(int _handle)const
{
	bool result;

	ALint iState;
	alGetSourcei(this->m_sources.at(_handle), AL_SOURCE_STATE, &iState);
	if(iState == AL_PLAYING)
		result = true;
	else
		result = false;

	return result;
}

void SoundEngine::play(int _handle)const
{
	alSourcePlay(this->m_sources.at(_handle));
}

void SoundEngine::stop(int _handle)const
{
	alSourceStop(this->m_sources.at(_handle));
}