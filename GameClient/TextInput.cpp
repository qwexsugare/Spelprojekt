#include "TextInput.h"
#include "Input.h"
#include "Graphics.h"

TextInput::TextInput()
{
	this->m_myText = NULL;
}

TextInput::TextInput(INT2 _pos, int _size)
{
	this->m_text = "";
	this->m_myText = g_graphicsEngine->createMyText("text1.png", m_text, _pos, _size);
}

TextInput::~TextInput()
{
	if(this->m_myText)
		g_graphicsEngine->removeMyText(this->m_myText);
}

void TextInput::update()
{
	for(int i = 'A'; i < 'Z'; i++)
	{
		if(g_keyboard->getKeyState(i) == Keyboard::KEY_PRESSED)
		{
			m_text += char(i);
		}
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_OEM_PLUS) == Keyboard::KEY_PRESSED)
	{
		m_text += '?';
	}

		/*else if (i == 13)
		{
			i = 95;
			str+=char(i);
		}
		else if (i==8)
		{
			str.erase(str.begin()+str.length()-1);
		}*/
}