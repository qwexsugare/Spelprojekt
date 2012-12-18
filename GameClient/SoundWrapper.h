#pragma once

#include <string>
using namespace std;

int createSoundHandle(string _filename);

void initSoundEngine();

void playSound(int _handle);

void deleteSoundEngine();