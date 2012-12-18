#include "SoundWrapper.h"
#include "SoundEngine.h"

SoundEngine* g_soundEngine;

int createSoundHandle(string _filename)
{
	return g_soundEngine->createSoundHandle(_filename);
}

void initSoundEngine()
{
	g_soundEngine = new SoundEngine();
}

void playSound(int _handle)
{
	g_soundEngine->play(_handle);
}

void deleteSoundEngine()
{
	delete g_soundEngine;
}