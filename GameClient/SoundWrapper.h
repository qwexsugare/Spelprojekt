#pragma once

#include <string>
using namespace std;

int createSoundHandle(string _filename);

void deactivateSound(int _handle);

void initSoundEngine();

bool isSoundPlaying(int _handle);

void loopSound(int _handle);

void playSound(int _handle);

void stopSound(int _handle);

void deleteSoundEngine();

void updateSoundEngine();