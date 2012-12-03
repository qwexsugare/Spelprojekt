#pragma once

#include <Windows.h>
#include <map>
using namespace std;

class Keyboard
{
private:
	int m_keys[256];
public:
	static enum{KEY_UP, KEY_DOWN, KEY_PRESSED};

	Keyboard();
	~Keyboard();

	void keyDown(WPARAM _key);
	void keyUp(WPARAM _key);
	void update();
	int getKeyState(WPARAM _key);
};