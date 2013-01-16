#include "TextLabel.h"
#include "Graphics.h"

TextLabel::TextLabel()
{
	m_myText = NULL;
}

TextLabel::TextLabel(string _text, string _texture, INT2 _pos, int _size)
{
	m_text = _text;
	this->m_myText = g_graphicsEngine->createMyText(_texture, "text/", "offsets.txt", m_text, _pos, _size);
	this->m_myText->DrawString(this->m_text);
}

TextLabel::~TextLabel()
{
	if(m_myText)
		g_graphicsEngine->removeMyText(m_myText);
}

void TextLabel::setText(string _text)
{
	m_text = _text;
	m_myText->DrawString(m_text);
}