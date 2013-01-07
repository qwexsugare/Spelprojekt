#pragma once

#include <string>
using namespace std;

int createSoundHandle(string _filename, bool _music);

void deactivateSound(int _handle);

void initSoundEngine();

bool isSoundPlaying(int _handle);

void loopSound(int _handle);

void playSound(int _handle);

void setMusicVolume(float _value);

void setSoundEffectsVolume(float _value);

void stopSound(int _handle);

void deleteSoundEngine();

void updateSoundEngine();