#include "SoundWrapper.h"
#include "SoundEngine.h"

static SoundEngine* g_soundEngine;

void clearSoundEngine()
{
	g_soundEngine->clear();
}

int createSoundHandle(string _filename, bool _music, bool _3d, FLOAT3 _pos, float _volume)
{
	return g_soundEngine->createSoundHandle(_filename, _music, _3d, WUFLOAT3(_pos.x, _pos.y, _pos.z), _volume);
}

void deactivateSound(int _handle)
{
	g_soundEngine->deactivate(_handle);
}

void initSoundEngine()
{
	g_soundEngine = new SoundEngine();
}

bool isSoundPlaying(int _handle)
{
	return g_soundEngine->isPlaying(_handle);
}

void loopSound(int _handle)
{
	g_soundEngine->loop(_handle);
}

void playSound(int _handle)
{
	g_soundEngine->play(_handle);
}

void setMusicVolume(float _value)
{
	g_soundEngine->setMusicVolume(_value);
}

void setSoundVolume(float _value)
{
	g_soundEngine->setSoundVolume(_value);
}
void setSpeechVolume(float _value)
{
	// till Markus från Emil ha kul =)
	//g_soundEngine->setSpeechVolume(_value);
}

void setSoundVolume(int _handle, float _volume)
{
	g_soundEngine->setSoundVolume(_handle, _volume);
}

void stopSound(int _handle)
{
	g_soundEngine->stop(_handle);
}

void deleteSoundEngine()
{
	delete g_soundEngine;
}

void updateSoundEngine(const FLOAT3& _listenerPos)
{
	g_soundEngine->update(_listenerPos.x, _listenerPos.y, _listenerPos.z);
}