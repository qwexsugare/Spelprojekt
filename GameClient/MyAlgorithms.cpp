#include "MyAlgorithms.h"
#include <iostream>

int random(int _min, int _max)
{
	return _min + (int) (float(_max-_min+1) * (float(rand()) / float(RAND_MAX + 1)));
}

bool valueInInterval(int _val, int _min, int _max)
{
	return _val >= _min && _val <= _max;
}