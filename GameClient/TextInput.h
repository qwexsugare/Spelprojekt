#pragma once

#include "MyText.h"
#include "DataStructures.h"

class TextInput
{
private:
	string m_text;
	MyText* m_myText;
public:
	TextInput();
	TextInput(INT2 _pos, int _size);
	~TextInput();

	void update();
};