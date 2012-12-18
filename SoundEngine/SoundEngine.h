#pragma once

#include "Framework.h"
#include <string>
#include <vector>
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
	map<string, ALuint> m_buffers;
	map<int, ALuint> m_sources;

	ALuint getWavBuffer(string _filename);
public:
	DECLDIR2 SoundEngine();
	DECLDIR2 ~SoundEngine();
	
	DECLDIR2 int createSoundHandle(string _filename);
	DECLDIR2 void inactivate(int _handle);
	DECLDIR2 bool isPlaying(int _handle)const;
	DECLDIR2 void play(int _handle)const;
	DECLDIR2 void stop(int _handle)const;
};