#include "SoundWrapper.h"
#include "SoundEngine.h"

static SoundEngine* g_soundEngine;

void clearSoundEngine()
{
	g_soundEngine->clear();
}

int createSoundHandle(string _filename, bool _music, float _volume)
{
	return g_soundEngine->createSoundHandle(_filename, _music, _volume);
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

void setSoundEffectsVolume(float _value)
{
	g_soundEngine->setSoundEffectsVolume(_value);
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

void updateSoundEngine()
{
	g_soundEngine->update();
}
/*
// RETARD CODE
void clearSoundEngine()
{

}

int createSoundHandle(string _filename, bool _music)
{
	return -1;
}

void deactivateSound(int _handle)
{

}

void initSoundEngine()
{

}

bool isSoundPlaying(int _handle)
{
	return false;
}

void loopSound(int _handle)
{

}

void playSound(int _handle)
{

}

void setMusicVolume(float _value)
{

}

void setSoundEffectsVolume(float _value)
{

}

void stopSound(int _handle)
{

}

void deleteSoundEngine()
{

}

void updateSoundEngine()
{

}*/