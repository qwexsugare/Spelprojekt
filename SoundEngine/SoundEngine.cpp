#include "SoundEngine.h"
#include <vector>

SoundEngine::SoundEngine()
{
	this->m_handleCounter = 0;

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
	for(map<int, Sound*>::iterator i = m_sounds.begin(); i != m_sounds.end(); i++)
		delete i->second;
	
	ALFWShutdown();
}

int SoundEngine::createSoundHandle(string _filename)
{
	int soundHandle = this->m_handleCounter++;

	ALuint buffer = this->getWavBuffer(_filename);
	ALuint source;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	
	this->m_sounds.insert(pair<int, Sound*>(soundHandle, new Sound(source)));

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

void SoundEngine::deactivate(int _handle)
{
	map<int, Sound*>::iterator isd = m_sounds.find(_handle);
	if(isd != m_sounds.end())
		isd->second->deactivate();
}

bool SoundEngine::isPlaying(int _handle)
{
	bool result;

	map<int, Sound*>::iterator isd = m_sounds.find(_handle);
	if(isd != m_sounds.end())
		result = this->m_sounds.at(_handle)->isPlaying();
	else
		result = false;

	return result;
}

void SoundEngine::loop(int _handle)
{
	this->m_sounds.at(_handle)->loop();
}

void SoundEngine::play(int _handle)const
{
	this->m_sounds.at(_handle)->play();
}

void SoundEngine::stop(int _handle)const
{
	this->m_sounds.at(_handle)->stop();
}

void SoundEngine::update()
{
	vector<map<int, Sound*>::iterator> removeIndices;

	for(map<int, Sound*>::iterator i = m_sounds.begin(); i != m_sounds.end(); i++)
	{
		// If the sound is active, replay it
		if(i->second->isActive())
		{
			if(i->second->isLooped())
			{
				if(!i->second->isPlaying())
				{
					i->second->play();
				}
			}
		}
		// Else check if its not playing and if so, add it to delete vector
		else
		{
			if(!i->second->isPlaying())
			{
				removeIndices.push_back(i);
			}
		}
	}
	
	// Remove some sounds
	for(int i = 0; i < removeIndices.size(); i++)
	{
		delete removeIndices[i]->second;
		m_sounds.erase(removeIndices[i]);
	}
}