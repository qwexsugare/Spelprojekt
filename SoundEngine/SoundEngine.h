#pragma once

#include "Framework.h"
#include "Sound.h"
#include <string>
#include <map>
using namespace std;

#if defined DLL_EXPORT
#define DECLDIR2 __declspec(dllexport)
#else
#define DECLDIR2 __declspec(dllimport)
#endif

class SoundEngine
{
private:
	int m_handleCounter;
	map<string, ALuint> m_buffers;
	map<int, Sound*> m_sounds;

	ALuint getWavBuffer(string _filename);
public:
	DECLDIR2 SoundEngine();
	DECLDIR2 ~SoundEngine();
	
	DECLDIR2 int createSoundHandle(string _filename);
	DECLDIR2 void deactivate(int _handle);
	DECLDIR2 bool isPlaying(int _handle);
	DECLDIR2 void play(int _handle)const;
	DECLDIR2 void loop(int _handle);
	DECLDIR2 void stop(int _handle)const;
	DECLDIR2 void update();
};