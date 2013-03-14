#pragma once

#include "MyText.h"
#include "DataStructures.h"

class TextInput
{
private:
	string m_text;
	MyText* m_myText;
	float m_timer;
	int m_inputLimit;
public:
	TextInput();
	TextInput(string _texture, INT2 _pos, int _size, int _inputLimit = 1000);
	~TextInput();

	string getText();
	void setText(string _text);
	void update(float _dt);
};