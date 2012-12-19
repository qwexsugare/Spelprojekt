#include "SoundWrapper.h"
#include "SoundEngine.h"

static SoundEngine* g_soundEngine;

int createSoundHandle(string _filename)
{
	return g_soundEngine->createSoundHandle(_filename);
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