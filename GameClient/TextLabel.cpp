#include "TextLabel.h"
#include "Graphics.h"

TextLabel::TextLabel()
{
	m_myText = NULL;
}

TextLabel::TextLabel(string _text, string _texture, INT2 _pos, int _size)
{
	INT2 m_pos = _pos;
	int m_size;
	//m_pos.x = (_pos.x*(g_graphicsEngine->getRealScreenSize().x /1920));
	//m_pos.y = (_pos.y*(g_graphicsEngine->getRealScreenSize().y /1080));
	m_size  = ((_size * (g_graphicsEngine->getRealScreenSize().x+g_graphicsEngine->getRealScreenSize().y)/(1920+1080)));
	m_text = _text;
	this->m_myText = g_graphicsEngine->createMyText(_texture, "text/", "offsets.txt", m_text, m_pos, m_size);
	this->m_myText->DrawString(this->m_text);
}

TextLabel::~TextLabel()
{
	if(m_myText)
		g_graphicsEngine->removeMyText(m_myText);
}

void TextLabel::setText(string _text)
{
	this->m_text = _text;
	this->m_myText->DrawString(m_text);
}
string TextLabel::getText()
{ 
	return this->m_text; 
}
string TextLabel::IntToString(int intInput)
{

	stringstream ss;
	ss << intInput;
	return ss.str();
}