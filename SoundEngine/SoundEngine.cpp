#include "SoundEngine.h"
#include <vector>

SoundEngine::SoundEngine()
{
	this->m_handleCounter = INT_MIN;
	this->m_musicVolume = 1.0f;
	this->m_soundVolume = 1.0f;

	// Initialize Framework
	ALFWInit();
	if (!ALFWInitOpenAL())
	{
		ALFWShutdown();
	}
}

SoundEngine::SoundEngine(float _musicVolume, float _soundVolume)
{
	this->m_handleCounter = INT_MIN;
	this->m_musicVolume = _musicVolume;
	this->m_soundVolume = _soundVolume;

	// Initialize Framework
	ALFWInit();
	if (!ALFWInitOpenAL())
	{
		ALFWShutdown();
	}
}

SoundEngine::~SoundEngine()
{
	for(map<int, Sound*>::iterator i = m_sounds.begin(); i != m_sounds.end(); i++)
		delete i->second;
	for(map<string, ALuint>::iterator i = m_buffers.begin(); i != m_buffers.end(); i++)
		alDeleteBuffers(1, &i->second);
	
	ALFWShutdownOpenAL();
	ALFWShutdown();
}

void SoundEngine::clear()
{
	for(map<string, ALuint>::iterator i = m_buffers.begin(); i != m_buffers.end(); i++)
		alDeleteBuffers(1, &i->second);
}

int SoundEngine::createSoundHandle(string _filename, bool _music, bool _3d, WUFLOAT3 _pos, float _volume)
{
	int soundHandle = this->m_handleCounter++;
	if(this->m_handleCounter == INT_MAX)
		this->m_handleCounter = INT_MIN;

	ALuint buffer = this->getWavBuffer(_filename);
	ALuint source;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);

	float finalVolume = _volume;
	if(_music)
		finalVolume *= this->m_musicVolume;
	else
		finalVolume *= this->m_soundVolume;

	this->m_sounds.insert(pair<int, Sound*>(soundHandle, new Sound(source, _volume, finalVolume, _music, _3d, _pos)));

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

void SoundEngine::setMusicVolume(float _value)
{
	this->m_musicVolume = _value;

	for(map<int, Sound*>::iterator i = m_sounds.begin(); i != this->m_sounds.end(); i++)
	{
		if(i->second->isMusic())
			i->second->setVolume(this->m_musicVolume*i->second->getVolume());
	}
}

void SoundEngine::setSoundVolume(float _value)
{
	this->m_soundVolume = _value;

	for(map<int, Sound*>::iterator i = m_sounds.begin(); i != this->m_sounds.end(); i++)
	{
		if(!i->second->isMusic())
			i->second->setVolume(this->m_soundVolume*i->second->getVolume());
	}
}

void SoundEngine::setSoundVolume(int _handle, float _volume)
{
	for(map<int, Sound*>::iterator i = m_sounds.begin(); i != this->m_sounds.end(); i++)
	{
		if(i->first == _handle)
		{
			if(i->second->isMusic())
				i->second->setVolume(_volume, this->m_musicVolume*_volume);
			else
				i->second->setVolume(_volume, this->m_soundVolume*_volume);
		}
	}
}

void SoundEngine::stop(int _handle)const
{
	this->m_sounds.at(_handle)->stop();
}

void SoundEngine::update(float _x, float _y, float _z)
{
	vector<map<int, Sound*>::iterator> removeIndices;

	for(map<int, Sound*>::iterator i = m_sounds.begin(); i != m_sounds.end(); i++)
	{
		if(i->second->is3d())
			i->second->update3dVolume(WUFLOAT3(_x, _y, _z));

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