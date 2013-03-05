#pragma once

#include "Hero.h"

class SpeechManager
{
private:
	static map<unsigned int, int> speeches;
public:
	static void init();
	static void release();
	static bool speak(unsigned int _id, int _sound);
	static void speakUltimate(unsigned int _id, int _sound);
	static void update();
};