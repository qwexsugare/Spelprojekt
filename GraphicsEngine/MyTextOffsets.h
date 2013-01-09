#pragma once

#include <string>
using namespace std;
#include "DataStructures.h"

class MyTextOffsets
{
private:
	INT2 m_charOffsets[256];
public:
	MyTextOffsets();
	MyTextOffsets(string _path, string _filename);
	~MyTextOffsets();

	INT2 getCharOffset(int _index)const { return this->m_charOffsets[_index]; }
};