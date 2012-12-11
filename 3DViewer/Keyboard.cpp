#include "Keyboard.h"

Keyboard::Keyboard()
{
	this->m_keys['1'] = KEY_UP;
	this->m_keys['2'] = KEY_UP;
	this->m_keys['3'] = KEY_UP;
	this->m_keys['4'] = KEY_UP;
	this->m_keys[VK_LEFT] = KEY_UP;
	this->m_keys[VK_RIGHT] = KEY_UP;
	this->m_keys[VK_UP] = KEY_UP;
	this->m_keys[VK_DOWN] = KEY_UP;
}

Keyboard::~Keyboard()
{

}

int Keyboard::getKeyState(WPARAM _key)
{
	return this->m_keys[_key];
}

void Keyboard::keyDown(WPARAM _key)
{
	if(this->m_keys[_key] == KEY_UP)
	{
		this->m_keys[_key] = KEY_PRESSED;
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