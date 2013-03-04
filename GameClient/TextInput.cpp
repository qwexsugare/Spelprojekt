#include "TextInput.h"
#include "Input.h"
#include "Graphics.h"

TextInput::TextInput()
{
	this->m_myText = NULL;
}

TextInput::TextInput(string _texture, INT2 _pos, int _size)
{
	INT2 m_pos = _pos;
	int m_size;
	//m_pos.x = (_pos.x*(g_graphicsEngine->getRealScreenSize().x /1920));
	//m_pos.y = (_pos.y*(g_graphicsEngine->getRealScreenSize().y /1080));
	m_size  = ((_size * (g_graphicsEngine->getRealScreenSize().x+g_graphicsEngine->getRealScreenSize().y)/(1920+1080)));
	this->m_text = "";
	this->m_myText = g_graphicsEngine->createMyText(_texture, "text/", "offsets.txt", m_text, m_pos, m_size);
	this->m_myText->DrawString(this->m_text);
	m_timer = 0.0f;
}

TextInput::~TextInput()
{
	if(this->m_myText)
		g_graphicsEngine->removeMyText(this->m_myText);
}
void TextInput::setText(string _text)
{
	this->m_text = _text;
	this->m_myText->DrawString(this->m_text);
}
string TextInput::getText()
{ 
	return this->m_text; 
}
void TextInput::update(float _dt)
{
	for(int i = 'A'; i < 'Z'+1; i++)
	{
		if(g_keyboard->getKeyState(i) == Keyboard::KEY_PRESSED && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP)
		{
			m_text += char(i);
			this->m_myText->DrawString(this->m_text);
		}
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_OEM_COMMA) == Keyboard::KEY_PRESSED)
	{
		m_text += ',';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_DELETE) == Keyboard::KEY_PRESSED)
	{
		m_text += ',';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_ADD) == Keyboard::KEY_PRESSED)
	{
		m_text += '+';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_OEM_PLUS) == Keyboard::KEY_PRESSED)
	{
		m_text += '+';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_OEM_MINUS) == Keyboard::KEY_PRESSED)
	{
		m_text += '-';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_SUBTRACT) == Keyboard::KEY_PRESSED)
	{
		m_text += '-';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_OEM_PLUS) == Keyboard::KEY_PRESSED)
	{
		m_text += '?';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(49) == Keyboard::KEY_PRESSED)
	{
		m_text += '!';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_OEM_PERIOD) == Keyboard::KEY_PRESSED)
	{
		m_text += '.';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_OEM_PERIOD) == Keyboard::KEY_PRESSED)
	{
		m_text += ':';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_SPACE) == Keyboard::KEY_PRESSED)
	{
		m_text += ' ';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_RETURN) == Keyboard::KEY_PRESSED)
	{
		m_text += '_';
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(50) == Keyboard::KEY_PRESSED)
	{
		m_text += 34;
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_OEM_PLUS) == Keyboard::KEY_PRESSED)
	{
		m_text += "\\";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(55) == Keyboard::KEY_PRESSED)
	{
		m_text += "/";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_DIVIDE) == Keyboard::KEY_PRESSED)
	{
		m_text += "/";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(55) == Keyboard::KEY_PRESSED)
	{
		m_text += "{";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(48) == Keyboard::KEY_PRESSED)
	{
		m_text += "}";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(48) == Keyboard::KEY_PRESSED)
	{
		m_text += "=";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(226) == Keyboard::KEY_PRESSED)
	{
		m_text += "<";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(226) == Keyboard::KEY_PRESSED)
	{
		m_text += ">";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(56) == Keyboard::KEY_PRESSED)
	{
		m_text += "(";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(57) == Keyboard::KEY_PRESSED)
	{
		m_text += ")";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MULTIPLY) == Keyboard::KEY_PRESSED)
	{
		m_text += "*";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP && g_keyboard->getKeyState(191) == Keyboard::KEY_PRESSED)
	{
		m_text += "*";
		this->m_myText->DrawString(this->m_text);
	}
	if(g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(52) == Keyboard::KEY_PRESSED)
	{
		m_text += "$";
		this->m_myText->DrawString(this->m_text);
	}
	for(int i = '0'; i < ':'; i++)
	{
		if(g_keyboard->getKeyState(i) == Keyboard::KEY_PRESSED && g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP)
		{
			m_text += char(i);
			this->m_myText->DrawString(this->m_text);
		}
	}
	if(g_keyboard->getKeyState(VK_BACK) == Keyboard::KEY_DOWN && g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP)
	{
		m_timer +=_dt;
		if(m_timer > 0.3f)
		{
			m_timer -= 0.1f;
			if(m_text.length() > 0)
			{
				m_text.erase(m_text.end()-1);
				this->m_myText->DrawString(this->m_text);
			}
		}
	}
	else if(g_keyboard->getKeyState(VK_BACK) == Keyboard::KEY_PRESSED && g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP)
	{
		if(m_text.length() > 0)
		{
			m_text.erase(m_text.end()-1);
			this->m_myText->DrawString(this->m_text);
		}
	}
	if(g_keyboard->getKeyState(VK_BACK) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP && g_keyboard->getKeyState(VK_MENU) == Keyboard::KEY_UP)
	{
		m_timer = 0.0f;
	}
}