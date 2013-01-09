#include "MyTextOffsets.h"
#include <fstream>

MyTextOffsets::MyTextOffsets()
{
	/*m_charOffsets['A'] = 50.0f;
	charOffsets['B'] = 60.0f;
	charOffsets['C'] = 60.0f;
	charOffsets['D'] = 60.0f;
	charOffsets['E'] = 70.0f;
	charOffsets['F'] = 70.0f;
	charOffsets['G'] = 60.0f;
	charOffsets['H'] = 60.0f;
	charOffsets['I'] = 110.0f;
	charOffsets['J'] = 60.0f;
	charOffsets['K'] = 60.0f;
	charOffsets['L'] = 75.0f;
	charOffsets['M'] = 20.0f;
	charOffsets['N'] = 50.0f;
	charOffsets['O'] = 60.0f;
	charOffsets['P'] = 60.0f;
	charOffsets['Q'] = 60.0f;
	charOffsets['R'] = 60.0f;
	charOffsets['S'] = 60.0f;
	charOffsets['T'] = 60.0f;
	charOffsets['U'] = 65.0f;
	charOffsets['V'] = 60.0f;
	charOffsets['W'] = 40.0f;
	charOffsets['X'] = 60.0f;
	charOffsets['Y'] = 70.0f;
	charOffsets['Z'] = 60.0f;
	charOffsets['-'] = 70.0f;
	charOffsets[' '] = 110.0f;
	charOffsets['_'] = 150.0f;
	charOffsets['0'] = 60.0f;
	charOffsets['1'] = 60.0f;
	charOffsets['2'] = 60.0f;
	charOffsets['3'] = 60.0f;
	charOffsets['4'] = 60.0f;
	charOffsets['5'] = 60.0f;
	charOffsets['6'] = 60.0f;
	charOffsets['7'] = 60.0f;
	charOffsets['8'] = 60.0f;
	charOffsets['9'] = 60.0f;
	charOffsets[','] = 80.0f;
	charOffsets['+'] = 0.5f;
	charOffsets[':'] = 80.0f;
	charOffsets['('] = 70.0f;
	charOffsets[')'] = 70.0f;
	charOffsets['?'] = 60.0f;
	charOffsets['!'] = 80.0f;
	charOffsets['$'] = 20.0f;
	charOffsets['.'] = 80.0f;
	charOffsets['/'] = 60.0f;
	charOffsets['\\'] = 60.0f;
	charOffsets['{'] = 80.0f;
	charOffsets['}'] = 80.0f;
	charOffsets['='] = 50.0f;
	charOffsets['"'] = 60.0f;
	charOffsets['>'] = 0.0f;
	charOffsets['<'] = 0.0f;
	charOffsets['*'] = 70.0f;*/
}

MyTextOffsets::MyTextOffsets(string _path, string _filename)
{
	ifstream stream;
	stream.open(_path+_filename);

	if(stream.is_open())
	{
		int nrOfCharsInSheet = 56;
		char* charsInSheet = new char[nrOfCharsInSheet+1]; // +1 for emils enter
		charsInSheet[0] = 'A';
		charsInSheet[1] = 'B';
		charsInSheet[2] = 'C';
		charsInSheet[3] = 'D';
		charsInSheet[4] = 'E';
		charsInSheet[5] = 'F';
		charsInSheet[6] = 'G';
		charsInSheet[7] = 'H';
		charsInSheet[8] = 'I';
		charsInSheet[9] = 'J';
		charsInSheet[10] = 'K';
		charsInSheet[11] = 'L';
		charsInSheet[12] = 'M';
		charsInSheet[13] = 'N';
		charsInSheet[14] = 'O';
		charsInSheet[15] = 'P';
		charsInSheet[16] = 'Q';
		charsInSheet[17] = 'R';
		charsInSheet[18] = 'S';
		charsInSheet[19] = 'T';
		charsInSheet[20] = 'U';
		charsInSheet[21] = 'V';
		charsInSheet[22] = 'W';
		charsInSheet[23] = 'X';
		charsInSheet[24] = 'Y';
		charsInSheet[25] = 'Z';
		charsInSheet[26] = '-';
		charsInSheet[27] = ' ';
		charsInSheet[28] = '0';
		charsInSheet[29] = '1';
		charsInSheet[30] = '2';
		charsInSheet[31] = '3';
		charsInSheet[32] = '4';
		charsInSheet[33] = '5';
		charsInSheet[34] = '6';
		charsInSheet[35] = '7';
		charsInSheet[36] = '8';
		charsInSheet[37] = '9';
		charsInSheet[38] = ',';
		charsInSheet[39] = '+';
		charsInSheet[40] = ':';
		charsInSheet[41] = '(';
		charsInSheet[42] = ')';
		charsInSheet[43] = '?';
		charsInSheet[44] = '!';
		charsInSheet[45] = '$';
		charsInSheet[46] = '.';
		charsInSheet[47] = '/';
		charsInSheet[48] = '\\';
		charsInSheet[49] = '{';
		charsInSheet[50] = '}';
		charsInSheet[51] = '=';
		charsInSheet[52] = '"';
		charsInSheet[53] = '>';
		charsInSheet[54] = '<';
		charsInSheet[55] = '*';
		charsInSheet[56] = '_';

		int index = 0;
		while(!stream.eof())
		{
			char buf[1024];
			stream.getline(buf, 1024);
			int val1;
			int val2;
			sscanf(buf, "%d %d", &val1, &val2);

			m_charOffsets[charsInSheet[index++]] = INT2(val1, val2);
		}

		m_charOffsets['_'] = INT2(40, 40);
	}
	// else you are fucked.
	else
	{

	}

	int lol = 0;
}

MyTextOffsets::~MyTextOffsets()
{

}