#pragma once

#if defined DLL_EXPORT
#define SOUND_EXPORT __declspec(dllexport)
#else
#define SOUND_EXPORT __declspec(dllimport)
#endif

#include "Framework.h"
#include "Sound.h"
#include <string>
#include <map>
using namespace std;

class SoundEngine
{
private:
	int m_handleCounter;
	map<string, ALuint> m_buffers;
	map<int, Sound*> m_sounds;
	float m_musicVolume;
	float m_soundVolume;

	ALuint getWavBuffer(string _filename);
public:
	SOUND_EXPORT SoundEngine();
	SOUND_EXPORT SoundEngine(float _musicVolume, float _soundVolume);
	SOUND_EXPORT ~SoundEngine();

	SOUND_EXPORT void clear();
	SOUND_EXPORT int createSoundHandle(string _filename, bool _music, float _volume = 1.0f);
	SOUND_EXPORT void deactivate(int _handle);
	SOUND_EXPORT bool isPlaying(int _handle);
	SOUND_EXPORT void play(int _handle)const;
	SOUND_EXPORT void loop(int _handle);
	SOUND_EXPORT void setMusicVolume(float _value);
	SOUND_EXPORT void setSoundVolume(float _value);
	SOUND_EXPORT void setSoundVolume(int _handle, float _volume);
	SOUND_EXPORT void stop(int _handle)const;
	SOUND_EXPORT void update();
};