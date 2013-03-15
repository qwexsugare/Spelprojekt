#include "Keyboard.h"

Keyboard::Keyboard()
{
	for(int i = 0; i < 256; i++)
		m_keys[i] = KEY_UP;

	this->m_nrOfKeysToReset = 0;
	this->chatMode=false;
}

Keyboard::~Keyboard()
{

}

int Keyboard::getKeyState(WPARAM _key)const
{
	if(this->chatMode)
		return Keyboard::KEY_UP;
	else
		return this->m_keys[_key];
}

int Keyboard::getKeyStateChatSuper(WPARAM _key)const
{
	return this->m_keys[_key];
}

void Keyboard::keyDown(WPARAM _key)
{
	if(this->m_keys[_key] == KEY_UP)
	{
		this->m_keys[_key] = KEY_PRESSED;
		this->m_keysToReset[this->m_nrOfKeysToReset++] = _key;
	}
	else
	{
		this->m_keys[_key] = KEY_DOWN;	
	}
}

void Keyboard::keyUp(WPARAM _key)
{
	this->m_keys[_key] = KEY_UP;
}

void Keyboard::update()
{
	for(int i = 0; i < this->m_nrOfKeysToReset; i++)
		this->m_keys[this->m_keysToReset[i]] = KEY_DOWN;

	this->m_nrOfKeysToReset = 0;
}
bool Keyboard::isInChatMode()
{
	return this->chatMode;
}

void Keyboard::setChatMode(bool _val)
{
	this->chatMode=_val;
}