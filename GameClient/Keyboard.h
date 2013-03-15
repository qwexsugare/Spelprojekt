#pragma once

#include <Windows.h>

class Keyboard
{
private:
	int m_keys[256];
	int m_keysToReset[256];
	int m_nrOfKeysToReset;
	bool chatMode;
public:
	static enum{KEY_UP, KEY_DOWN, KEY_PRESSED};

	Keyboard();
	~Keyboard();

	void keyDown(WPARAM _key);
	void keyUp(WPARAM _key);
	int getKeyState(WPARAM _key)const;
	int getKeyStateChatSuper(WPARAM _key)const;
	void update();
	bool isInChatMode();
	void setChatMode(bool _val);
};